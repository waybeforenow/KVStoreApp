#include <grpcpp/grpcpp.h>
#include <stdint.h>

#include <immer/map.hpp>
#include <string>

#include "github.com/tendermint/tendermint/abci/types/types.grpc.pb.h"

class KVStoreApp final : public ::types::ABCIApplication::Service {
  using ServerContext = grpc::ServerContext;
  using Status = grpc::Status;

  // Implementations of RPC methods.
  Status Info(ServerContext* ctx, const types::RequestInfo* req,
              types::ResponseInfo* resp) override;

  Status SetOption(ServerContext* ctx, const types::RequestSetOption* req,
                   types::ResponseSetOption* resp) override;

  Status DeliverTx(ServerContext* ctx, const types::RequestDeliverTx* req,
                   types::ResponseDeliverTx* resp) override;

  Status CheckTx(ServerContext* ctx, const types::RequestCheckTx* req,
                 types::ResponseCheckTx* resp) override;

  Status Commit(ServerContext* ctx, const types::RequestCommit* req,
                types::ResponseCommit* resp) override;

  Status Query(ServerContext* ctx, const types::RequestQuery* req,
               types::ResponseQuery* resp) override;

  Status InitChain(ServerContext* ctx, const types::RequestInitChain* req,
                   types::ResponseInitChain* resp) override;

  Status BeginBlock(ServerContext* ctx, const types::RequestBeginBlock* req,
                    types::ResponseBeginBlock* resp) override;

  Status EndBlock(ServerContext* ctx, const types::RequestEndBlock* req,
                  types::ResponseEndBlock* resp) override;

  Status Echo(ServerContext* ctx, const types::RequestEcho* req,
              types::ResponseEcho* resp) override;

  Status Flush(ServerContext* ctx, const types::RequestFlush* req,
               types::ResponseFlush* resp) override;

  // Private helper methods.
  uint32_t isValid(const std::string& tx);

  // Private members.
  immer::map<std::string, std::string> store;
  immer::map<std::string, std::string> mutatedStore;
};
