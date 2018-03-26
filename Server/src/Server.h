/*
 * Server.h
 *
 *  Created on: Oct 12, 2017
 *      Author: user
 */

#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_
#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"
#include "MThread.h"
#include <iostream>

namespace npl {
class ServerHandler {

};

class Server : public MThread{
private:
	TCPSocket* serverSock;
	ServerHandler* handler;
	bool isRunning;

public:
	void run();
	Server(ServerHandler* handler);
	virtual ~Server();
};

} /* namespace npl */

#endif /* SRC_SERVER_H_ */
