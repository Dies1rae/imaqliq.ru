#include "TcpServer.h"

#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char* argv[]) {
    std::string _ip = "0.0.0.0";
    int _port = 80;

    if (argc < 2) {
		std::cout << "Daemon start with basic parametrs" << std::endl;
        std::cout << _ip << " " << _port << std::endl;
        std::cout << "Process PID: " << getpid() + 1 << std::endl;
	} else if (argc == 2) {
        _ip = argv[1];
        std::cout << "Daemon start with basic parametrs" << std::endl;
        std::cout << _ip << " " << _port << std::endl;
        std::cout << "Process PID: " << getpid() + 1 << std::endl;
    } else if(argc == 3) {
        _ip = argv[1];
        try {
            _port = std::stoi(argv[2]);
        } catch (...) {
            std::cerr << "Port number error\n";
            return -1;
        }
        _ip = argv[1];
        std::cout << "Daemon start with basic parametrs: " << std::endl;
        std::cout << _ip << " " << _port << std::endl;
        std::cout << "Process PID: " << getpid() + 1 << std::endl;
    } else {
        std::cerr << "To much args. Need IpAddr and Port number\n";
        return -1;
    }

    TcpServer mainS(_ip.c_str(),_port);
    std::cout << "Server started" << std::endl;
    if(mainS.init() != 0){
        std::cerr << "Some error with server INIT() " << mainS.init() << std::endl;
        return -1;
    }
    
    pid_t c_pid = fork();
    if (c_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (c_pid > 0) {
        sleep(1);
        exit(0);
    }

    setsid();
    mainS.run();
    return 0;
}