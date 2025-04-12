#include "Node.hpp"
#include "Wallet.hpp"
#include "logicrypto.hpp"
#include <iostream>

int main() {
  logicrypto::init();


  Wallet wallet2("wallet 2");
  Wallet wallet3("wallet 3");

  Node my_node = Node("my node seed");

  my_node.mineNewBlock("European stocks move 1.4% higher, reversing course after streak of tariff-led losses");

  my_node.addTransaction(wallet2.getSendAddress(),1000);
  my_node.mineNewBlock("second block");

  my_node.addTransaction(wallet2,wallet3.getSendAddress(),300);
  my_node.addTransaction(wallet3.getSendAddress(),200);
  my_node.mineNewBlock("third block");

  my_node.printBlockchain();

  std::cout << "Node Balance: " << my_node.getAddressBalance(my_node.getSendAddress()) << std::endl;
  std::cout << "Wallet 2 Balance: " << my_node.getAddressBalance(wallet2.getSendAddress()) << std::endl;
  std::cout << "Wallet 3 Balance: " << my_node.getAddressBalance(wallet3.getSendAddress()) << std::endl;

  return 0;
}
