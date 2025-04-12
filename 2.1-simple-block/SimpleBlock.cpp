#include "SimpleBlock.hpp"
#include "ByteVector.hpp"

SimpleBlock::SimpleBlock(std::string data) {
  //TODO
}


SimpleBlock::SimpleBlock(std::shared_ptr<SimpleBlock> parent, std::string data) {
  //TODO
}


const std::shared_ptr<const SimpleBlock> SimpleBlock::getParent() const {
  //TODO
  return nullptr;
}


const logicrypto::ByteVector& SimpleBlock::getHash() const {
  //TODO
  return logicrypto::ByteVector(32);
}


std::string SimpleBlock::getData() const {
  //TODO
  return "";
}
