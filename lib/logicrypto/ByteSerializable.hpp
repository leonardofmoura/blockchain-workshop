#ifndef BYTESERIALIZABLE_HPP
#define BYTESERIALIZABLE_HPP

#include "ByteVector.hpp"

namespace logicrypto {

class ByteSerializable {
  public:
    ByteSerializable() = default;
    virtual ~ByteSerializable() = default;

    virtual ByteVector serialize() const = 0;
};

}

#endif
