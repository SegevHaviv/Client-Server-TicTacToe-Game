/*
 * FileTest.cpp
 *
 *  Created on: Oct 12, 2017
 *      Author: user
 */

#include "FileTest.h"

FileTest::FileTest() {
	file = new File("FileForTest.txt");
}

FileTest::~FileTest() {

}

bool FileTest:: test(){
	//TODO : Clearing the content of the file before checking it.

	file->insertUser((char*)"Daniel", "222333");

	if(!(file->isValid((char*)"Daniel", (char*)"222333")))
		return false;

	if(!(file->isExist((char*)"Daniel")))
		return false;

	return true;
}

