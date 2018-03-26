/*
 * FileTest.h
 *
 *  Created on: Oct 12, 2017
 *      Author: user
 */

#ifndef FILETEST_H_
#define FILETEST_H_

#include "File.h"

class FileTest {
private:
	File* file;
public:
	FileTest();
	virtual ~FileTest();
	bool test();
};

#endif /* FILETEST_H_ */
