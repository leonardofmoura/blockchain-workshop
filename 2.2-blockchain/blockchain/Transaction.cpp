#include "Transaction.hpp"
#include "TxOutput.hpp"
#include "logicrypto.hpp"
#include <cstdint>
#include <ios>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <strings.h>
#include <ByteVector.hpp>

Transaction::Transaction(std::shared_ptr<TxInput> input):
  input(input), coinbase(false) {
  this->unspent = this->input->getAmount();
}


Transaction::Transaction(uint32_t amount): input(std::make_shared<TxInput>()), coinbase(true), unspent(amount) {}


bool Transaction::addOutput(uint32_t amount, const logicrypto::ByteVector& dest_pk) {
  // verify valid output
  if (amount > this->unspent) {
    return false;
  }

  // create the new outputt
  auto new_output = std::make_shared<TxOutput>(amount,dest_pk);

  // add it to the output list
  this->outputs.push_back(new_output);

  this->unspent -= amount;

  return true; 
}



bool Transaction::unlock(const logicrypto::ByteVector& unlock_code) {
  // check if unlock code is valid
  if (!logicrypto::ed25519_verify(this->getSignData(),unlock_code,this->input->getDestPk())) {
    return false;
  }

  this->unlock_code = unlock_code;
  this->unlocked = true;
  return true;
}


bool Transaction::unlock_coinbase(std::string message, uint32_t block_depth) {
  this->unlock_code = logicrypto::ByteVector(message) + logicrypto::ByteVector::fromInt(block_depth);

  this->unlocked = true;

  return true;
}


logicrypto::ByteVector Transaction::finalize() {
  if (!this->unlocked) {
    throw std::runtime_error("Transaction not unlocked");
  }

  if (this->finalized) {
    throw std::runtime_error("Transaction Already finalized");
  }


  logicrypto::ByteVector combined_outputs;


  for (auto& out: this->outputs) {
    logicrypto::ByteVector out_data = out->serialize();
    combined_outputs.insert(combined_outputs.end(), out_data.begin(), out_data.end());
  }


  logicrypto::ByteVector txdata = this->input->getOutputTxid()+this->unlock_code+combined_outputs;
  this->txid = logicrypto::blake2b(txdata);

  // std::cout << "Transaction data: " << txdata.toHexString() << std::endl;
  // std::cout << "TxID: " << this->txid.toHexString() << std::endl;

  this->finalized = true;

  return this->txid;
}


const std::shared_ptr<const TxOutput>& Transaction::getOutput(int n) const {
  if (n >= this->outputs.size()) {
    throw std::runtime_error("Output does not exist");
  }

  return reinterpret_cast<const std::shared_ptr<const TxOutput>&>(this->outputs.at(n));
}

int Transaction::getOutputNumber() const {
  return this->outputs.size();
}


// TODO: can be optimized
logicrypto::ByteVector Transaction::getSignData() const {
  logicrypto::ByteVector res = this->input->serialize();

  for (auto& o: this->outputs) {
    res = res + o->serialize(); 
  }

  return res;
}


std::shared_ptr<TxInput> Transaction::getInput() const {
  return this->input;
}


logicrypto::ByteVector Transaction::getUnlockCode() const {
  return this->unlock_code;
}


// will return an empty vector if transaction was not finalized
logicrypto::ByteVector Transaction::getTxid() const {
  if (!this->finalized) {
    throw std::runtime_error("Transaction not finalized");
  }

  return this->txid;
}


uint32_t Transaction::getUnspent() const {
  return this->unspent;
}


bool Transaction::isFinalized() const {
  return  this->finalized;
}


bool Transaction::isUnlocked() const {
  return  this->unlocked;
}


std::string Transaction::toString() const {
  std::stringstream ss;

  ss << "=== Transaction ===" << std::endl;

  if (!this->finalized) {
    ss << "Warning: transaction not finalized!" << std::endl;
  }

  ss << "TXID: " << this->txid.toHexString() << std::endl;
  ss << "Coinbase: " << std::boolalpha << this->coinbase << std::endl;


  if (coinbase) {
    ss << "Coinbase Message: " << std::string(this->unlock_code.begin(),this->unlock_code.end()-4) << std::endl;
  }
  else {
    ss << "Unlock Code: " << this->unlock_code.toHexString() << std::endl;
  }

  ss << "Unspent amount: " << this->unspent << std::endl;
  ss << std::endl;

  ss << "Input TxID: " << this->input->getOutputTxid().toHexString() << std::endl;
  ss << "Input Index: " << +this->input->getOutputIndex() << std::endl;
  ss << "Input Amount: " << this->input->getAmount() << std::endl;
  ss << "Input Dest PK:" << this->input->getDestPk().toHexString() << std::endl;
  ss << std::endl;

  int index = 0;
  int output_total = 0;
  for (auto& out: this->outputs) {
    ss << "Output " << index << std::endl;
    ss << "Output Amount: " << out->getAmount() << std::endl;
    ss << "Ouput Dest PK: " << out->getDestString() << std::endl;
    ss << std::endl;
    index++;
    output_total += out->getAmount();
  }

  ss << "Output Total: " << output_total << std::endl;
  ss << "==============" << std::endl << std::endl;

  return ss.str();
}

