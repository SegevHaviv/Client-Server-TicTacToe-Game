/*
 * PostLoginDispatcher.h
 *
 *  Created on: Oct 13, 2017
 *      Author: user
 */

#ifndef SRC_POSTLOGINDISPATCHER_H_
#define SRC_POSTLOGINDISPATCHER_H_

#include "TCPSocket.h"
#include "MThread.h"
#include <map>
#include <set>
#include "MTCPListener.h"
#include <unistd.h>
#include "TCPMessengerProtocol.h"
#include "Guard.h"
#include <fstream>
#include <sstream>
#include <string.h>
#include <algorithm>
namespace npl {

class PostLoginDispatcher: public MThread {

	MTCPListener listener;
	map<string, TCPSocket*> onlinePeers;
	set<string> inGamePlayers;
	map<string, int> namesAndScores;
	pthread_mutex_t mutex;
	pthread_mutex_t mutex2;
	TCPSocket* currSock;
	bool isAlive;
	string newName;
	void updateListener();
	int sendCommand(TCPSocket* socket, const char* content, int command);

public:
	PostLoginDispatcher();
	virtual ~PostLoginDispatcher();

	map<string, int> getAllScores();
	void pushAllScores(map<string, int> namesAndScores);
	void addPeer(char* user, TCPSocket* peer);
	void close();
	void run();

};

} /* namespace npl */

#endif /* SRC_POSTLOGINDISPATCHER_H_ */
