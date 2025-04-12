#include "Node.hpp"
#include "ByteVector.hpp"
#include "Wallet.hpp"
#include <cstdint>
#include <memory>
#include <string>


const uint32_t Node::COINBASE_AMOUNT = 1024;


Node::Node(std::string seed): wallet(seed) {}


bool Node::addTransaction(const Wallet& from, const logicrypto::ByteVector& to, uint32_t amount) {
  auto user_utxos = this->utxo_map.find(from.getSendAddress().toHexString());

  if (user_utxos == this->utxo_map.end()) {
    return false;
  }

  std::shared_ptr<TxInput> input = nullptr;

  // find a utxo that has the necessary funds
  for (auto& utxo: user_utxos->second) {
    if (utxo->getAmount() >= amount) {
      input = utxo;
      break;
    }
  }

  // return false if no valid input found
  if (input == nullptr) {
    return false;
  }

  // create the transaction 
  auto new_transaction = std::make_shared<Transaction>(input);

  // create the output to send the money
  if (!new_transaction->addOutput(amount,to)) {
    return false;
  };

  // send the remainder back to the user
  if (!new_transaction->addOutput(new_transaction->getUnspent(),from.getSendAddress())) {
    return false;
  }

  // unlock the transaction
  new_transaction->unlock(from.getTransactionSignature(new_transaction->getSignData()));

  // finalize
  new_transaction->finalize();

  // set the input as spent
  input->setSpent();

  // add the transaction to the memory pool
  this->memory_pool.push(new_transaction);

  return true;
}



bool Node::addTransaction(const logicrypto::ByteVector& to, uint32_t amount) {
  return this->addTransaction(this->wallet,to,amount);
}


bool Node::mineNewBlock(std::string coinbase_msg) {
  std::shared_ptr<Block> new_block;

  if (this->blockchain.size() == 0) {
    new_block = std::make_shared<Block>();
  }
  else {
    new_block = std::make_shared<Block>(this->blockchain.back());
  }

  //create coinbase
  this->addCoinbase(coinbase_msg, new_block->getOrder());

  // add all transactions to the block
  while(!this->memory_pool.empty()) {
    new_block->addTransaction(this->memory_pool.front());
    this->memory_pool.pop();
  }

  // mine the block
  new_block->mine();

  // remove spent inputs and add new outputs
  for (auto& t: *new_block) {
    // remove the spent transaction input
    auto usr = this->utxo_map.find(t->getInput()->getDestPk().toHexString());

    // only remove if dest is found
    if (usr != this->utxo_map.end()) {
      auto& input_set = usr->second;

      //remove input
      input_set.erase(t->getInput());

    }
    // =======
    // create new transaction inputs for every output
    for (int i = 0; i < t->getOutputNumber(); i++) {
      auto& out = t->getOutput(i);
      auto new_input = std::make_shared<TxInput>(t->getTxid(),i,out);
      this->utxo_map[out->getDestPk().toHexString()].insert(new_input);
    }
  }
  
  
  // add block to the blockchain
  this->blockchain.push_back(new_block);
  return true;
}


void Node::addCoinbase(std::string coinbase_msg, int block_depth) {
  auto coinbase = std::make_shared<Transaction>(Node::COINBASE_AMOUNT);
  coinbase->addOutput(COINBASE_AMOUNT,this->wallet.getSendAddress());

  coinbase->unlock_coinbase(coinbase_msg,block_depth);
  coinbase->finalize();

  this->memory_pool.push(coinbase);
}


void Node::printBlockchain() const {
  for (auto& block: this->blockchain) {
    block->print();
  }
}


uint32_t Node::getAddressBalance(const logicrypto::ByteVector& addr) const {
  uint32_t balance = 0;

  auto utxo_set = this->utxo_map.find(addr.toHexString());
  if (utxo_set != this->utxo_map.end()) {
    for (const auto& utxo: utxo_set->second) {
      balance += utxo->getAmount();
    } 
  }

  return balance;
}


const logicrypto::ByteVector& Node::getSendAddress() const {
  return this->wallet.getSendAddress();
}

