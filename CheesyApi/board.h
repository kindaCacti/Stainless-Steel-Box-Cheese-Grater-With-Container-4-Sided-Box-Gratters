#pragma once
#include "pieces.h"
#include <algorithm>
#include <set>
#include <iostream>

class Board{
    Piece board[64];

public:
    Board() = default;
    Board(Piece*);
    Piece* getBoard(){ return board; }
    void setPieces();
    void promote();
    std::string toString() const;
    Piece at(int, int);
    Piece at(int index){ return board[index]; }
    void setAt(int, int, Piece);
    bool canPawnTake(int, int, int, bool = true);
    bool canPawnDoubleMove(int, int, bool = true);
    bool canCastle(int, int, int, bool = false);
    std::vector<Move> generateMoves(Move, int, int, int, bool = true);
    void reverseMove(Move&);
    int getKingPosition(PIECE_COLOR);
    bool isKingUnderAttack(PIECE_COLOR, bool = false);
    void makeMove(int, int, Move);
    std::vector<Move> getMoves(int, int, bool = true);
    std::vector<Move> getMovesOfColor(PIECE_COLOR, bool = true);
    bool isCheckmate(PIECE_COLOR);
    bool isStalemate(PIECE_COLOR);
};