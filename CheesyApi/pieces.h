#include "piece.h"


class Pawn : public Piece {
  
public:
  Pawn() : Piece("pawn", "Pawn", {{0, 1}, {0, 2}, {-1, 1}, {1, 1}}) {}
};