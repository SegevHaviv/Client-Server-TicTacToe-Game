
#include "UdpSocketTest.h"
#include "TcpSocketTest.h"
#include "MTCPListenerTest.h"
#include "FileTest.h"
#include <fstream>

using namespace std;
using namespace npl;

int main() {
	bool passFlag = true;
	UdpSocketTest udpTest;
	if (!udpTest.test()){
		cerr<<endl<<endl<<"UDP test failed"<<endl;
		passFlag = false;
	}else{
		cout<<endl<<"UDP test pass"<<endl;
	}
	cout<<endl<<endl<<endl;

	TcpSocketTest tcpTest;
	if(!tcpTest.test()){
		cerr<<endl<<endl<<"TCP test failed"<<endl;
		passFlag = false;
	}else{
		cout<<endl<<"TCP test pass"<<endl;
	}
	cout<<endl<<endl<<endl;

	MTCPListenerTest mtcpTest;
	if(!mtcpTest.test()){
		cerr<<endl<<endl<<"MTCPListener test failed"<<endl;
		passFlag = false;
	}else{
		cout<<endl<<"MTCPListener test pass"<<endl;
	}
	FileTest fileTest;
	if(!fileTest.test()){
		cerr<<endl<<endl<<"File test failed"<<endl;
		passFlag = false;
	}else{
		cout<<endl<<"File test pass"<<endl;
	}


	if(passFlag){
		cout<<endl<<endl<<"**** TEST PASS ****"<<endl;
	}else{
		cerr<<endl<<endl<<"**** TEST FAIL ****"<<endl;
	}
}

