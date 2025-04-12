# TASK 2.1: SimpelBlock

add_executable(simple-block simple-blockchain.cpp SimpleBlock.cpp)

# Link logicrypto
target_include_directories(simple-block PRIVATE logicrypto)
target_link_libraries(simple-block PRIVATE logicrypto)

