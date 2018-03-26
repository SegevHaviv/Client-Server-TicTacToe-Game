/*
 * File.cpp
 *
 *  Created on: Oct 12, 2017
 *      Author: user
 */

#include "File.h"

using namespace std;

File::File(char* fileName) {
	  out.open(fileName, std::ios_base::app);
	  in.open(fileName, std::ifstream::in);
}

File::~File() {
	in.close();
	out.close();
}

bool File::insertUser(const string& userName,const string& password){
	out << userName + ":" + password << endl;
	if(isExist(userName.c_str()))
		return true;
	return false;
}

bool File:: isValid(const char* userName,const char* password){
	string entireLine,currUser,currPass;

	while(in.good()){
		getline(in,entireLine);
		currUser = entireLine.substr(0, entireLine.find(":"));
		if(strcmp(userName,currUser.c_str()) == 0){
			currPass = entireLine.substr(entireLine.find(":") + 1, entireLine.length());
			if(strcmp(password,currPass.c_str()) == 0){
				return true;
			}
		}
	}
	return false;
}

bool File:: isExist(const char* userName){
	string entireLine;
	string currUser;

	while(in.good()){
		getline(in,entireLine);
		currUser = entireLine.substr(0, entireLine.find(":"));
		if(strcmp(userName,currUser.c_str()) == 0){
			return true;
		}
	}
	return false;
}


