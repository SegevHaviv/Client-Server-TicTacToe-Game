/*
 * ServerManager.cpp
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#include "Manager.h"

namespace npl {

Manager::Manager() {
	server = new Server(this);
	PreDispatcher = new PreLoginDispatcher(this);
	PostDispatcher = new PostLoginDispatcher();

}

void Manager::movePeerToOD(TCPSocket* peer) {
	PreDispatcher->addPeer(peer);
}

void Manager::movePeerToLD(char* user, TCPSocket* peer){
	PostDispatcher->addPeer(user, peer);
}

Manager::~Manager() {
	delete server;
	delete PreDispatcher;
	delete PostDispatcher;
}

} /* namespace npl */
