#include "bot.h"
#include "../CheesyApi/piece.h"
#include "../CheesyApi/pieces.h"
#include <vector>
#include <iostream>

int main(){
    CheeseBotAPI cba(8, 8, 10);
    std::vector<std::vector<Piece*>> board;
    board.assign(8, {});
    for(int i = 0; i<8; i++){
        board[i].assign(8, nullptr);
    }
    std::cout<<cba.getMove(board);
}