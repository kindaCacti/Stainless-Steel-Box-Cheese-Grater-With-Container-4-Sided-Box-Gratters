#include "piece.h"


class Pawn : public Piece {

public:
  Pawn() : Piece("p", "Pawn", {{0, 1}, {0, 2}, {-1, 1}, {1, 1}}) {}
};

class Rook : public Piece {
  
public:
  Rook() : Piece("r", "Rook", {}, {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}) {}
};

class Knight : public Piece {
  
public:
  Knight() : Piece("n", "Knight", {{2, 1}, {1, 2}, {-2, 1}, {1, -2}, {2, -1}, {-1, 2}, {-2, -1}, {-1, -2}}) {}
};

class Bishop : public Piece {
  
public:
  Bishop() : Piece("b", "Bishop", {}, {{1, 1}, {-1, -1}, {-1, 1}, {1, -1}}) {}
};

class King : public Piece {
  
public:
  King() : Piece("k", "King", {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}}) {}
};

class Queen : public Piece {
  
public:
  Queen() : Piece("q", "Queen", {}, {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}}) {}
};