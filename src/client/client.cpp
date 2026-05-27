#include <iostream>
#include <unistd.h>
#include <fstream>

#include <config.hpp>

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

int sendtstmsg(int serv_addr) {
    
}

int main(int argc, char** argv) {
    bool is_debug = false;

    if (argc > 0) {
        for (int argi = 1; argi < argc; argi++) {
            char* arg = argv[argi];

            if (arg == std::string("--debug").c_str()) {
                is_debug = true;
            } else if (arg == "smsg") {
                
            } else {
                std::cout << "Is '" << arg << "' argument is undefined." << std::endl;
            }
        }
    }

    Config cfg = ConfigManager::loadConfig("../.env");

    std::string daemon_socket_path = cfg.daemon_socket_path;
    std::string repo = cfg.repo;

    if(daemon_socket_path.empty() && repo.empty()) {
        std::cerr << "Failed to load .env config." << std::endl;
        
        return -1;
    }
    
    std::cout << "You are in ForgeIt: AutoBot CLI. Here u can use:\n" 
    << "\tstatus: general information about bot.\n"
    << "Args:\n" 
    << "\t--debug: for additional text output\n" 
    << "\nGitHub repo: https://github.com/" << repo << ".\n"
    << std::endl;

    if (is_debug) {
        std::cout << "Debbug mode active: you will get extra additional logs." << std::endl;
    }

    int cl_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (cl_fd < 0) {
        std::cerr << "failed to create socket." << std::endl;
        return -1;
    }

    

    return 0;
}