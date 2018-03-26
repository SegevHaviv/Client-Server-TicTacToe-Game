/*
 * File.h
 *
 *  Created on: Oct 12, 2017
 *      Author: user
 */

#ifndef SRC_FILE_H_
#define SRC_FILE_H_

#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

class File {
private:
	ofstream out;
	ifstream in;

public:
	File(char* fileName);
	bool isValid(const char* userName,const char* password); // Checking if the details are correct.
	bool isExist(const char* userName); // Checking if a user exists already.
	bool insertUser(const string& userName,const string& password); // Inserting a user to the file.
	virtual ~File();
};

#endif /* SRC_FILE_H_ */
