#include <TcpServer.hpp>
#include <iostream>
#include <sys/socket.h>

TcpServer::TcpServer(int port): isRunning(false), isBound(false), sockFd(-1){

  this-> sockFd = socket(AF_INET, SOCK_STREAM, 0);
  this-> portNumber = htons(port);

  this->socketAddress = {
    .sin_family = AF_INET,
    .sin_port = this-> portNumber,
    .sin_addr = {
      .s_addr = INADDR_ANY
    },
  };
}

void TcpServer::bindFdToPort(){
  const sockaddr* socketAddressToBind = reinterpret_cast<sockaddr*>(&socketAddress);
  int bindingOutcome = bind(this->sockFd, socketAddressToBind, sizeof(this->socketAddress));
  
  if(bindingOutcome != 0){
    std::cerr<<"Cannot bind to port " << ntohs(this-> portNumber) << "check for error code " << bindingOutcome <<std::endl; 
    this-> isBound = false;
    return;
  }
    this-> isBound = true;
}

void TcpServer::acceptLoop(){
  while (this->isRunning) {
    sockaddr_in clientAddress;
    sockaddr *clientAddressToAccept = reinterpret_cast<sockaddr*>(&clientAddress);
    socklen_t clientAddrLen = sizeof(clientAddress);

    int clientFd = accept(this->sockFd, clientAddressToAccept, &clientAddrLen );

    if (clientFd >= 0 ){
      handleRequest(clientFd);
    }
  }
}

void TcpServer::handleRequest(int clientFd){
}

TcpServer::~TcpServer(){
  this->isRunning = false;
  if(this->sockFd != -1){
    shutdown(this->sockFd,SHUT_RDWR);
  }
  if (this->listener.joinable()){
    this->listener.join();
  }
}

bool TcpServer::startListening(){

  if(!this->isBound) {
    std::cerr << "Server failed to bind to the socket port" << std::endl;
    return false;
  }

  int listeningOutcome = listen(this-> sockFd, MAX_CONNECTIONS);

  if(listeningOutcome){
    std::cerr << "Server failed to listen to the socket port" << std::endl;
    return false;
  }

  this-> isRunning = true;
  this->listener = std::thread([this](){acceptLoop();});
  return true;
}

