cmake_minimum_required(VERSION 3.16)

project(logicrypto VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Import libsodium
find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)

# Define the library
add_library(logicrypto SHARED)

# Add sources and includes
file(GLOB_RECURSE SOURCES ./*.cpp)
file(GLOB_RECURSE HEADERS ./*.hpp)

# Add sources to the library
target_sources(logicrypto PRIVATE ${SOURCES} ${HEADERS})

# Set include directories
target_include_directories(logicrypto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SODIUM_INCLUDE_DIRS})

# Link with libsodium
target_link_libraries(logicrypto PRIVATE ${SODIUM_LIBRARIES})

