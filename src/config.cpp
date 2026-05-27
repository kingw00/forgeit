#include <config.hpp>


std::string ConfigManager::trim(const std::string& str) {
    size_t f = str.find_first_not_of(" \t\r\n");
    if(f == std::string::npos) return "";
    size_t l = str.find_last_not_of(" \t\r\n");
    return str.substr(f, (l - f + 1));
}
Config ConfigManager::loadConfig(const std::string& fpath) {
    Config config;
    std::ifstream file(fpath);

    if(!file.is_open()) {
        std::cerr << "[Config Error]: Failed to open config." << std::endl;
        return config;
    }

    std::string line;
    while(std::getline(file, line)) {
        line = trim(line);

        if(line.empty() || line == "#") continue;

        size_t d_pos = line.find('=');
        if(d_pos == std::string::npos) continue;

        std::string key = line.substr(0, d_pos);
        std::string val = line.substr(d_pos + 1);

        if (key == "github_token") {
            config.github_token = val;
        } else if (key == "repo") {
            config.repo = val;
        }
    }

    file.close();

    if(!config.github_token.empty() && !config.repo.empty()) {
        config.is_valid = true;
    } 

    return config;
}