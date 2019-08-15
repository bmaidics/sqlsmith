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

#include "hs2client/logging.h"
#include "hs2client/macros.h"
#include "hs2client/thrift-internal.h"

#include "gen-cpp/ImpalaService_types.h"
#include "gen-cpp/TCLIService.h"

namespace hs2 = apache::hive::service::cli::thrift;
using std::unique_ptr;

namespace hs2client {

// Max rows to fetch, if not specified.
const static int DEFAULT_MAX_ROWS = 1024;

Operation::Operation(const std::shared_ptr<ThriftRPC>& rpc)
  : impl_(new OperationImpl()), rpc_(rpc), open_(false) {}

Operation::~Operation() {
  DCHECK(!open_);
}

Status Operation::GetState(Operation::State* out) const {
  hs2::TGetOperationStatusReq req;
  req.__set_operationHandle(impl_->handle);
  hs2::TGetOperationStatusResp resp;
  TRY_RPC_OR_RETURN(rpc_->client->GetOperationStatus(resp, req));
  RETURN_NOT_OK(resp.status);
  *out = TOperationStateToOperationState(resp.operationState);
  return TStatusToStatus(resp.status);
}

Status Operation::GetLog(std::string* out) const {
  hs2::TGetLogReq req;
  req.__set_operationHandle(impl_->handle);
  hs2::TGetLogResp resp;
  TRY_RPC_OR_RETURN(rpc_->client->GetLog(resp, req));
  RETURN_NOT_OK(resp.status);
  *out = resp.log;
  return TStatusToStatus(resp.status);
}

Status Operation::GetProfile(std::string* out) const {
  impala::TGetRuntimeProfileReq req;
  req.__set_operationHandle(impl_->handle);
  req.__set_sessionHandle(impl_->session_handle);
  impala::TGetRuntimeProfileResp resp;
  TRY_RPC_OR_RETURN(rpc_->client->GetRuntimeProfile(resp, req));
  RETURN_NOT_OK(resp.status);
  *out = resp.profile;
  return TStatusToStatus(resp.status);
}

Status Operation::GetResultSetMetadata(std::vector<ColumnDesc>* column_descs) const {
  hs2::TGetResultSetMetadataReq req;
  req.__set_operationHandle(impl_->handle);
  hs2::TGetResultSetMetadataResp resp;
  TRY_RPC_OR_RETURN(rpc_->client->GetResultSetMetadata(resp, req));
  RETURN_NOT_OK(resp.status);

  column_descs->clear();
  column_descs->reserve(resp.schema.columns.size());
  for (const hs2::TColumnDesc& tcolumn_desc: resp.schema.columns) {
    column_descs->emplace_back(tcolumn_desc.columnName,
        TTypeDescToColumnType(tcolumn_desc.typeDesc), tcolumn_desc.position,
        tcolumn_desc.comment);
  }

  return TStatusToStatus(resp.status);
}

Status Operation::Fetch(unique_ptr<ColumnarRowSet>* results, bool* has_more_rows) const {
  return Fetch(DEFAULT_MAX_ROWS, FetchOrientation::NEXT, results, has_more_rows);
}

Status Operation::Fetch(int max_rows, FetchOrientation orientation,
    unique_ptr<ColumnarRowSet>* results, bool* has_more_rows) const {
  hs2::TFetchResultsReq req;
  req.__set_operationHandle(impl_->handle);
  req.__set_orientation(FetchOrientationToTFetchOrientation(orientation));
  req.__set_maxRows(max_rows);
  std::unique_ptr<ColumnarRowSet::ColumnarRowSetImpl> row_set_impl(
      new ColumnarRowSet::ColumnarRowSetImpl());
  TRY_RPC_OR_RETURN(rpc_->client->FetchResults(row_set_impl->resp, req));
  RETURN_NOT_OK(row_set_impl->resp.status);

  if (has_more_rows != NULL) {
    *has_more_rows = row_set_impl->resp.hasMoreRows;
  }
  Status status = TStatusToStatus(row_set_impl->resp.status);
  DCHECK(status.ok());
  results->reset(new ColumnarRowSet(row_set_impl.release()));
  return status;
}

Status Operation::Cancel() const {
  hs2::TCancelOperationReq req;
  req.__set_operationHandle(impl_->handle);
  hs2::TCancelOperationResp resp;
  TRY_RPC_OR_RETURN(rpc_->client->CancelOperation(resp, req));
  return TStatusToStatus(resp.status);
}

Status Operation::Close() {
  if (!open_) return Status::OK();

  hs2::TCloseOperationReq req;
  req.__set_operationHandle(impl_->handle);
  hs2::TCloseOperationResp resp;
  TRY_RPC_OR_RETURN(rpc_->client->CloseOperation(resp, req));
  RETURN_NOT_OK(resp.status);

  open_ = false;
  return TStatusToStatus(resp.status);
}

bool Operation::HasResultSet() const {
  State op_state;
  Status s = GetState(&op_state);
  if (!s.ok()) return false;
  return op_state == State::FINISHED;
}

bool Operation::IsColumnar() const {
  // We currently only support the columnar hs2 protocols.
  return true;
}

} // namespace hs2client
