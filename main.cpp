#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

std::string get_config_value(const std::string& key) {
    std::ifstream file("../config.json");
    if(!file.is_open()) return "";

    std::string line;
    while(std::getline(file, line)) {
        if(line.find("\"" + key + "\"") != std::string::npos) {
            size_t start = line.find(":", line.find("\"" + key + "\"")) + 1;
            start = line.find("\"", start) + 1;
            size_t end = line.find("\"", start);
            return line.substr(start, end - start);
        }
    }

    return "";
}

int main(int argc, char** argv) {
    std::cout << "==> ForgeIt: AutoBot started..." << std::endl;

    std::string token = get_config_value("github_token");
    std::string repo = get_config_value("repo");

    if (token.empty() || repo.empty()) {
        std::cerr << "[Error]: Failed to get config values." << std::endl;
        return 1;   
    }

    std::cout << "[Info]: Connectiong to the GitHub repository " << repo << "." << std::endl;

    std::string command = "curl -L "
        "-H \"Accept: application/vnd.github.object\""
        "-H \"Authorization: Bearer " + token + "\" "
        "https://api.github.com/repos/" + repo + "/contents/";

    int res = std::system(command.c_str());

    if(res == 0) {
        std::cout << "[Succes]" << std::endl;
    } else {
        std::cout << "[Failed]" << std::endl;
    }

    return 0;
}