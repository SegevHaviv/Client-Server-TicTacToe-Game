/*
 * PreLoginDispatcher.h
 *
 *  Created on: Oct 13, 2017
 *      Author: user
 */

#ifndef SRC_PRELOGINDISPATCHER_H_
#define SRC_PRELOGINDISPATCHER_H_

#include "MThread.h"
#include "MTCPListener.h"
#include "File.h"
#include "TCPSocket.h"
#include <map>
#include "Guard.h"
#include "TCPMessengerProtocol.h"
#include <unistd.h>

namespace npl {

class PreDispatcherHandler {
public:
	virtual void movePeerToPostD(char* user, TCPSocket* peer)=0;
	virtual ~PreDispatcherHandler();
};

class PreLoginDispatcher : public MThread {
private:

	File* file;

	PreDispatcherHandler* handler;
	TCPSocket* currSock;

	bool running;
	pthread_mutex_t mutex1, mutex2;
	MTCPListener listener;

	map<string, TCPSocket*> onlinePeers;

public:

	bool login(char* userName, char* hashedPassword);
	string hash(string unHashedPassword);
	bool Register(char* userName, char* password);
	void updateListener();
	void addPeer(TCPSocket* peer);
	int sendCommand(TCPSocket* socket, const char* content,int command);
	void run();

	PreLoginDispatcher(PreDispatcherHandler* handler);
	virtual ~PreLoginDispatcher();
};

} /* namespace npl */

#endif /* SRC_PRELOGINDISPATCHER_H_ */
