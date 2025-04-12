# PART 1: CRYPTOGRAPHY

add_executable(crypto-test crypto-test.cpp)

# Link logicrypto
target_include_directories(crypto-test PRIVATE logicrypto)
target_link_libraries(crypto-test PRIVATE logicrypto)

