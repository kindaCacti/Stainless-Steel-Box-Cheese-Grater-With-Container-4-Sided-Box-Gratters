#include <iostream>
#include "CheesyApi/pieces.h"

int main() {
  std::cout << "Cheese grater" << std::endl;
  auto piece = Queen();
  for(auto m : piece.getMoves(5, 5)) {
    std::cout << m << std::endl;
  }
  return 0;
}