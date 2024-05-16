#include <iostream>
#include "CheesyApi/cheeseApi.h"

int main() {
  std::cout << "Cheese grater" << std::endl;
  CheeseAPI api = CheeseAPI();
  std::cout << api << std::endl;
  api.printMoves(1, 6);
  return 0;
}