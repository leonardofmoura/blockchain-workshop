#include "logicrypto.hpp"
#include "ByteVector.hpp"
#include "KeyPair.hpp"

#include <algorithm>
#include <memory>
#include <sodium.h>
#include <sodium/core.h>
#include <sodium/crypto_hash.h>
#include <sodium/crypto_sign.h>
#include <utility>


using namespace logicrypto;

bool logicrypto::init() {
  if (sodium_init() < 0) {
    return false;
  }
  return true;
}


ByteVector logicrypto::blake2b(const ByteVector& message) {
  ByteVector hash(HASH_SIZE);
  
  crypto_generichash(hash.data(),hash.size(),message.data(),message.size(),NULL,0);

  return hash;
}


ByteVector logicrypto::blake2b_pair(const ByteVector &m1, const ByteVector &m2) {
  ByteVector hash(HASH_SIZE);
  
  ByteVector combined(m1);
  combined.insert(combined.end(), m2.begin(), m2.end());

  crypto_generichash(hash.data(),hash.size(),combined.data(),combined.size(),NULL,0);
  return hash;
}


std::unique_ptr<KeyPair> logicrypto::ed25519_keygen() {
  ByteVector private_key(crypto_sign_SECRETKEYBYTES);
  ByteVector public_key(crypto_sign_PUBLICKEYBYTES);

  crypto_sign_keypair(public_key.data(),private_key.data());

  return std::make_unique<KeyPair>(std::move(private_key), std::move(public_key));
}


std::unique_ptr<KeyPair> logicrypto::ed25519_keygen(const std::string& seed) {
  ByteVector private_key(crypto_sign_SECRETKEYBYTES);
  ByteVector public_key(crypto_sign_PUBLICKEYBYTES);
  ByteVector seed_bytes(crypto_sign_SEEDBYTES);

  if (seed.size() < seed_bytes.size()) {
    std::copy(seed.begin(), seed.end(), seed_bytes.begin());
  }
  else {
    std::copy(seed.begin(), seed.begin()+seed_bytes.size(), seed_bytes.begin());
  }

  crypto_sign_seed_keypair(public_key.data(),private_key.data(),seed_bytes.data());

  return std::make_unique<KeyPair>(std::move(private_key), std::move(public_key));
}


std::unique_ptr<KeyPair> logicrypto::ed25519_keygen(const ByteVector& seed) {
  ByteVector private_key(crypto_sign_SECRETKEYBYTES);
  ByteVector public_key(crypto_sign_PUBLICKEYBYTES);
  ByteVector seed_bytes(crypto_sign_SEEDBYTES);

  if (seed.size() < seed_bytes.size()) {
    std::copy(seed.begin(), seed.end(), seed_bytes.begin());
  }
  else {
    std::copy(seed.begin(), seed.begin()+seed_bytes.size(), seed_bytes.begin());
  }
  crypto_sign_seed_keypair(public_key.data(),private_key.data(), seed_bytes.data());

  return std::make_unique<KeyPair>(std::move(private_key), std::move(public_key));
}


ByteVector logicrypto::ed25519_sign(const ByteVector& message, const ByteVector& private_key) {
  ByteVector sig(crypto_sign_BYTES);
  
  crypto_sign_detached(sig.data(), NULL, message.data(), message.size(), private_key.data());

  return sig;
}



bool logicrypto::ed25519_verify(const ByteVector& message, const ByteVector& sig, const ByteVector& public_key) {
  return crypto_sign_verify_detached(sig.data(),message.data(),message.size(),public_key.data()) == 0;
}
