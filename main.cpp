#include <iostream>
#include "CheesyApi/cheeseApi.h"
#include "CheesyBot/bot.h"

int main() {
  std::cout << "Cheese grater" << std::endl;
  CheeseAPI api = CheeseAPI();
  std::cout << api << std::endl;
  CheeseBotAPI cba;
  cba.getMove(api);
  std::cout<<cba.getTreeSize()<<std::endl;
  api.printMoves(1, 6);
  return 0;
}