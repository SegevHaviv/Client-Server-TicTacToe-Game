/*
 * TcpSocketTest.cpp
 *
 *  Created on: Mar 13, 2016
 *      Author: user
 */

#include "TcpSocketTest.h"
#include <pthread.h>
#include <unistd.h>

using namespace npl;

bool TcpSocketTest::test(){
	start();
	sleep(1);
	TCPSocket* client = new TCPSocket("127.0.0.1",9586);
	string msg = "12345678901234567890";
	client->send(msg);
	cout<<"client sent: "<<msg<<endl;
	char buff[1024];
	int rc = client->recv(buff,sizeof(buff));
	buff[rc] = '\0';
	cout<<"client recv: "<<buff<<endl;

	client->close();
	delete client;

	if(rc == (int)msg.size()){
		if(strcmp(msg.c_str(),buff) == 0){
			return true;
		}
	}
	cerr<<"TCP test failed"<<endl;
	waitForThread();
	return false;
}

void TcpSocketTest::run(){
	TCPSocket* server = new TCPSocket(9586);
	TCPSocket* peer = server->listenAndAccept();
	cout<<"server got peer connection"<<endl;

	char buff[1024];
	int rc = peer->recv(buff,sizeof(buff));

	buff[rc] = '\0';
	cout<<"server recv: "<<buff<<endl;

	peer->send(buff);
	cout<<"server sent: "<<buff<<endl;

	peer->close();
	server->close();
	delete peer;
	delete server;
}
