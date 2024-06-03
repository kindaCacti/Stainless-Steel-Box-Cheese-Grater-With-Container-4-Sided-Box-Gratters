#include <iostream>
#include <vector>
#include "./CheesyApi/game.h"

int main(){
    Game game;
    while(game.isOngoing()){
        std::cout<<game<<std::endl;
        char movX = 0, movY = 0;
        int roundAtTheStart = game.getRound();

        do{
            do{
                std::cout<<game.askForMovement();
                std::cin>>movX>>movY;
            }while(!game.choosePiece(movX, movY, std::cout));

            std::cout<<"possible moves are (write 'o' to change a piece): "<<std::endl;
            game.showPossibleMoves(std::cout);

            char ex, ey;
            std::cin>>ex;

            if(ex == 'o') continue;

            std::cin>>ey;

            if(!game.makeMove(ex, ey)){
                std::cout<<"Incorrect Move"<<std::endl;
            }

        }while(game.getRound() == roundAtTheStart);

        game.isEnd(std::cout);
    }
    return 0;
}