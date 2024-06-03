#include <iostream>
#include <vector>
#include "./chess_API/game.h"

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

            game.showPossibleMoves(std::cout);

            char ex, ey;
            std::cin>>ex;

            if(ex == 'o') continue;
            if(ex=='q') return 0;

            std::cin>>ey;

            if(!game.makeMove(ex, ey)){
                std::cout<<"Incorrect Move"<<std::endl;
            }

        }while(game.getRound() == roundAtTheStart);

        game.isEnd(std::cout);
    }
    return 0;
}