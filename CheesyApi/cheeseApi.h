#pragma once
#include "pieces.h"
#include <iostream>
#include <string>

class CheeseAPI {

  Piece* board[8][8] = {nullptr};
  Move whiteKingPos;
  Move blackKingPos;

public:

  CheeseAPI();

  void spawnPiece(Piece* piece, int x, int y, int color);
  bool posInRange(int x, int y) const;
  int posColor(int x, int y) const;
  bool isKingInDanger(int color) const;
  std::vector<Move> getPieceAvailableMoves(int x, int y);
  Piece* movePiece(int x, int y, int dx, int dy);
  auto const getBoard() { return board; }
  std::string toString();
  void printMoves(int x, int y);
  std::string uniqueStamp();

  friend std::ostream& operator<<(std::ostream& os, CheeseAPI api);
};