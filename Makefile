PROTOC=protoc
LDFLAGS+=-L/usr/local/lib `pkg-config --libs protobuf grpc++`
CPPFLAGS+=`pkg-config --cflags protobuf grpc`
CXXFLAGS+=-std=c++14 -I.

.DEFAULT_GOAL := KVStoreApp

KVStoreApp: \
	github.com/gogo/protobuf/gogoproto/gogo.pb.o \
	github.com/tendermint/tendermint/libs/common/types.pb.o \
	github.com/tendermint/tendermint/crypto/merkle/merkle.pb.o \
	github.com/tendermint/tendermint/abci/types/types.pb.o \
	github.com/tendermint/tendermint/abci/types/types.grpc.pb.o \
	main.o KVStoreApp.o 
	$(CXX) $^ $(LDFLAGS) -o $@

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) --cpp_out=. $<

.PHONY: clean
clean:
	rm main && find . \( -name "*.o" -or -name "*.pb.cc" -or -name "*.pb.h" \) -delete
