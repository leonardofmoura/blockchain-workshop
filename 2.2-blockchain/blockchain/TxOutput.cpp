#include "TxOutput.hpp"
#include <sstream>
#include <ByteVector.hpp>


TxOutput::TxOutput(uint32_t amount, logicrypto::ByteVector dest_pk): amount(amount), dest_pk(dest_pk) {}


uint32_t TxOutput::getAmount() const {
  return this->amount;
}


const logicrypto::ByteVector& TxOutput::getDestPk() const {
  return this->dest_pk;
}


std::string TxOutput::getDestString() const {
  return this->dest_pk.toHexString();
}


// amount + dest_pk
logicrypto::ByteVector TxOutput::serialize() const {
  return logicrypto::ByteVector::fromInt(this->amount) + this->dest_pk;
}


std::string TxOutput::toString() const {
  std::stringstream ss;

  ss << "Amount: " << this->amount << std::endl;
  ss << "Dest Pk: " << this->dest_pk.toHexString() << std::endl;
  ss << "Data: " << this->serialize().toHexString() << std::endl;

  return ss.str();
}
