#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <filesystem>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <config.hpp>

int main() {
    Config cfg = ConfigManager::loadConfig("../.env");

    std::string daemon_socket_path = cfg.daemon_socket_path;
    std::string repo = cfg.repo;
    std::string token = cfg.github_token;

    if(daemon_socket_path.empty() || repo.empty() || token.empty()) {
        std::cerr << "Failed to read config file." << std::endl;
        return -1;
    }

    std::string log_path = "/tmp/forgeit_daemon.log";

    std::cout << "Starting ForgeIt daemon..." << std::endl;

    std::cout << "Creating temp log files. Path: `" << log_path << "`." << std::endl;

    std::filesystem::remove(log_path);
    std::cout << "Old log file has been deleted." << std::endl;

    std::ofstream logs;
    logs.open(log_path);
    if(!logs.is_open()) {
        std::cerr << "Failed to open logs file." << std::endl;
        return -1;
    }

    int socket_fd;
    sockaddr_un addr;

    char buffer[4096];

    unlink(daemon_socket_path.c_str());
    std::memset(&addr, 0, sizeof(sockaddr_un));
    
    addr.sun_family = AF_UNIX;
    
    memcpy(addr.sun_path, daemon_socket_path.c_str(), daemon_socket_path.length());

    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        logs << "Failed to create socket." << std::endl;
        return -1;
    }

    if (bind(socket_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        std::cout << "Failed to bind socket." << std::endl;
        logs << "Failed to bind socket." << std::endl;
        return -1;
    }

    std::cout << "Socket binded. File: " << daemon_socket_path << "." << std::endl;
    logs << "Socket binded. File: " << daemon_socket_path.c_str() << "." << std::endl;

    if(listen(socket_fd, 1) < 0) {
        std::cerr << "Failed to listen incoming requests." << std::endl;
        return -1;
    }

    while(1) {
        int cl_fd = accept(socket_fd, nullptr, nullptr);

        if(cl_fd < 0) {
            continue;
        }

        std::cout << "Client connected. Client file Discriptor: " << cl_fd << "." << std::endl;

        ssize_t bytes_read = read(cl_fd, buffer, sizeof(buffer) - 1);     
        if(bytes_read == 0) {
            std::cout << "Client " << cl_fd << " disconnected." << std::endl;
            logs << "Client " << cl_fd << " disconnected." << std::endl;
            close(cl_fd);
        } else if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            std::string cl_msg(buffer);

            std::cout << "[" << cl_fd << "]: " << cl_msg << std::endl;
            logs << "[" << cl_fd << "]: " << cl_msg << std::endl;
        } else {
            std::cout << "Failed to read client n." << cl_fd << " socket." << std::endl;
            close(cl_fd);
        }

        close(cl_fd);
    }


    close(socket_fd);
    std::filesystem::remove(daemon_socket_path);

    logs.close();

    return 0;
}