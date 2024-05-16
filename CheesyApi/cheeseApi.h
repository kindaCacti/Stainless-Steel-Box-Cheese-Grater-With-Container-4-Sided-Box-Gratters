#pragma once
#include "pieces.h"
#include <iostream>
#include <string>

class CheeseAPI {

  Piece* board[8][8] = {nullptr};

public:

  CheeseAPI();

  void spawnPiece(Piece* piece, int x, int y, int color);
  bool posInRange(int x, int y);
  int posColor(int x, int y);
  std::vector<Move> getPieceAvailableMoves(int x, int y);
  Piece* movePiece(int x, int y, int dx, int dy);
  auto const getBoard() { return board; }
  std::string toString();
  void printMoves(int x, int y);

  friend std::ostream& operator<<(std::ostream& os, CheeseAPI api);
};