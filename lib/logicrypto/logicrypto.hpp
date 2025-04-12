#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include "ByteVector.hpp"
#include "KeyPair.hpp"

#include <memory>
#include <sodium.h>

namespace logicrypto {
  const size_t HASH_SIZE = crypto_generichash_BYTES;

  bool init();

  ByteVector blake2b(const ByteVector& message);

  ByteVector blake2b_pair(const ByteVector& m1, const ByteVector& m2);

  std::unique_ptr<KeyPair> ed25519_keygen();

  std::unique_ptr<KeyPair> ed25519_keygen(const std::string& seed);

  std::unique_ptr<KeyPair> ed25519_keygen(const ByteVector& seed);

  ByteVector ed25519_sign(const ByteVector& message, const ByteVector& private_key);

  bool ed25519_verify(const ByteVector& message, const ByteVector& sig, const ByteVector& public_key);
}


#endif
