/*
 * Client.h
 *
 *  Created on: Oct 18, 2017
 *      Author: user
 */

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include "TCPSocket.h"
#include "UDPSocket.h"
#include "MThread.h"
#include "TCPMessengerProtocol.h"

#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <string.h>

namespace npl {

class ClientHandler {
public:
	bool startGame;
	bool inGame;
	//handles with the recieved command
	virtual void onCommandRecieved(int cmd)=0;
	//handles the message we got
	virtual void onMessageRecieved(string message)=0;
	//the session is open, gets the ip and port of the other side
	virtual void onOpenSession(string ip, int port)=0;
	//the session is close
	virtual void onClosedSession()=0;
	//other player requests to connect me
	virtual void onOtherPlayerReq(char* username)=0;

	virtual ~ClientHandler();

};

class Client: public MThread {
	ClientHandler* handler;
	TCPSocket* TCPSock;
	UDPSocket* UDPSock;
	char* wantsToPlayWithMe;
	bool myTurn;


public:
	Client(ClientHandler* handler);
	virtual ~Client();

	int sendServerCommand(int cmd, const char* buff);

	int recvServerCommand();
	bool connect(string ip);
	bool disconnect();
	bool exit();

	void printScoreBoard();
	bool isNameTaken(char* userName);
	bool registerUser(char* userName, unsigned enPass);
	bool LogInUser(char* userName, unsigned enPass);
	void getOnlinePlayers(char* userName);

	void sendRequest(char* userName);
	void acceptRequest();
	void rejectRequest();

	void run();
};

} /* namespace npl */

#endif /* SRC_CLIENT_H_ */
