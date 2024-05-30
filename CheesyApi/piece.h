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

  bool operator==(Move const& other) const {
    return dx == other.dx && dy == other.dy;
  }

  friend std::ostream& operator<<(std::ostream& os, Move const& move) {
    return os << move.dx << "x" << move.dy;
  }
};




class Piece {

protected:
  std::vector<Move> staticMoves;
  std::vector<Move> dynamicMoves;
  std::string name = "piece";
  std::string displayName = "Default piece";
  int weight = 1;

  int color = COLOR_BLACK;

public:

  Piece() = default;
  Piece(std::string setName, std::string setDisplayName, int setWeight, std::vector<Move> setStaticMoves) :
    name(setName), displayName(setDisplayName), weight(setWeight), staticMoves(setStaticMoves) {}
  Piece(std::string setName, std::string setDisplayName, int setWeight,
    std::vector<Move> setStaticMoves,  std::vector<Move> setDynamicMoves) :
    name(setName), displayName(setDisplayName), weight(setWeight),
    staticMoves(setStaticMoves), dynamicMoves(setDynamicMoves) {}
  
  std::vector<Move> const& getStaticMoves() const { return staticMoves; }
  std::vector<Move> const& getDynamicMoves() const { return dynamicMoves; }
  void setColor(int setColor) { color = setColor; }
  int getColor() const { return color; }
  std::string const& getName() const { return name; }
  std::string uniqueStamp() {return (name + std::to_string(color)); }

  friend std::ostream& operator<<(std::ostream& os, Piece const& piece) {
    return os << piece.name;
  }
};