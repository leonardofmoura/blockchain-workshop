#include "KeyPair.hpp"
#include <utility>

using namespace logicrypto;

KeyPair::KeyPair(ByteVector private_key, ByteVector public_key):
  private_key(std::move(private_key)), public_key(std::move(public_key)) {}


KeyPair::~KeyPair() {
  //reset the private key memory when destructing object
  this->private_key.assign(this->private_key.size(),0);
}


const ByteVector& KeyPair::getPublic() const {
  return this->public_key;
}


const ByteVector& KeyPair::getPrivate() const {
  return this->private_key;
}
