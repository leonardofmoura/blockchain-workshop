# TASK 2.2: Block

add_executable(block-test 
  block-test.cpp
  blockchain/Block.cpp
  blockchain/Transaction.cpp
  blockchain/TxInput.cpp
  blockchain/TxOutput.cpp
  blockchain/Wallet.cpp
)

# Link logicrypto
target_include_directories(block-test PRIVATE logicrypto)
target_link_libraries(block-test PRIVATE logicrypto)


# TASK 2.3: Node

add_executable(node-test 
  node-test.cpp
  blockchain/Block.cpp
  blockchain/Node.cpp
  blockchain/Transaction.cpp
  blockchain/TxInput.cpp
  blockchain/TxOutput.cpp
  blockchain/Wallet.cpp
)

# Link logicrypto
target_include_directories(node-test PRIVATE logicrypto)
target_link_libraries(node-test PRIVATE logicrypto)
