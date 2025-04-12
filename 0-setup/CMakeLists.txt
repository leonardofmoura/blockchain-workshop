cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(test-setup VERSION 0.0.1 LANGUAGES CXX)

# Import libsodium
find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)

# Add executable
add_executable(test-setup test-setup.cpp)


# Set include directories
target_include_directories(test-setup PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR} 
  ${SODIUM_INCLUDE_DIRS}
)

# Link with libsodium
target_link_libraries(test-setup PRIVATE ${SODIUM_LIBRARIES})

