#include <iostream>
#include <vector>
#include "./CheesyApi/game.h"
#include "./CheesyBot/bot.h"

int main(){
    std::cout<<"hi\n";
    Game game;
    while(game.isOngoing()){
        std::cout<<game<<std::endl;
        char movX = 0, movY = 0;
        int roundAtTheStart = game.getRound();
        if(game.getRound()%2){
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

        }else{
            std::cout<<"Bots best move is: ";
            Bot b(game.getBoard());
            
            std::vector<int> bestMove = b.getRandomMove(game.getRound());

            std::string bmove = b.convertToChessNotation(bestMove[0], bestMove[1]);
            bmove += b.convertToChessNotation(bestMove[2], bestMove[3]);
            bool tmp1 = game.choosePiece(bmove[0], bmove[1], std::cout);
            game.showPossibleMoves(std::cout);
            bool tmp2 = game.makeMove(bmove[2], bmove[3]);

            std::cout<<bmove[0]<<bmove[1]<<" -- "<<bmove[2]<<bmove[3]<<std::endl;
        }

        game.isEnd(std::cout);
    }
    return 0;
}