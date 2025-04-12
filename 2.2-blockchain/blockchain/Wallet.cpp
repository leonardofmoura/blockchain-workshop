#include "Wallet.hpp"
#include "ByteVector.hpp"
#include "logicrypto.hpp"

Wallet::Wallet(std::string seed): keys(logicrypto::ed25519_keygen(seed)) {}

const logicrypto::ByteVector& Wallet::getSendAddress() const {
  return this->keys->getPublic();
}


logicrypto::ByteVector Wallet::getTransactionSignature(const logicrypto::ByteVector& transaction_data) const {
  return logicrypto::ed25519_sign(transaction_data,this->keys->getPrivate());
}
