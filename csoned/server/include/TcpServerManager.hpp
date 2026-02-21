#pragma once

#include <TcpServer.hpp>
#include <memory>
#include <unordered_map>
class TcpServerManager{
  std::unordered_map<int, std::unique_ptr<TcpServer>> servers;
  TcpServerManager();

public:
  static TcpServerManager& getServerManager();
  TcpServer& getServerForPort(int port) ;
  void destroyServer(int port);
};
