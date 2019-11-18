# KVStoreApp
Sample Tendermint application, written in C++. It's based on [the example Go application](https://tendermint.com/docs/guides/go.html) in the [Tendermint documentation](https://tendermint.com/docs/).

## Prerequisites
* [Boost String Algorithms](https://www.boost.org/doc/libs/1_71_0/doc/html/string_algo.html)
* [gRPC](https://grpc.io)
* [protobuf](https://github.com/protocolbuffers/protobuf)
* [immer](https://github.com/arximboldi/immer)
* [Tendermint](https://github.com/tendermint/tendermint)

## Build
```
git submodule update --init --recursive
make KVStoreApp
```

## Run
```
GRPC_BIND=127.0.0.1:20021 ./KVStoreApp
```

In a separate window:
```
tendermint node --abci grpc --proxy_app "tcp://127.0.0.1:20021"
```
