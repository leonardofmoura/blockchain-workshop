#include <iomanip>
#include <iostream>
#include <sodium.h>
#include <sstream>
#include <string>


std::string to_hex(unsigned char* hash, size_t len) {
  std::ostringstream os;
  for (size_t i =0; i < len; i++) {
    os << std::hex << std::setw(2) << std::setfill('0');
    os << (unsigned) hash[i];
  }
  return os.str();
}


int main() {
  if (sodium_init() < 0) {
    std::cerr << "Could not init libsodium" << std::endl;
    return 1;
  }

  std::string hello = "hello world!";
  unsigned char hash[crypto_hash_sha256_BYTES];
  auto data_ptr = reinterpret_cast<const unsigned char*>(hello.data());
  
  crypto_hash_sha256(hash,data_ptr,hello.size());

  std::cout << "hash: " << to_hex(hash,crypto_hash_sha256_BYTES) << std::endl; 

  return 0;
}

