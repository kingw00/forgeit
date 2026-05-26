cmake_minimum_required(VERSION 3.10)
project(ForgeIt VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(forgeit 
    ./main.cpp
    
)

target_include_directories(forgeit PRIVATE include)

find_package(CURL REQUIRED)
target_link_libraries(forgeit PRIVATE CURL::libcurl)