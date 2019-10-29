# KVStoreApp
Sample Tendermint application, written in C++. It's based on [the example Go application](https://tendermint.com/docs/guides/go.html) in the [Tendermint documentation](https://tendermint.com/docs/).

## Prerequisites
* [gRPC](https://grpc.io)
* [protobuf](https://github.com/protocolbuffers/protobuf)
* [immer](https://github.com/arximboldi/immer)
* [Tendermint](https://github.com/tendermint/tendermint)

## Build
```
make
```

## Run
```
GRPC_BIND=127.0.0.1:20021 ./main
```

In a separate window:
```
tendermint node --abci grpc --proxy_app "tcp://127.0.0.1:20020"
```
