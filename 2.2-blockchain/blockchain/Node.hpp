#ifndef NODE_HPP
#define NODE_HPP

#include "Block.hpp"
#include "ByteVector.hpp"
#include "Wallet.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

class Node {
  public:
    Node(std::string seed);

    bool addTransaction(const Wallet& from, const logicrypto::ByteVector& to, uint32_t amount);
    bool addTransaction(const logicrypto::ByteVector& to, uint32_t amount);
    bool mineNewBlock(std::string coinbase_msg);
    void printBlockchain() const;
    uint32_t getAddressBalance(const logicrypto::ByteVector& addr) const;
    const logicrypto::ByteVector& getSendAddress() const;


  private:
    static const uint32_t COINBASE_AMOUNT;

    const Wallet wallet;
    std::vector<std::shared_ptr<Block>> blockchain;
    std::queue<std::shared_ptr<Transaction>> memory_pool;
    std::unordered_map<std::string,std::unordered_set<std::shared_ptr<TxInput>>> utxo_map;

    void addCoinbase(std::string coinbase_msg, int block_depth);
};

#endif
