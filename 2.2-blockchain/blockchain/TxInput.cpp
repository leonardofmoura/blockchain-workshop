#include "TxInput.hpp"
#include "TxOutput.hpp"
#include <cstdint>
#include <memory>
#include <ByteVector.hpp>

TxInput::TxInput(logicrypto::ByteVector output_txid, uint8_t output_index, std::shared_ptr<const TxOutput> output):
  output_txid(output_txid), output_index(output_index), amount(output->getAmount()), dest_pk(output->getDestPk()) {}


TxInput::TxInput(): 
  output_txid(logicrypto::ByteVector(32)), output_index(0), amount(0), dest_pk(logicrypto::ByteVector(32)) {}


logicrypto::ByteVector TxInput::getOutputTxid() const {
  return this->output_txid;
}


uint8_t TxInput::getOutputIndex() const {
  return this->output_index;
}


uint32_t TxInput::getAmount() const {
  return this->amount;
}


const logicrypto::ByteVector& TxInput::getDestPk() const {
  return this->dest_pk;
}


bool TxInput::isSpent() const {
  return this->spent;
}


void TxInput::setSpent() {
  this->spent = true;
}


logicrypto::ByteVector TxInput::serialize() const {
  return logicrypto::ByteVector({
    this->output_txid,
    this->output_index,
    this->amount,
    this->dest_pk
  });
}

