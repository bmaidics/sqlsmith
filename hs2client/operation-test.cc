// Copyright 2016 Cloudera Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "hs2client/operation.h"

#include <gtest/gtest.h>
#include <memory>
#include <sstream>

#include "hs2client/service.h"
#include "hs2client/session.h"
#include "hs2client/test-util.h"

using namespace hs2client;
using namespace std;

class OperationTest : public HS2ClientTest {};

TEST_F(OperationTest, TestFetch) {
  CreateTestTable();
  InsertIntoTestTable(vector<int>({1, 2, 3, 4}), vector<string>({"a", "b", "c", "d"}));

  unique_ptr<Operation> select_op;
  EXPECT_OK(session_->ExecuteStatement("select * from " + TEST_TBL + " order by int_col",
      &select_op));

  unique_ptr<ColumnarRowSet> results;
  bool has_more_rows = false;
  // Impala only supports NEXT and FIRST.
  EXPECT_ERROR(select_op->Fetch(2, FetchOrientation::LAST, &results,
      &has_more_rows));

  // Fetch the results in two batches by passing max_rows to Fetch.
  EXPECT_OK(select_op->Fetch(2, FetchOrientation::NEXT, &results, &has_more_rows));
  EXPECT_OK(Wait(select_op));
  EXPECT_TRUE(select_op->HasResultSet());
  unique_ptr<Int32Column> int_col = results->GetInt32Col(0);
  unique_ptr<StringColumn> string_col = results->GetStringCol(1);
  EXPECT_EQ(int_col->data(), vector<int>({1, 2}));
  EXPECT_EQ(string_col->data(), vector<string>({"a", "b"}));
  EXPECT_TRUE(has_more_rows);

  EXPECT_OK(select_op->Fetch(2, FetchOrientation::NEXT, &results, &has_more_rows));
  int_col = results->GetInt32Col(0);
  string_col = results->GetStringCol(1);
  EXPECT_EQ(int_col->data(), vector<int>({3, 4}));
  EXPECT_EQ(string_col->data(), vector<string>({"c", "d"}));

  EXPECT_OK(select_op->Fetch(2, FetchOrientation::NEXT, &results, &has_more_rows));
  int_col = results->GetInt32Col(0);
  string_col = results->GetStringCol(1);
  EXPECT_EQ(int_col->length(), 0);
  EXPECT_EQ(string_col->length(), 0);
  EXPECT_FALSE(has_more_rows);

  EXPECT_OK(select_op->Fetch(2, FetchOrientation::NEXT, &results, &has_more_rows));
  int_col = results->GetInt32Col(0);
  string_col = results->GetStringCol(1);
  EXPECT_EQ(int_col->length(), 0);
  EXPECT_EQ(string_col->length(), 0);
  EXPECT_FALSE(has_more_rows);

  EXPECT_OK(select_op->Close());
}

TEST_F(OperationTest, TestIsNull) {
  CreateTestTable();
  // Insert some NULLs and ensure Column::IsNull() is correct.
  InsertIntoTestTable(vector<int>({1, 2, 3, 4, 5, NULL_INT_VALUE}),
      vector<string>({"a", "b", "NULL", "d", "NULL", "f"}));

  unique_ptr<Operation> select_nulls_op;
  EXPECT_OK(session_->ExecuteStatement("select * from " + TEST_TBL + " order by int_col",
      &select_nulls_op));

  unique_ptr<ColumnarRowSet> nulls_results;
  bool has_more_rows = false;
  EXPECT_OK(select_nulls_op->Fetch(&nulls_results, &has_more_rows));
  unique_ptr<Int32Column> int_col = nulls_results->GetInt32Col(0);
  unique_ptr<StringColumn> string_col = nulls_results->GetStringCol(1);
  EXPECT_EQ(int_col->length(), 6);
  EXPECT_EQ(int_col->length(), string_col->length());

  bool int_nulls[] = {false, false, false, false, false, true};
  for (int i = 0; i < int_col->length(); i++) {
    EXPECT_EQ(int_col->IsNull(i), int_nulls[i]);
  }
  bool string_nulls[] = {false, false, true, false, true, false};
  for (int i = 0; i < string_col->length(); i++) {
    EXPECT_EQ(string_col->IsNull(i), string_nulls[i]);
  }

  EXPECT_OK(select_nulls_op->Close());
}

