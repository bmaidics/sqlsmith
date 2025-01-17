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

#include <cassert>
#include <iostream>

#include "hs2client/api.h"

using namespace hs2client;
using namespace std;

int main(int argc, char** argv) {
  // Connect to the server.
  string host = "localhost";
  int port = 21050;
  int conn_timeout = 0;
  ProtocolVersion protocol = ProtocolVersion::HS2CLIENT_PROTOCOL_V7;
  unique_ptr<Service> service;
  Status status = Service::Connect( host, port, conn_timeout, protocol, &service);
  if (!status.ok()) {
    cout << "Failed to connect to service: " << status.GetMessage();
    service->Close();
    return 1;
  }

  // Open a session.
  string user = "user";
  HS2ClientConfig config;
  unique_ptr<Session> session;
  status = service->OpenSession(user, config, &session);
  if (!status.ok()) {
    cout << "Failed to open session: " << status.GetMessage();
    session->Close();
    service->Close();
    return 1;
  }

  // Execute a statement.
  string statement = "SELECT int_col, string_col FROM test order by int_col";
  unique_ptr<Operation> execute_op;
  status = session->ExecuteStatement(statement, &execute_op);
  if (!status.ok()) {
    cout << "Failed to execute select: " << status.GetMessage();
    execute_op->Close();
    session->Close();
    service->Close();
    return 1;
  }

  unique_ptr<ColumnarRowSet> execute_results;
  bool has_more_rows = true;
  int total_retrieved = 0;
  cout << "Contents of test:\n";
  while (has_more_rows) {
    status = execute_op->Fetch(&execute_results, &has_more_rows);
    if (!status.ok()) {
      cout << "Failed to fetch results: " << status.GetMessage();
      execute_op->Close();
      session->Close();
      service->Close();
      return 1;
    }

    unique_ptr<Int32Column> int_col = execute_results->GetInt32Col(0);
    unique_ptr<StringColumn> string_col =
        execute_results->GetStringCol(1);
    assert(int_col->length() == string_col->length());
    total_retrieved += int_col->length();
    for (int64_t i = 0; i < int_col->length(); ++i) {
      if (int_col->IsNull(i)) {
        cout << "NULL";
      } else {
        cout << int_col->GetData(i);
      }
      cout << ":";

      if (string_col->IsNull(i)) {
        cout << "NULL";
      } else {
        cout << "'" << string_col->GetData(i) << "'";
      }
      cout << "\n";
    }
  }
  cout << "retrieved " << total_retrieved << " rows\n";
  cout << "\n";
  execute_op->Close();

  unique_ptr<Operation> show_tables_op;
  status = session->ExecuteStatement("show tables", &show_tables_op);
  if (!status.ok()) {
    cout << "Failed to execute GetTables: " << status.GetMessage();
    show_tables_op->Close();
    session->Close();
    service->Close();
    return 1;
  }

  cout << "Show tables:\n";
  Util::PrintResults(show_tables_op.get(), cout);
  show_tables_op->Close();

  // Shut down.
  session->Close();
  service->Close();

  return 0;
}
