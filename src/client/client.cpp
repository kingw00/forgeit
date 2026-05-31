#include <iostream>
#include <unistd.h>
#include <fstream>

#include <config.hpp>

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

struct Event {
    
};

int main(int argc, char** argv) {
    bool is_debug = false;

    if (argc > 0) {
        for (int argi = 1; argi < argc; argi++) {
            char* arg = argv[argi];

            if (arg == std::string("--debug").c_str()) {
                is_debug = true;
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

    char buffer[4096];
    
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

    int serv_fd;
    sockaddr_un serv_addr;
    serv_addr.sun_family = AF_UNIX;
    
    memcpy(serv_addr.sun_path, daemon_socket_path.c_str(), sizeof(daemon_socket_path));

    serv_fd = connect(cl_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    if(serv_fd < 0) {
        std::cerr << "Failed to connect to the ForgeIt daemon socket." << std::endl;

        close(cl_fd);

        return -1;
    }
    
    std::cout << "Connected to the daemon socket." << std::endl;

    while(1) {
        if (serv_fd < 0) {
            continue;
        }

        // Sending test message.
        const char* msg = "Hello from client.";

        if(strlen(msg) + 1 > sizeof(buffer)) {
            memcpy(buffer, msg, sizeof(buffer) - 1);
            buffer[sizeof(buffer)] = '\0';
        } else {
            memcpy(buffer, msg, strlen(msg) + 1);
        }

        send(cl_fd, buffer, sizeof(buffer), 0);

        // Closing daemon file descriptor.
        close(serv_fd);
    }

    if (serv_fd > 0) {
        close(serv_fd);
    }

    return 0;
}