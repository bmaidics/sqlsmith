// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "ImpalaService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::impala;

class ImpalaServiceHandler : virtual public ImpalaServiceIf {
 public:
  ImpalaServiceHandler() {
    // Your initialization goes here
  }

  void Cancel( ::impala::TStatus& _return, const  ::beeswax::QueryHandle& query_id) {
    // Your implementation goes here
    printf("Cancel\n");
  }

  void ResetCatalog( ::impala::TStatus& _return) {
    // Your implementation goes here
    printf("ResetCatalog\n");
  }

  void ResetTable( ::impala::TStatus& _return, const TResetTableReq& request) {
    // Your implementation goes here
    printf("ResetTable\n");
  }

  void GetRuntimeProfile(std::string& _return, const  ::beeswax::QueryHandle& query_id) {
    // Your implementation goes here
    printf("GetRuntimeProfile\n");
  }

  void CloseInsert(TInsertResult& _return, const  ::beeswax::QueryHandle& handle) {
    // Your implementation goes here
    printf("CloseInsert\n");
  }

  void PingImpalaService(TPingImpalaServiceResp& _return) {
    // Your implementation goes here
    printf("PingImpalaService\n");
  }

  void GetExecSummary( ::impala::TExecSummary& _return, const  ::beeswax::QueryHandle& handle) {
    // Your implementation goes here
    printf("GetExecSummary\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<ImpalaServiceHandler> handler(new ImpalaServiceHandler());
  shared_ptr<TProcessor> processor(new ImpalaServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
