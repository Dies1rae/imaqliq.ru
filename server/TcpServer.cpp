#include "TcpServer.h"

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
#include <istream>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <limits.h>
#include <iterator>
#include <vector>
#include <algorithm> 


int TcpServer::init() {
    svr_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (svr_socket == -1)   {
        std::cerr << "Can't create a socket! Quitting" << std::endl;
        return -1;
    }
    int opt = 1;
    setsockopt(svr_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(svr_port);
    inet_pton(AF_INET, svr_addr, &hint.sin_addr);
    
    bind(svr_socket, (sockaddr*)&hint, sizeof(hint));
    
    listen(svr_socket, SOMAXCONN);
    std::cerr << "server listen on: " << svr_socket << std::endl;
    return 0;
}

int TcpServer::run() {
    bool running = true;
    while (running) {
        FD_ZERO(fd_in);
        FD_ZERO(fd_out);
        FD_ZERO(fd_ex);
        FD_SET(svr_socket, fd_in);  
        for (int i=0;i<cl_so_main.size();i++) {
            FD_SET(cl_so_main[i], fd_in);
        }
        int socketCount = select(FD_SETSIZE, fd_in, NULL, NULL,NULL);
            if (FD_ISSET(svr_socket, fd_in)){
                sockaddr_in client_addr;
                int addrlen = sizeof(client_addr);
                cl_so_main.push_back(accept(svr_socket, (struct sockaddr*)&client_addr, (socklen_t*)&addrlen));
            }
            for (int i=0;i<cl_so_main.size();i++) {
                if (FD_ISSET(cl_so_main[i], fd_in)) {
                    char buf[MAX_BUFFER_SIZE];
                    memset(buf,0, MAX_BUFFER_SIZE);
                    int bytesIn = recv(cl_so_main[i], buf, MAX_BUFFER_SIZE, 0);
                    if (bytesIn <= 0) {
                        close(cl_so_main[i]); 
                        FD_CLR(cl_so_main[i], fd_in);
                        FD_CLR(cl_so_main[i],fd_out);
                        FD_CLR(cl_so_main[i],fd_ex);                            
                        cl_so_main.erase(cl_so_main.begin()+i); 
                    }
                    else{
                        onMessageReceived(cl_so_main[i], buf, bytesIn);
                    }
                }
            }
        }
    return 0;
}

void TcpServer::onMessageReceived(int clientSocket, const char* msg, int length) {
	std::istringstream iss(msg);
	std::vector<std::string> parsed;
	std::string file_name;

    while(!iss.eof()) {
        std::string tmp;
        std::getline(iss, tmp); 
        parsed.push_back(tmp);
    }

    if(!parsed.empty()) {
        if (parsed[0] == "SAVE" && parsed.size() >= 2) {
            file_name = parsed[1];
            std::ofstream dst_("./" + file_name, std::ios::binary);

            for(size_t ptr = 2; ptr < parsed.size(); ptr ++) {
                if(ptr < parsed.size() - 1){
                    dst_ << parsed[ptr] + '\n';
                } else {
                    dst_ << parsed[ptr];
                }
            }
            dst_.close();
        }
    }
}

