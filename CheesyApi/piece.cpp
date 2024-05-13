#include "piece.h"
#include <algorithm>

std::vector<Move> Piece::getMoves(int x, int y) const {
  std::vector<Move> moves;

  for(Move move : staticMoves) {
    if(x+move.dx >= 0 && x+move.dx < 8 && y+move.dy >= 0 && y+move.dy < 8) {
      moves.push_back(move);
    }
  }

  for(Move move : dynamicMoves) {
    Move sMove = Move(move.dx, move.dy);
    while(x+sMove.dx >= 0 && x+sMove.dx < 8 && y+sMove.dy >= 0 && y+sMove.dy < 8) {
      moves.push_back(sMove);
      sMove += move;
    }
  }

  return moves;
}