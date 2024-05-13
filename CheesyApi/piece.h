#pragma once
#include <vector>
#include <string>
#include "iostream"

class Move {

  int dx = 0;
  int dy = 0;

public:

  Move() = default;
  Move(int setDx, int setDy): dx(setDx), dy(setDy) {}

  friend std::ostream& operator<<(std::ostream& os, Move const& move) {
    return os << move.dx << "x" << move.dy;
  }

};


class Piece {

protected:
  std::string name = "piece";
  std::string displayName = "Default piece";

  std::vector<Move> moves;

public:

  Piece() = default;
  Piece(std::string setName, std::string setDisplayName, std::vector<Move> setMoves) :
    name(setName), displayName(setDisplayName), moves(setMoves) {}

  std::vector<Move> const& getMoves() const { return moves; }
};