#include <iostream>

int main(int argc, char** argv) {
    bool is_debug = false;

    if (argc > 0) {
        for (int argi = 0; argi < argc; argi++) {
            char* arg = argv[argi];

            if (arg == "--debug") {
                is_debug = true;
            }
        }
    }
    
    std::cout << "[ForgeIt Info]: Starting ForgeIt: AutoBot." << std::endl;

    return 0;
}