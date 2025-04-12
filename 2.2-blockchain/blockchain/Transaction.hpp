#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include "TxInput.hpp"
#include "TxOutput.hpp"
#include <cstdint>
#include <memory>
#include <vector>
#include <ByteVector.hpp>

class Transaction {
  private:
    const std::shared_ptr<TxInput> input;
    logicrypto::ByteVector unlock_code; //signature of the transaction
    std::vector<std::shared_ptr<TxOutput>> outputs;

    // blake2b(input_txid+unlock_code+outputs)
    logicrypto::ByteVector txid;

    uint32_t unspent;
    bool finalized = false;
    bool unlocked = false;
    const bool coinbase;

  public:
    Transaction(std::shared_ptr<TxInput> input);
    Transaction(uint32_t amount); // transaction with no input is a coinbase

    // add outputs
    bool addOutput(uint32_t amount, const logicrypto::ByteVector& dest_pk);

    // add unlock code
    bool unlock(const logicrypto::ByteVector& unlock_code);

    // special case for coinbase
    bool unlock_coinbase(std::string message, uint32_t block_depth);

    // generate txid
    logicrypto::ByteVector finalize();

    const std::shared_ptr<const TxOutput>& getOutput(int n) const;
    int getOutputNumber() const;

    // blake2b input_txid + input_amount + input_dest_pk + outputs
    logicrypto::ByteVector getSignData() const;

    std::shared_ptr<TxInput> getInput() const;
    logicrypto::ByteVector getUnlockCode() const;
    logicrypto::ByteVector getTxid() const;
    uint32_t getUnspent() const;
    bool isFinalized() const;
    bool isUnlocked() const;
    std::string toString() const;
};

#endif
