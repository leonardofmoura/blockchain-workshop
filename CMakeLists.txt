cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set project name
project(crypto-test VERSION 0.0.2 LANGUAGES CXX)

add_subdirectory(lib/logicrypto)
add_subdirectory(1-cryptography)
add_subdirectory(2.1-simple-block)
add_subdirectory(2.2-blockchain)

