#include "TcpConnector.h"

#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
    std::string _ip = "192.168.1.5";
    int _port = 80;
    std::string file_path;
    std::ostringstream buff;

    if (argc < 3) {
        std::cerr << "Error need more arguments: " << std::endl;
        std::cerr << "filename <\'homepath\'filename.txt>" << std::endl;
        std::cerr << "Server IP address and port number" << std::endl;
	} else if (argc > 4) {
        std::cerr << "Error too much arguments: " << std::endl;
        std::cerr << "filename <\'homepath\'filename.txt>" << std::endl;
        std::cerr << "Server IP address and port number" << std::endl;
    } else if(argc == 4) {
        file_path = argv[1];
        _ip = argv[2];
        try {
            _port = std::stoi(argv[3]);
        } catch (...) {
            std::cerr << "Port number error\n";
            return -1;
        }
    }

    std::ifstream src( file_path, std::ios::binary );
    if(!src.good()){
        std::cerr << "File error\n";
            return -1;
    }

    buff << "SAVE\n";
    buff << file_path.substr(file_path.find_last_of('/') + 1) + '\n';
    buff << src.rdbuf();
    src.close();

    TcpConnector test(_ip.c_str(), _port);
    test.InitSend(buff.str());    
    std::cerr << "Copied one file: " << file_path << "| to " << _ip << ":" << _port << std::endl;

    return 0;
}