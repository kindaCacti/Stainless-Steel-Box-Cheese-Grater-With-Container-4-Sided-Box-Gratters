#pragma once
#include "../CheesyApi/piece.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class CheeseBotAPI{
    int depth;
    int boardHeight;
    int boardWidth;
    std::vector<Move> moves;

    std::vector<Move> getCorrectMoves(std::vector<Move>& allMoves, std::vector<std::vector<Piece*>>& board, int posX, int posY){
        std::vector<Move> out;
        for(Move move : allMoves){
            int mx = posX + move.dx;
            int my = posY + move.dy;
            if(board[mx][my] == nullptr or board[mx][my]->getColor() == board[posX][posY]->getColor())
                continue;

            out.push_back(Move(mx, my));
        }
        return out;
    }

    void getMoves(std::vector<std::vector<Piece*>>& board){
        for(int y = 0; y<boardWidth; y++){
            for(int x = 0; x<boardHeight; x++){
                if(board[y][x] == nullptr) continue;
                std::vector<Move> allMoves = board[y][x]->getMoves(x, y);
                std::vector<Move> tmp = getCorrectMoves(allMoves, board, x, y);
                std::copy(tmp.begin(), tmp.end(), std::back_inserter(moves));
            }
        }
    }

    int chooseMove(){
        int numberOfMoves = moves.size();
        return rand() % numberOfMoves;
    }

public:
    CheeseBotAPI(int _boardHeight = 8, int _boardWidth = 8, int _depth = 1): boardHeight(_boardHeight), boardWidth(_boardWidth), depth(_depth) {
        srand(time(NULL));
    }

    Move getMove(std::vector<std::vector<Piece*>> board){
        getMoves(board);
        Move out =  moves[chooseMove()];
        moves.clear();
        return out;
    }
};