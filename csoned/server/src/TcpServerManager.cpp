#include <TcpServerManager.hpp>


TcpServerManager::TcpServerManager(){
  servers.clear();
};

TcpServerManager& TcpServerManager::getServerManager(){
  static TcpServerManager serverManager;
  return serverManager;
}
TcpServer& TcpServerManager::getServerForPort(int port){
  if(servers.find(port) != servers.end()){
    return *(servers[port]);
  }
  servers[port] = std::unique_ptr<TcpServer>(new TcpServer(port));
  servers[port]->bindFdToPort();
  return *(servers[port]);
}

void TcpServerManager::destroyServer(int port){
  if(servers.find(port) != servers.end()){
    servers.erase(port);
  }
}
