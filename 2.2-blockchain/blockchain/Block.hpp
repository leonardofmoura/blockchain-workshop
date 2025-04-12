#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Transaction.hpp"
#include <cstdint>
#include <memory>
#include <sodium/crypto_hash_sha256.h>
#include <string>

#include <ByteVector.hpp>

class Block {
  private:
    static int nextOrder;
    int order;
    const std::shared_ptr<Block> parent;

    // sha256(previous_hash + merkle_root + nonce)
    logicrypto::ByteVector block_hash;
    const logicrypto::ByteVector parent_hash;
    logicrypto::ByteVector merkle_root;

    std::vector<std::shared_ptr<const Transaction>> transactions;
    uint32_t nonce = 0;
    bool mined = false;

    void calculateMerkleRoot();

  public:
    Block(std::shared_ptr<Block> parent);
    Block();

    bool addTransaction(std::shared_ptr<Transaction> transaction);
    const std::shared_ptr<const Transaction>& getTransaction(int n) const;
    std::string mine();

    std::string getHashString() const;
    const logicrypto::ByteVector& getBlockHash() const;

    std::shared_ptr<Block> getParent() const;
    const logicrypto::ByteVector& getParentHash() const;

    int getOrder() const;

    void print() const;

    using ConstTransactionIterator = std::vector<std::shared_ptr<const Transaction>>::const_iterator;

    ConstTransactionIterator begin() const;
    ConstTransactionIterator end() const;
};

#endif
