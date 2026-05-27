cmake_minimum_required(VERSION 3.10)
project(ForgeIt VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGX} -O3 -Wall -Wextra")

add_executable(forgeit_client
    src/client/client.cpp
    src/config.cpp
    src/config.cpp
)

add_executable(forgeit_daemon
    src/daemon/daemon.cpp
    src/daemon/socket.cpp
    src/daemon/utils.cpp
    src/config.cpp
)

include_directories(include)

find_package(CURL REQUIRED)
target_link_libraries(forgeit_daemon PRIVATE CURL::libcurl)
