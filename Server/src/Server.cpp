/*
 * Server.cpp
 *
 *  Created on: Oct 12, 2017
 *      Author: user
 */

#include "Server.h"

using namespace std;

namespace npl {

Server::Server(ServerHandler* handler) {
	this->handler = handler;
	this->isRunning = true;
	this->serverSock = new TCPSocket(MSNGR_PORT);
	this->start();

}

void Server::run() {
	while (isRunning == true) {
		TCPSocket* peerSocket = serverSock->listenAndAccept();

		cout << peerSocket << "has connected" << endl;

		//handler->movePeerToOD(peerSocket);
	}
}

Server::~Server() {
	serverSock->close();
	//delete handler;
}

} /* namespace npl */
