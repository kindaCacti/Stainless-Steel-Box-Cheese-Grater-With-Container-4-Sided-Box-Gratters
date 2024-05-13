#pragma once
#include <vector>
#include <string>
#include "iostream"

const int COLOR_BLACK = 0;
const int COLOR_WHITE = 1;

class Move {

public:

  int dx = 0;
  int dy = 0;

  Move() = default;
  Move(int setDx, int setDy): dx(setDx), dy(setDy) {}

  void operator+=(Move const& other) {
    dx += other.dx;
    dy += other.dy;
  }

  friend std::ostream& operator<<(std::ostream& os, Move const& move) {
    return os << move.dx << "x" << move.dy;
  }
};




class Piece {

protected:
  std::string name = "piece";
  std::string displayName = "Default piece";
  int color = COLOR_BLACK;

  std::vector<Move> staticMoves;
  std::vector<Move> dynamicMoves;

public:

  Piece() = default;
  Piece(std::string setName, std::string setDisplayName, std::vector<Move> setStaticMoves) :
    name(setName), displayName(setDisplayName), staticMoves(setStaticMoves) {}
  Piece(std::string setName, std::string setDisplayName,
    std::vector<Move> setStaticMoves,  std::vector<Move> setDynamicMoves) :
    name(setName), displayName(setDisplayName),
    staticMoves(setStaticMoves), dynamicMoves(setDynamicMoves) {}

  std::vector<Move> getMoves(int x, int y) const;
  void setColor(int setColor) { color = setColor; }
  int getColor() const { return color; }
};