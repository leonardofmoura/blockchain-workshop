#include "ByteVector.hpp"
#include <fstream>
#include <ios>
#include <logicrypto.hpp>
#include <memory>
#include <iostream>
#include <sodium.h>
#include <sodium/crypto_sign.h>


void write_sig(const logicrypto::ByteVector& sig) {
  //write sig to file
  std::ofstream out("sig.bin", std::ios::binary);
  if (!out) {
    std::cerr << "Could not open file\n";
  }

  out.write(reinterpret_cast<const char *>(sig.data()),sig.size());
  out.close();
  std::cout << "Writen to file" << std::endl;
}


logicrypto::ByteVector loadfile() {
  std::ifstream in("sig.bin", std::ios::binary);
  if (!in) {
    std::cerr << "Error opening file\n";
  }

  in.seekg(0,std::ios::end);
  std::streamsize size = in.tellg();
  in.seekg(0,std::ios::beg);

  logicrypto::ByteVector sig(size);

  if (!in.read(reinterpret_cast<char*>(sig.data()),size)) {
    std::cerr << "Error reading file\n";
  }

  return std::move(sig);
}


int main() {
  logicrypto::init();

  logicrypto::ByteVector test("loasjdfhsdool");
  std::cout << logicrypto::blake2b(test).toHexString() << std::endl;

  std::unique_ptr<logicrypto::KeyPair> keys = logicrypto::ed25519_keygen("logicseed");;


  std::cout << "Public Key: " << keys->getPublic().toHexString() << "\n";
  std::cout << "Private Key: " << keys->getPrivate().toHexString() << "\n";
 
  logicrypto::ByteVector message("My message");

  logicrypto::ByteVector sig = logicrypto::ed25519_sign(message,keys->getPrivate());
  // logicrypto::ByteVector sig = loadfile();

  std::cout << "Signature: " << sig.toHexString() << "\n";

  bool verif = logicrypto::ed25519_verify(message,sig,keys->getPublic());

  std::cout << "Signature Valid: " << std::boolalpha << verif << std::endl;

  bool invalid_verif = logicrypto::ed25519_verify(message,logicrypto::ByteVector(crypto_sign_BYTES),keys->getPublic());

  std::cout << "Invalid Verif: " << std::boolalpha << invalid_verif << std::endl;

  // write_sig(sig);

  return 0;
}
