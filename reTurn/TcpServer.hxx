#ifndef TCP_SERVER_HXX
#define TCP_SERVER_HXX

#include <asio.hpp>
#ifdef USE_SSL
#include <asio/ssl.hpp>
#endif
#include <string>
#include "TcpConnection.hxx"
#include "ConnectionManager.hxx"
#include "RequestHandler.hxx"

namespace reTurn {

class TcpServer
{
public:
  // noncopyable
  TcpServer(const TcpServer&) = delete;
  TcpServer& operator=(const TcpServer&) = delete;

  /// Create the server to listen on the specified TCP address and port
  explicit TcpServer(asio::io_service& ioService, RequestHandler& rqeuestHandler, const asio::ip::address& address, unsigned short port);

  void start();

private:
  /// Handle completion of an asynchronous accept operation.
  void handleAccept(const asio::error_code& e);

  /// The io_service used to perform asynchronous operations.
  asio::io_service& mIOService;

  /// Acceptor used to listen for incoming connections.
  asio::ip::tcp::acceptor mAcceptor;

  /// The connection manager which owns all live connections.
  ConnectionManager mConnectionManager;

  /// The next connection to be accepted.
  ConnectionPtr mNewConnection;

  /// The handler for all incoming requests.
  RequestHandler& mRequestHandler;
};

}

#endif 


/* ====================================================================

 Copyright (c) 2007-2008, Plantronics, Inc.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are 
 met:

 1. Redistributions of source code must retain the above copyright 
    notice, this list of conditions and the following disclaimer. 

 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution. 

 3. Neither the name of Plantronics nor the names of its contributors 
    may be used to endorse or promote products derived from this 
    software without specific prior written permission. 

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ==================================================================== */
