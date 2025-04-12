#include "Transaction.hpp"
#include "TxInput.hpp"
#include "TxOutput.hpp"
#include "logicrypto.hpp"
#include <iostream>
#include <memory>
#include <sodium.h>
#include <cstring>

int main() {
  logicrypto::init();

  auto coinbase_in_out = std::make_shared<TxOutput>(500,logicrypto::ByteVector(4));
  std::cout << coinbase_in_out->toString();

  auto coinbase_in = std::make_shared<TxInput>(logicrypto::ByteVector(32),0,coinbase_in_out);
  
  auto coinbase = std::make_shared<Transaction>(coinbase_in);
  coinbase->addOutput(300,logicrypto::ByteVector(32));

  std::cout << coinbase->toString();


  coinbase->addOutput(100, logicrypto::ByteVector(32));
  coinbase->finalize();

  std::cout << coinbase->toString();
  
  return 0;
}

