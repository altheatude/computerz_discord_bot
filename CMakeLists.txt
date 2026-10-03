cmake_minimum_required(VERSION 3.16)

project(SLCBot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bot
    src/main.cpp
)

find_package(dpp CONFIG REQUIRED)

target_include_directories(bot PRIVATE include/laserpants/dotenv)
target_link_libraries(bot PRIVATE dpp::dpp)