#include "Block.hpp"
#include "ByteVector.hpp"
#include "Transaction.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <ostream>
#include <sodium.h>
#include <string>
#include <logicrypto.hpp>
#include <utility>

int Block::nextOrder = 0;

Block::Block(std::shared_ptr<Block> parent): 
  parent(parent), parent_hash(parent->getBlockHash()) {
  this->order = Block::nextOrder++;
}


Block::Block(): parent(nullptr), parent_hash(logicrypto::ByteVector(logicrypto::HASH_SIZE)), order(0) {
  Block::nextOrder = 1;
}


bool Block::addTransaction(std::shared_ptr<Transaction> transaction) {
  // only allow finalized transactions
  if (!transaction->isFinalized()) {
    return false;
  }

  this->transactions.push_back(transaction); 
  return true;
}


const std::shared_ptr<const Transaction>& Block::getTransaction(int n) const {
  return this->transactions.at(n);
}


std::string Block::mine() {
  // use initializer list for more efficient allocation
  this->calculateMerkleRoot();

  logicrypto::ByteVector block_data{this->parent_hash,this->merkle_root,logicrypto::ByteVector::fromInt(this->nonce)}; 

  logicrypto::ByteVector hash = logicrypto::blake2b(block_data); 

  auto data_end = block_data.begin() + 2*logicrypto::HASH_SIZE;

  while (hash[0] != 0 || hash[1] != 0) {
    // print previous run
    // std::cout << "Block Data:" << block_data.toHexString() << std::endl;
    // std::cout << "Tested nonce: " << this->nonce << std::endl;
    // std::cout << "Block Info: " << block_data.toHexString() << std::endl;
    // std::cout << "Hash: " << hash.toHexString() << std::endl;
    // std::cout << std::endl;

    // calculate new hash
    this->nonce++;
    logicrypto::ByteVector new_nonce = logicrypto::ByteVector::fromInt(this->nonce);
    std::copy(new_nonce.begin(), new_nonce.end(), data_end);
    hash = logicrypto::blake2b(block_data);
  }

  this->block_hash = hash;

  return this->block_hash.toHexString();
}


std::string Block::getHashString() const {
  return this->block_hash.toHexString();
}


const logicrypto::ByteVector& Block::getBlockHash() const {
  return this->block_hash;
}


std::shared_ptr<Block> Block::getParent() const {
  return this->parent;
}


const logicrypto::ByteVector& Block::getParentHash() const {
  return this->parent_hash;
}


int Block::getOrder() const {
  return this->order;
}

void Block::print() const {
  std::cout << "===== Block " << std::setw(2) << std::setfill('0') << this->order;
  std::cout <<" =====" << std::endl;
  std::cout << "Block Hash: " << this->getHashString() << std::endl;
  std::cout << "Parent Hash:" << this->getParentHash().toHexString() << std::endl;
  std::cout << "Merkle Root: " << this->merkle_root.toHexString() << std::endl;

  std::cout << std::endl;

  // transactions
  for (auto& t: this->transactions) {
    std::cout << t->toString();
  }

  std::cout << std::endl;
  std::cout << "====================" << std::endl;
}


void Block::calculateMerkleRoot() {
  std::vector<logicrypto::ByteVector> tree_level;
  tree_level.reserve(this->transactions.size());

  for (const auto& tx: this->transactions) {
    tree_level.push_back(tx->getTxid());
  }

  while (tree_level.size() > 1) {
    // check odd number of transactions
    if (tree_level.size() % 2 != 0) {
      // copy last element
      tree_level.push_back(tree_level.back());
    } 

    std::vector<logicrypto::ByteVector> next_level;
    next_level.reserve(tree_level.size()/2);

    for (size_t i = 0; i < tree_level.size(); i += 2) {
      next_level.push_back(logicrypto::blake2b_pair(tree_level[i],tree_level[i+1]));
    }

    // make the next level the new level
    tree_level = std::move(next_level);
  }

  this->merkle_root = std::move(tree_level.front());
}


Block::ConstTransactionIterator Block::begin() const {
  return this->transactions.begin(); 
}


Block::ConstTransactionIterator Block::end() const {
  return this->transactions.end(); 
}
