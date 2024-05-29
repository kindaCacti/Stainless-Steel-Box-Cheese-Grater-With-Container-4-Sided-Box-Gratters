#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "piece.h"

enum class pieces_names{
    empty,
    white_pawn, white_knight, white_bishop, white_rook, white_queen, white_king,
    black_pawn, black_knight, black_bishop, black_rook, black_queen, black_king
};

class Board{
    std::unique_ptr<pieces_names[]> board;
public: 
    Board() = default;
    Board(Board& _second_board){
        board = std::unique_ptr<pieces_names[]>(new pieces_names[8*8]);
        for(int i = 0; i<8; i++){
            for(int j = 0; j<8; j++){
                board[i*8+j] = _second_board.getAt(j, i);
            }
        }
    }

    pieces_names getAt(int x, int y){
        y--;
        x--;
        int resolv = y*8 + x;
        return board[resolv];
    }

    void setAt(int x, int y, pieces_names pn){
        y--;
        x--;
        int resolv = y*8+x;
        board[resolv] = pn;
    }

    void move(int from_x, int from_y, int to_x, int to_y){
        pieces_names tmp = getAt(from_x, from_y);
        setAt(from_x, from_y, pieces_names::empty);
        setAt(to_x, to_y, tmp);
    }

    void setDefault(){
        for(int i = 0; i<64; i++) board[i] = pieces_names::empty;
        for(int i = 0; i<8; i++){
            board[6*8+i] = pieces_names::black_pawn;
            board[8 + i] = pieces_names::white_pawn;
        }

        board[0] = pieces_names::white_rook;
        board[7] = pieces_names::white_rook;
        board[1] = pieces_names::white_knight;
        board[6] = pieces_names::white_knight;
        board[2] = pieces_names::white_bishop;
        board[5] = pieces_names::white_bishop;
        board[3] = pieces_names::white_queen;
        board[4] = pieces_names::white_king;

        board[56] = pieces_names::black_rook;
        board[63] = pieces_names::black_rook;
        board[57] = pieces_names::black_knight;
        board[62] = pieces_names::black_knight;
        board[58] = pieces_names::black_bishop;
        board[61] = pieces_names::black_bishop;
        board[59] = pieces_names::black_queen;
        board[60] = pieces_names::black_king;
    }
};