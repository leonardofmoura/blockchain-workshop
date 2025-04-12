#ifndef TXOUTPUT_HPP
#define TXOUTPUT_HPP

#include <string>
#include <cstdint>

#include <ByteVector.hpp>
#include <ByteSerializable.hpp>

class TxOutput: public logicrypto::ByteSerializable {
  private:
    const uint32_t amount;
    const logicrypto::ByteVector dest_pk;

  public:

    TxOutput(uint32_t ammount, logicrypto::ByteVector dest_pk);

    uint32_t getAmount() const;
    const logicrypto::ByteVector& getDestPk() const;
    std::string getDestString() const;

    // amount + dest_pk
    logicrypto::ByteVector serialize() const override;
    std::string toString() const;
};

#endif
