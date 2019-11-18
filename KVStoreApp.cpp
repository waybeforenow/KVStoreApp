#include "KVStoreApp.hpp"

#include <boost/algorithm/string.hpp>

using ServerContext = grpc::ServerContext;
using Status = grpc::Status;

uint32_t KVStoreApp::isValid(const std::string& tx) {
  std::vector<std::string> parts;
  boost::split(parts, tx, [](const char c) { return c == '='; });

  if (parts.size() != 2) {
    return 1;
  }
  auto key = std::move(parts[0]), value = std::move(parts[1]);

  auto item = this->store.find(key);
  if (item == nullptr) {
    return 0;
  }
  if (*item == value) {
    return 2;
  }

  return 0;
}

Status KVStoreApp::CheckTx(ServerContext* ctx, const types::RequestCheckTx* req,
                           types::ResponseCheckTx* resp) {
  resp->set_code(isValid(req->tx()));
  resp->set_gas_wanted(1);
  return Status::OK;
}

Status KVStoreApp::BeginBlock(ServerContext* ctx,
                              const types::RequestBeginBlock* req,
                              types::ResponseBeginBlock* resp) {
  mutatedStore = this->store;
  return Status::OK;
}

Status KVStoreApp::DeliverTx(ServerContext* ctx,
                             const types::RequestDeliverTx* req,
                             types::ResponseDeliverTx* resp) {
  const auto code = isValid(req->tx());
  resp->set_code(code);
  if (code != 0) {
    return Status::OK;
  }

  std::vector<std::string> parts;
  boost::split(parts, req->tx(), [](const char c) { return c == '='; });
  auto key = std::move(parts[0]), value = std::move(parts[1]);
  this->mutatedStore = this->mutatedStore.set(key, value);

  return Status::OK;
}

Status KVStoreApp::Commit(ServerContext* ctx, const types::RequestCommit* req,
                          types::ResponseCommit* resp) {
  this->store = std::move(this->mutatedStore);
  return Status::OK;
}

Status KVStoreApp::Query(ServerContext* ctx, const types::RequestQuery* req,
                         types::ResponseQuery* resp) {
  const auto& key = req->data();
  const auto item = this->store.find(key);
  resp->set_key(key);
  if (item == nullptr) {
    resp->set_log("does not exist");
  } else {
    resp->set_log("exists");
    resp->set_value(*item);
  }

  return Status::OK;
}

Status KVStoreApp::Echo(ServerContext* ctx, const types::RequestEcho* req,
                        types::ResponseEcho* resp) {
  resp->set_message(req->message());
  return Status::OK;
}

Status KVStoreApp::Info(ServerContext* ctx, const types::RequestInfo* req,
                        types::ResponseInfo* resp) {
  return Status::OK;
}

Status KVStoreApp::SetOption(ServerContext* ctx,
                             const types::RequestSetOption* req,
                             types::ResponseSetOption* resp) {
  return Status::OK;
}

Status KVStoreApp::InitChain(ServerContext* ctx,
                             const types::RequestInitChain* req,
                             types::ResponseInitChain* resp) {
  return Status::OK;
}

Status KVStoreApp::EndBlock(ServerContext* ctx,
                            const types::RequestEndBlock* req,
                            types::ResponseEndBlock* resp) {
  return Status::OK;
}

Status KVStoreApp::Flush(ServerContext* ctx, const types::RequestFlush* req,
                         types::ResponseFlush* resp) {
  return Status::OK;
}
