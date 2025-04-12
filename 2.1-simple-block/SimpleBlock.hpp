#ifndef SIMPLE_BLOCK_HPP
#define SIMPLE_BLOCK_HPP

#include "ByteVector.hpp"
#include <memory>
#include <string>


class SimpleBlock {
  public:
    SimpleBlock(std::string data);
    SimpleBlock(std::shared_ptr<SimpleBlock> parent, std::string data);
    
    const std::shared_ptr<const SimpleBlock> getParent() const;
    const logicrypto::ByteVector& getHash() const;
    std::string getData() const;

  private:
    const std::shared_ptr<const SimpleBlock> parent;
    logicrypto::ByteVector block_hash;
    std::string data;
};


#endif

