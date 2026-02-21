#include <TcpServerManager.hpp>
#include <TcpServer.hpp>
#include <iostream>

int main(){
  TcpServerManager& serverManger = TcpServerManager::getServerManager();
  int restServerPortNumber = 9000;
  TcpServer& restServer = serverManger.getServerForPort(restServerPortNumber);
  if(restServer.startListening()){
    std::cout<< "REST Server Started on port" << restServerPortNumber << std::endl; 
  }
  
  while(true){
    //TODO: display a list of active servers 
  }
}
