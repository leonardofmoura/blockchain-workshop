#include "ByteVector.hpp"

#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace logicrypto;

ByteVector::ByteVector(): std::vector<uint8_t>() {} 


ByteVector::ByteVector(std::size_t size): std::vector<uint8_t>(size) {}


ByteVector::ByteVector(std::string s): std::vector<uint8_t>(s.begin(),s.end()) {}

ByteVector::ByteVector(std::initializer_list<ByteVector> arrays): std::vector<uint8_t>() {
  // determine resulting length
  int total_len = 0;
  for (const ByteVector& a: arrays) {
    total_len += a.size();
  }
  
  // allocate a new vector with all the necessary space
  this->reserve(total_len);

  for (const ByteVector& a : arrays) {
    this->insert(this->end(), a.begin(), a.end());
  }
}


ByteVector ByteVector::fromInt(uint32_t n) {
  ByteVector res(4);

  // use biwise operations for efficiency
  res[0] = (n >> 24) & 0xFF;  // Extract the most significant byte
  res[1] = (n >> 16) & 0xFF; 
  res[2] = (n >> 8) & 0xFF;
  res[3] = n & 0xFF; 

  return res;
}


std::string ByteVector::toHexString() const {
  std::stringstream ss;

  for (const auto &byte: *this) {
    ss << std::setw(2) << std::setfill('0') << std::hex << (unsigned) byte;
  }
  
  return ss.str();
}


ByteVector ByteVector::merge(const ByteVector& d) const {
  ByteVector res(this->size() + d.size());

  std::copy(this->begin(), this->end(), res.begin());
  std::copy(d.begin(), d.end(), res.begin()+this->size());

  return res;
}


ByteVector ByteVector::operator+(const ByteVector& other) const {
  return this->merge(other);
}

