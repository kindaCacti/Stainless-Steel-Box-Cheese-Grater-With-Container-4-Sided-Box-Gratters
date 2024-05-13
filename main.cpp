#include <iostream>
#include "CheesyApi/pieces.h"

int main() {
  std::cout << "Cheese grater" << std::endl;
  Pawn pawn = Pawn();
  for(auto m : pawn.getMoves()) {
    std::cout << m << std::endl;
  }
  return 0;
}