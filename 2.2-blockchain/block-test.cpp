#include "Block.hpp"
#include "ByteVector.hpp"
#include "Wallet.hpp"
#include "logicrypto.hpp"
#include <iostream>
#include <memory>
#include <ostream>
#include <sodium.h>
#include <cstring>
#include <stdexcept>

int main() {
  logicrypto::init();

  Wallet test_wallet = Wallet("my test wallet");
  Wallet send_wallet = Wallet("my second test wallet");

  // create genesis Block
  std::shared_ptr<Block> genesis = std::make_shared<Block>();

  std::cout << "My Blockchain" << std::endl;
 
  auto coinbase_in_out = std::make_shared<TxOutput>(500,test_wallet.getSendAddress());
  auto coinbase_in = std::make_shared<TxInput>(logicrypto::ByteVector(32),0,coinbase_in_out);

  auto coinbase = std::make_shared<Transaction>(coinbase_in);
  coinbase->addOutput(500,test_wallet.getSendAddress());

  if (!coinbase->unlock(test_wallet.getTransactionSignature(coinbase->getSignData()))) {
    throw std::runtime_error("Signature not valid");
  }
  coinbase->finalize();


  genesis->addTransaction(coinbase);
  genesis->mine();
  genesis->print();
  std::cout << std::endl;

  std::shared_ptr<Block> first = std::make_shared<Block>(genesis);


  auto first_transaction_in = std::make_shared<TxInput>(coinbase->getTxid(),0,coinbase->getOutput(0));
  auto first_transaction = std::make_shared<Transaction>(first_transaction_in);
  first_transaction->addOutput(450,send_wallet.getSendAddress());
  first_transaction->unlock(test_wallet.getTransactionSignature(first_transaction->getSignData()));
  first_transaction->finalize();
  first->addTransaction(first_transaction);

  auto coinbase_in_out2 = std::make_shared<TxOutput>(500,test_wallet.getSendAddress());
  auto coinbase_in2 = std::make_shared<TxInput>(logicrypto::ByteVector(32),0,coinbase_in_out2);
  auto coinbase2 = std::make_shared<Transaction>(coinbase_in2);
  coinbase2->addOutput(500,test_wallet.getSendAddress());
  coinbase2->unlock(test_wallet.getTransactionSignature(coinbase2->getSignData()));
  coinbase2->finalize();
  first->addTransaction(coinbase);

  first->mine();
  first->print();
  std::cout << std::endl;

  return 0;
}

