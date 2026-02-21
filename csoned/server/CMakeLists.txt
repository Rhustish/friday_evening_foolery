cmake_minimum_required(VERSION 3.21)
project(CsOneDServer)

add_executable(CsOneDServer)

target_sources(CsOneDServer PRIVATE 
  src/TcpServer.cpp
  src/TcpServerManager.cpp
  src/main.cpp
)
target_include_directories(CsOneDServer PRIVATE include)
