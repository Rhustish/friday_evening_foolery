rm -fr builtProtos

mkdir builtProtos

protoc --cpp_out=./builtProtos/ game.proto
