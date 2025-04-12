#ifndef KEYPAIR_HPP
#define KEYPAIR_HPP

#include <ByteVector.hpp>

namespace logicrypto {
  class KeyPair {
    public:
      KeyPair(ByteVector private_key, ByteVector public_key);
      ~KeyPair();

      const ByteVector& getPublic() const;
      const ByteVector& getPrivate() const;

    private:
      const ByteVector public_key;

      // cannot be constant to be zeroed in the end
      ByteVector private_key;
  };
}

#endif // !KEYPAIR_HPP
