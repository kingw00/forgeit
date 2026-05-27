#include <iostream>

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
    
    std::cout << "You are in ForgeIt: AutoBot CLI. Here u can use:\n\tstatus: general information about bot.\nArgs:\n\t--debug: for additional text output" << std::endl;

    if (is_debug) {
        std::cout << "Debbug mode active: you will get extra additional logs." << std::endl;
    }

    return 0;
}