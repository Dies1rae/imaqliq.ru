#include "TcpConnector.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <netdb.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <limits.h>
#include <iterator>
#include <vector>
#include <algorithm> 

int TcpConnector::InitSend (const std::string& file) {
    svr_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (svr_socket == -1)   {
        std::cerr << "Can't create a socket! Quitting" << std::endl;
        return -1;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(svr_port);
    inet_pton(AF_INET, svr_addr, &hint.sin_addr);
    //hint.sin_addr = *((struct in_addr *)&svr_addr);
    //bzero(&(hint.sin_zero), 8);


    if(connect(svr_socket, (sockaddr*) &hint, sizeof(hint)) == -1) {
        std::cerr << "connected error" << std::endl;
        return -1;
    } else {
        std::cerr << "connected ok" << std::endl;
        send(svr_socket, file.c_str(), file.size(), 0);
        exit(1);
    }
    close(svr_socket);
    return 0;
}
