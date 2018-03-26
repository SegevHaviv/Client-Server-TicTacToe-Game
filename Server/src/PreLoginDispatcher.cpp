/*
 * PreLoginDispatcher.cpp
 *
 *  Created on: Oct 13, 2017
 *      Author: user
 */

#include "PreLoginDispatcher.h"

namespace npl {

PreLoginDispatcher::PreLoginDispatcher(PreDispatcherHandler* handler) {
	this->handler = handler;
	file = new File((char*) "Users.txt");
	running = true;
	currSock = NULL;

}

PreLoginDispatcher::~PreLoginDispatcher() {
	running = false;
}

bool PreLoginDispatcher::login(char* userName, char* password) {
	Guard guard(&mutex1);
// TODO hash password
	if (file->isValid(userName, password))
		return true;
	return false;
}

int PreLoginDispatcher::sendCommand(TCPSocket* socket, const char* content,
		int command) {
	int commandNew = htonl(command);
	int result = socket->write((char*) &commandNew, 4);
	if (result < 0) {
		return -1;
	}
	if (content != NULL) {
		int len = strlen(content);
		int lenNew = htonl(len);
		result = socket->write((char*) &lenNew, 4);
		if (result < 0)
			return -1;
		result = socket->write(content, len);
		if (result < 0)
			return -1;
	}
	return result;
}

void PreLoginDispatcher::addPeer(TCPSocket* peer) {
	Guard guard(&mutex2);
	string peerAddressAndPort = peer->toString();
	cout << "New peer added to the OpenedDispatcher: " << peerAddressAndPort
			<< endl;
//Checking if the peer is already connected
	if (onlinePeers.find(peerAddressAndPort) == onlinePeers.end()) {
		listener.add(peer);
		onlinePeers[peerAddressAndPort] = peer;
	}
}

string PreLoginDispatcher::hash(string unHashedPassword) {
	return unHashedPassword;
}

void PreLoginDispatcher::updateListener() {
	vector<TCPSocket*> vector;
	for (map<string, TCPSocket *>::iterator it = this->onlinePeers.begin();
			it != this->onlinePeers.end(); ++it) {
		vector.push_back(it->second);
	}
	this->listener.add(vector);
}

bool PreLoginDispatcher::Register(char* userName, char* password) {
	Guard guard(&mutex1);
	if (file->isExist(userName))
		return false;

	file->insertUser(userName, password);
	return true;
}

void PreLoginDispatcher::run() {

	while (running) {
		currSock = listener.listen();
		if (currSock == NULL) {
			continue;
		}
		int command;

		currSock->recv((char*) &command, 4);
		command = htonl(command);

		switch (command) {
//		case CHECK_USERNAME: {
//
//			break;
//		}

		case REGISTER: {
			int size;
			currSock->recv((char*) &size, 4);
			size = htonl(size);
			char userInfo[size + 1];
			currSock->recv(userInfo, size);
			string str = userInfo;

			string userName = str.substr(0, str.find(" "));
			string password = str.substr(str.find(" ") + 1, str.length());

			password = hash(password.c_str());

			if (file->insertUser(userName, password)) {
				sendCommand(currSock, NULL, REGISTER_SUCCESSFUL);
			} else {
				sendCommand(currSock, NULL, REGISTER_FAIL);
			}

			break;
		}

		case LOGIN: {
			int size;
			currSock->recv((char*) &size, 4);
			size = htonl(size);
			char userInfo[size + 1];
			currSock->recv(userInfo, size);
			string str = userInfo;

			string userName = str.substr(0, str.find(" "));
			string password = str.substr(str.find(" ") + 1, str.length());

			password = hash(password);

			if (file->isValid(userName.c_str(), password.c_str())) {
				sendCommand(currSock, NULL, LOGIN_SUCCESSFUL);
			} else {
				sendCommand(currSock, NULL, LOGIN_FAIL);
			}
		}
		case EXIT: {
			onlinePeers.erase(onlinePeers.find(currSock->toString()));
			sleep(1);
			cout << "deleting open" << endl;
			//updating listener every time we delete sockets:
			updateListener();
			sleep(1);
			break;
		}
		default: {
			cout << "Invaild Input" << endl;
			break;
		}
		}

	}
}

} /* namespace npl */
