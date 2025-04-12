#ifndef WALLET_HPP
#define WALLET_HPP

#include <ByteVector.hpp>
#include <memory>

#include "KeyPair.hpp"

class Wallet {
  private:
    const std::string seed;
    const std::unique_ptr<logicrypto::KeyPair> keys;

  public:
    Wallet(std::string seed);

    const logicrypto::ByteVector& getSendAddress() const;
    logicrypto::ByteVector getTransactionSignature(const logicrypto::ByteVector& transaction) const;
};

#endif
