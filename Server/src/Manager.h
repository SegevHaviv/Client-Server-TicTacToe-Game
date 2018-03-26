/*
 * Manager.h
 *
 *  Created on: Oct 16, 2017
 *      Author: user
 */

#ifndef SRC_MANAGER_H_
#define SRC_MANAGER_H_

#include "TCPSocket.h"

#include "PreLoginDispatcher.h"
#include "PostLoginDispatcher.h"
#include "Server.h"

namespace npl {

class Manager : public ServerHandler,PreDispatcherHandler {
	Server* server;
	PreLoginDispatcher* PreDispatcher;
	PostLoginDispatcher* PostDispatcher;

public:
	Manager();
	void movePeerToOD(TCPSocket* peer);
	void movePeerToLD(char* user, TCPSocket* peer);
	virtual ~Manager();
};
} /* namespace npl */

#endif /* SRC_MANAGER_H_ */
