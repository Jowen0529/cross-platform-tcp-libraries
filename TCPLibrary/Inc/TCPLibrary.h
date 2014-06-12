// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// TCPLibrary.h
// TCPLibrary
//
// Precompiled Header for TCP Project
//

#include <TCPBuild.h>


// Networking
#if WINDOWS_PLATFORM

#include <WinSock2.h>

#elif LINUX_PLATFORM

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>

#endif


// Universal
#define TCP_SOCKET_ERROR -1
#define TCP_MESSAGE_ERROR -1
#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <list>


// TCPLibrary
#include <TCPSocket.h>
#include <TCPSocketUtil.h>
#include <Proxy.h>
#include <Server.h>
#include <Client.h>
