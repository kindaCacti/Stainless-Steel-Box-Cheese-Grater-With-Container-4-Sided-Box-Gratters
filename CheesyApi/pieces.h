#pragma once
#include <string>
#include <vector>

enum class PIECE_COLOR { WHITE, BLACK };

enum class PIECE_NAMES { NO_PIECE, PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING };

enum class MOVES {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  UL_DIAG,
  UR_DIAG,
  DL_DIAG,
  DR_DIAG,
  LSHAPE1,
  LSHAPE2,
  LSHAPE3,
  LSHAPE4,
  LSHAPE5,
  LSHAPE6,
  LSHAPE7,
  LSHAPE8,
  PAWN_MOVES,
  CASTLE
};

struct Move {
  int delta_x;
  int delta_y;

  Move operator*(int a) const { return {delta_x * a, delta_y * a}; }

  bool operator==(Move &mv) {
    if (mv.delta_x == delta_x and mv.delta_y == delta_y)
      return true;
    return false;
  }

  std::string toString() const {
    return std::to_string(delta_x) + "x" + std::to_string(delta_y) + "\n";
  }
};

struct Piece {
  PIECE_NAMES name;
  PIECE_COLOR color;
  int moves_done = 0;

  Piece() = default;
  Piece(PIECE_NAMES pn, PIECE_COLOR pc = PIECE_COLOR::WHITE, int mov = 0)
      : name(pn), color(pc), moves_done(mov) {}
};

struct MovePossibilities {
  std::vector<MOVES> repeatingMoves;
  std::vector<MOVES> singleMoves;
};

char pieceChar(Piece);
MovePossibilities getBaseMoves(PIECE_NAMES, int);
Move translateMoves(MOVES);
int pieceValues(PIECE_NAMES);
