#ifndef BYTEVECTOR_HPP
#define BYTEVECTOR_HPP

#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>


namespace logicrypto  {

class ByteVector : public std::vector<uint8_t> {
  public:
    ByteVector();
    ByteVector(std::size_t size);
    ByteVector(std::string s);
    ByteVector(std::initializer_list<ByteVector> arrays);

    static ByteVector fromInt(uint32_t n);

    std::string toHexString() const;
    ByteVector merge(const ByteVector& d) const;
    static ByteVector merge(std::initializer_list<ByteVector> arrays);


    // Operator + as syntatic sugar for merge
    ByteVector operator+(const ByteVector& other) const;
};


}



#endif
