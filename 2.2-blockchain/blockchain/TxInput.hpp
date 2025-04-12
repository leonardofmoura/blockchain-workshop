#ifndef TXINPUT_HPP
#define TXINPUT_HPP

#include "ByteSerializable.hpp"
#include "TxOutput.hpp"
#include <cstdint>
#include <memory>
#include <ByteVector.hpp>

class TxInput: public logicrypto::ByteSerializable {
  private:
    const logicrypto::ByteVector output_txid;
    const uint8_t output_index;
    const uint32_t amount;
    const logicrypto::ByteVector dest_pk;
    bool spent = false;


  public:
    TxInput(logicrypto::ByteVector output_txid, uint8_t output_index, std::shared_ptr<const TxOutput> output);
    TxInput(); // empty input used in a coinbase
    logicrypto::ByteVector getOutputTxid() const;
    uint8_t getOutputIndex() const;
    uint32_t getAmount() const;
    const logicrypto::ByteVector& getDestPk() const;
    bool isSpent() const;
    void setSpent();
    logicrypto::ByteVector serialize() const override;
}; 

#endif
