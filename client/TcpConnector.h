#pragma once

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
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <limits.h>
#include <vector>
#include <algorithm>

#pragma comment (lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE (49152)
#ifndef TCPSERVER_H
#define TCPSERVER_H

class TcpConnector {
public:
    TcpConnector(const char * ipAddress, int port) {
        svr_addr = ipAddress;
        svr_port = port;
        fd_in = new fd_set;
        fd_out = new fd_set;
        fd_ex = new fd_set;
    }
    int InitSend(const std::string& file);
private:
    const char                * svr_addr;
    int                         svr_port;
    int                         svr_socket;
    fd_set                      * fd_in;
    fd_set                      * fd_out;
    fd_set                      * fd_ex;
};

#endif /* TCPSERVER_H */