#include_directories ("${PROJECT_SOURCE_DIR}/TCPLibrary/Src/")
#include_directories ("${PROJECT_SOURCE_DIR}/TCPLibrary/Inc/")

add_library(TCP Src/Proxy.cpp Src/Server.cpp Src/Client.cpp Src/TCPSocketCross.cpp Src/TCPSocketLinux.cpp Src/TCPSocketUtilCross.cpp Src/TCPSocketUtilLinux.cpp Src/TCPLibrary.cpp)