TEST_F(OperationTest, TestCancel) {
  CreateTestTable();
  InsertIntoTestTable(vector<int>({1, 2, 3, 4}), vector<string>({"a", "b", "c", "d"}));

  unique_ptr<Operation> op;
  EXPECT_OK(session_->ExecuteStatement("select count(*) from " + TEST_TBL, &op));
  op->Cancel();
  // Impala currently returns ERROR and not CANCELED for canceled queries
  // due to the use of beeswax states, which don't support a canceled state.
  EXPECT_OK(Wait(op, Operation::State::ERROR));

  string profile;
  EXPECT_OK(op->GetProfile(&profile));
  EXPECT_TRUE(profile.find("Cancelled") != string::npos);

  EXPECT_OK(op->Close());
}

TEST_F(OperationTest, TestGetLog) {
  CreateTestTable();

  unique_ptr<Operation> op;
  EXPECT_OK(session_->ExecuteStatement("select count(*) from " + TEST_TBL, &op));
  string log;
  EXPECT_OK(op->GetLog(&log));
  EXPECT_TRUE(log != "");

  EXPECT_OK(op->Close());
}

TEST_F(OperationTest, TestGetResultSetMetadata) {
  const string TEST_COL1 = "int_col";
  const string TEST_COL2 = "varchar_col";
  const int MAX_LENGTH = 10;
  const string TEST_COL3 = "decimal_cal";
  const int PRECISION = 5;
  const int SCALE = 3;
  std::stringstream create_query;
  create_query << "create table " << TEST_TBL << " (" << TEST_COL1 << " int, "
               << TEST_COL2 << " varchar(" << MAX_LENGTH << "), " << TEST_COL3
               << " decimal(" << PRECISION << ", " << SCALE << "))";
  unique_ptr<Operation> create_table_op;
  EXPECT_OK(session_->ExecuteStatement(create_query.str(), &create_table_op));
  EXPECT_OK(create_table_op->Close());

  // Perform a select, and check that we get the right metadata back.
  unique_ptr<Operation> select_op;
  EXPECT_OK(session_->ExecuteStatement("select * from " + TEST_TBL, &select_op));
  vector<ColumnDesc> column_descs;
  select_op->GetResultSetMetadata(&column_descs);
  EXPECT_EQ(column_descs.size(), 3);

  EXPECT_EQ(column_descs[0].column_name(), TEST_COL1);
  EXPECT_EQ(column_descs[0].type()->ToString(), "INT");
  EXPECT_EQ(column_descs[0].type()->type_id(), ColumnType::TypeId::INT);
  EXPECT_EQ(column_descs[0].position(), 0);

  EXPECT_EQ(column_descs[1].column_name(), TEST_COL2);
  EXPECT_EQ(column_descs[1].type()->ToString(), "VARCHAR");
  EXPECT_EQ(column_descs[1].type()->type_id(), ColumnType::TypeId::VARCHAR);
  EXPECT_EQ(column_descs[1].position(), 1);
  EXPECT_EQ(column_descs[1].GetCharacterType()->max_length(), MAX_LENGTH);

  EXPECT_EQ(column_descs[2].column_name(), TEST_COL3);
  EXPECT_EQ(column_descs[2].type()->ToString(), "DECIMAL");
  EXPECT_EQ(column_descs[2].type()->type_id(), ColumnType::TypeId::DECIMAL);
  EXPECT_EQ(column_descs[2].position(), 2);
  EXPECT_EQ(column_descs[2].GetDecimalType()->precision(), PRECISION);
  EXPECT_EQ(column_descs[2].GetDecimalType()->scale(), SCALE);

  EXPECT_OK(select_op->Close());

  // Insert ops don't have result sets.
  std::stringstream insert_query;
  insert_query << "insert into " << TEST_TBL << " VALUES (1, cast('a' as varchar("
               << MAX_LENGTH << ")), cast(1 as decimal(" << PRECISION << ", " << SCALE
               << ")))";
  unique_ptr<Operation> insert_op;
  EXPECT_OK(session_->ExecuteStatement(insert_query.str(), &insert_op));
  vector<ColumnDesc> insert_column_descs;
  EXPECT_OK(insert_op->GetResultSetMetadata(&insert_column_descs));
  EXPECT_EQ(insert_column_descs.size(), 0);
  EXPECT_OK(insert_op->Close());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
