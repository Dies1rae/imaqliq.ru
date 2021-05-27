#include "TcpConnector.h"

#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
    std::string _ip = "192.168.1.5";
    int _port = 80;
    TcpConnector test(_ip.c_str(), _port);
    test.InitSend("test");

    if (argc < 2) {
        //file error
	} else if (argc == 2) {
        //server address error
    } else if(argc == 3) {
        //port error
    }

    //get file text
    
    //check file path and name

    //check ip and port

    //push it to address    
    
    return 0;
}
