// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// TCPLibrary.h
// TCPLibrary
//
// Precompiled Header for Cross Platform TCP Libraries
//

// Universal
#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <list>


// TCPLibrary
namespace TCPLibrary
{
	typedef void(*CallBack)(const std::string&);
	#define TCP_SOCKET_ERROR -1
	#define TCP_MESSAGE_ERROR -1
}

#include <TCPSocket.h>
#include <TCPSocketUtil.h>
#include <Proxy.h>
#include <Server.h>
#include <Client.h>
