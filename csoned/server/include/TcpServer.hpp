#pragma once

#include <thread>
#include <memory>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>

class TcpServer {

  friend std::default_delete<TcpServer>;
  friend class TcpServerManager;

  // A lookup of servers by ports
  static const int MAX_CONNECTIONS = 10;

  sockaddr_in socketAddress;
  in_port_t portNumber;
  std::thread listener;
  bool isRunning;
  bool isBound;
  int sockFd;

  TcpServer(int port);

  void bindFdToPort();
  void acceptLoop();
  void handleRequest(int clientFd);

  TcpServer(const TcpServer &) = delete;
  TcpServer(TcpServer &&) = delete;
  TcpServer &operator=(const TcpServer &) = delete;
  TcpServer &operator=(TcpServer &&) = delete;
  ~TcpServer();


public:
  bool startListening();
};
