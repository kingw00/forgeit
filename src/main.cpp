#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include <config.hpp>

int main(int argc, char** argv) {
    std::cout << "==> ForgeIt: AutoBot started..." << std::endl;

    Config config = ConfigManager::loadConfig("../.env");

    if (!config.is_valid) {
        std::cerr << "[Error]: Config not valid." << std::endl;

        return 1;
    }

    std::string token = config.github_token;
    std::string repo = config.repo;

    std::cout << "[Info]: Config loaded." << std::endl;

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