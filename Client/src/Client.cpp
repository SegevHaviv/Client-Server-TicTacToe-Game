/*
 * Client.cpp
 *
 *  Created on: Oct 18, 2017
 *      Author: user
 */

#include "Client.h"


namespace npl {

Client::Client(ClientHandler* handler) {
	TCPSock = NULL;
	UDPSock = NULL;
	this->handler = handler;
	wantsToPlayWithMe = NULL;
	myTurn = false;
}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

int Client::sendServerCommand(int cmd, const char* buff) {

	int cmdNet = htonl(cmd);

	int res = TCPSock->write((char*) &cmdNet, 4);
	if (res < 4) {
		return -1;
	}
	if (buff != NULL) {
		int len = strlen(buff);
		int lenNet = htonl(len);
		res = TCPSock->write((char*) &lenNet, 4);
		if (res < 4) {
			return -1;
		}
		res = TCPSock->write(buff, len);
		if (res < len) {
			return -1;
		}
	}
	return res;
}

bool Client:: connect(string ip){
	TCPSock = new TCPSocket(ip,MSNGR_PORT);

	if(TCPSock != NULL){
		this->start();
		return true;
	}
		return false;
}

bool Client:: disconnect(){
	sendServerCommand(EXIT, NULL);
	return true;
}

bool Client:: exit(){
	if (TCPSock != NULL) {
		TCPSock->close();
		return true;
	}

	return false;
}

int Client::recvServerCommand() {
	//if the client is not in a game, listen to the tcp socket:
	int cmd;
	int res = TCPSock->recv((char*) &cmd, 4);
	//cout << "TCPMSNClient::recvCommand" << endl;
	cmd = ntohl(cmd);
	if (res < 4) {
		return -1;
	}
	switch (cmd) {
	case EXIT: {
		handler->onClosedSession();
		break;
	}
	case TAKEN_USERNAME: {
		handler->onCommandRecieved(TAKEN_USERNAME);
		break;
	}
	case AVAILABLE_USERNAME: {
		handler->onCommandRecieved(AVAILABLE_USERNAME);
		break;
	}
	case REGISTER_SUCCESSFUL: {
		handler->onCommandRecieved(REGISTER_SUCCESSFUL);
		break;
	}
	case REGISTER_FAIL: {
		handler->onCommandRecieved(REGISTER_FAIL);
		break;
	}
	case LOGIN_SUCCESSFUL: {
		handler->onCommandRecieved(LOGIN_SUCCESSFUL);
		break;
	}
	case LOGIN_FAIL: {
		handler->onCommandRecieved(LOGIN_FAIL);
		break;
	}
	case SHOW_USER_LIST: {
		int size;
		int res = TCPSock->recv((char*) &size, 4);
		if (res < 4) {
			return -1;
		}
		size = htonl(size);
		char* buffer = new char[size];
		res = TCPSock->recv(buffer, size);
		if (res < size) {
			return -1;
		}
		cout << buffer << endl;
		handler->onMessageRecieved(string(buffer));
		break;
	}
	case SEND_REQUEST: {
//		int size;
//		mark = 'X';
//		int res = TCPSock->recv((char*) &size, 4);
//		if (res < 4) {
//			return -1;
//		}
//		size = htonl(size);
//		char* username = new char[size];
//		res = TCPSock->recv(username, size);
//		if (res < size) {
//			return -1;
//		}
//		handler->onOtherPlayerReq(username);
//		wantsToPlayWithMe = username;
		break;
	}
	case START_GAME: {
//		int size;
//		int res = TCPSock->recv((char*) &size, 4);
//		if (res < 4) {
//			return -1;
//		}
//		size = htonl(size);
//		char* port = new char[size];
//		res = TCPSock->recv(port, size);
//		if (res < size) {
//			return -1;
//		}
//		string strport = string(port);
//		int intport = 0;
//		for (int i = 0; i < 5; i++) {
//			intport = intport + ((strport[i]) - 48);
//			intport *= 10; // casting between string to int
//		}
//		intport /= 10;
//		peerPort = intport;
//		if (udpSocket == NULL){
//		udpSocket = new UDPSocket(this->getPort());
//		}
//		square = "0123456789";
//		handler->onCommandRecieved(ACCEPT_REQUEST);
//		handler->startGame = true;
//		handler->inGame=true;
//		isPlaying = true;
//		sleep(1);
		break;
	}
	case REJECT_REQUEST: {
		handler->onCommandRecieved(REJECT_REQUEST);
		break;
	}
	case PRINT_SCOREBOARD: {
		int size;
		int res = TCPSock->recv((char*) &size, 4);
		if (res < 4) {
			return -1;
		}
		size = htonl(size);
		char* buffer = new char[size];
		res = TCPSock->recv(buffer, size);
		if (res < size) {
			return -1;
		}
		cout << string(buffer) << endl;
		break;
	}
	default:
		break;
	}

	return 1;
}


void Client::printScoreBoard() {
	sendServerCommand(REQUEST_SCOREBOARD, NULL);
}

bool Client::isNameTaken(char* userName) {
	handler->onCommandRecieved(0);
	if (sendServerCommand(CHECK_USERNAME, userName))
		return true;
	return false;
}

bool Client::registerUser(char* userName, unsigned enPass) {
	char buff[100];
	sprintf(buff, "%s::%u", userName, enPass);
	if (sendServerCommand(REGISTER, buff))
		return true;
	return false;
}

bool Client::LogInUser(char* userName, unsigned enPass) {
	char buff[100];
	sprintf(buff, "%s::%u", userName, enPass);
	if (sendServerCommand(LOGIN, buff))
		return true;
	return false;
}

void Client::getOnlinePlayers(char* userName) {
	sendServerCommand(SHOW_USER_LIST, userName);
}

void Client::sendRequest(char* userName) {
	sendServerCommand(SEND_REQUEST, userName);
}

void Client::acceptRequest() {
	sendServerCommand(ACCEPT_REQUEST, wantsToPlayWithMe);
	myTurn = true;
}

void Client::rejectRequest() {
	sendServerCommand(REJECT_REQUEST, wantsToPlayWithMe);

}



} /* namespace npl */
