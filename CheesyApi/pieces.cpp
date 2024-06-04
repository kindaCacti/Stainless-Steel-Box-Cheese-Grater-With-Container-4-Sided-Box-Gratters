#include "pieces.h"

char pieceChar(Piece tp) {

  int nameCharOffset = (tp.color == PIECE_COLOR::BLACK) * 32;

  int out = '.';

  switch (tp.name) {
  case PIECE_NAMES::PAWN:
    out = 'P';
    break;
  case PIECE_NAMES::BISHOP:
    out = 'B';
    break;
  case PIECE_NAMES::KNIGHT:
    out = 'N';
    break;
  case PIECE_NAMES::ROOK:
    out = 'R';
    break;
  case PIECE_NAMES::QUEEN:
    out = 'Q';
    break;
  case PIECE_NAMES::KING:
    out = 'K';
    break;
  }

  if (out != '.')
    out += nameCharOffset;
  return out;
}

MovePossibilities getBaseMoves(PIECE_NAMES pn, int moves_done = 0) {
  switch (pn) {
    case PIECE_NAMES::PAWN:
      return {{}, {MOVES::UP}};
    case PIECE_NAMES::BISHOP:
      return {{MOVES::UL_DIAG, MOVES::UR_DIAG, MOVES::DL_DIAG, MOVES::DR_DIAG},
              {}};
    case PIECE_NAMES::ROOK:
      return {{MOVES::UP, MOVES::DOWN, MOVES::LEFT, MOVES::RIGHT}, {}};
    case PIECE_NAMES::KNIGHT:
      return {{},
              {MOVES::LSHAPE1, MOVES::LSHAPE2, MOVES::LSHAPE3, MOVES::LSHAPE4,
              MOVES::LSHAPE5, MOVES::LSHAPE6, MOVES::LSHAPE7, MOVES::LSHAPE8}};
    case PIECE_NAMES::QUEEN:
      return {{MOVES::UP, MOVES::DOWN, MOVES::LEFT, MOVES::RIGHT, MOVES::UL_DIAG,
              MOVES::UR_DIAG, MOVES::DL_DIAG, MOVES::DR_DIAG},
              {}};
    case PIECE_NAMES::KING:
      return {{},
              {MOVES::UP, MOVES::DOWN, MOVES::LEFT, MOVES::RIGHT, MOVES::UL_DIAG,
              MOVES::UR_DIAG, MOVES::DL_DIAG, MOVES::DR_DIAG, MOVES::CASTLE}};
  }
  return {{}, {}};
}

Move translateMoves(MOVES mov) {
  switch (mov) {
  case MOVES::UP:
    return {0, 1};
  case MOVES::DOWN:
    return {0, -1};
  case MOVES::LEFT:
    return {-1, 0};
  case MOVES::RIGHT:
    return {1, 0};
  case MOVES::UL_DIAG:
    return {-1, 1};
  case MOVES::DL_DIAG:
    return {-1, -1};
  case MOVES::UR_DIAG:
    return {1, 1};
  case MOVES::DR_DIAG:
    return {1, -1};
  case MOVES::LSHAPE1:
    return {2, 1};
  case MOVES::LSHAPE2:
    return {-2, 1};
  case MOVES::LSHAPE3:
    return {2, -1};
  case MOVES::LSHAPE4:
    return {-2, -1};
  case MOVES::LSHAPE5:
    return {1, 2};
  case MOVES::LSHAPE6:
    return {1, -2};
  case MOVES::LSHAPE7:
    return {-1, 2};
  case MOVES::LSHAPE8:
    return {-1, -2};
  case MOVES::PAWN_MOVES:
    return {0, 2};
  }
  return {0, 0};
}

int pieceValues(PIECE_NAMES pn) {
  switch (pn) {
  case PIECE_NAMES::PAWN:
    return 1;
  case PIECE_NAMES::BISHOP:
  case PIECE_NAMES::KNIGHT:
    return 3;
  case PIECE_NAMES::ROOK:
    return 5;
  case PIECE_NAMES::QUEEN:
    return 7;
  case PIECE_NAMES::KING:
    return 2137;
  }
  return 0;
}