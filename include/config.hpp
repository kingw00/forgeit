#pragma once
#include <fstream>
#include <string>
#include <iostream>

struct Config {
    std::string github_token;
    std::string repo;
    bool is_valid = false;
};

class ConfigManager {
private: 
    static std::string trim(const std::string& str);
    
public:
    static Config loadConfig(const std::string& fpath);
};