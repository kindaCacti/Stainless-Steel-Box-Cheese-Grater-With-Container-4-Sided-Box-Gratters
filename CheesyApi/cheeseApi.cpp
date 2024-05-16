#include "cheeseApi.h"
#include "pieces.h"
#include <algorithm>

CheeseAPI::CheeseAPI() {
  int pawnRows[2] = {1, 6};
  int figureRows[2] = {0, 7};
  int colors[2] = {COLOR_BLACK, COLOR_WHITE};
  for(int c = 0; c < 2; ++c) {
    for(int x = 0; x < 8; ++x) {
      spawnPiece(new Pawn(), x, pawnRows[c], colors[c]);
    }
    spawnPiece(new Rook(), 0, figureRows[c], colors[c]);
    spawnPiece(new Knight(), 1, figureRows[c], colors[c]);
    spawnPiece(new Bishop(), 2, figureRows[c], colors[c]);
    spawnPiece(new Queen(), 3, figureRows[c], colors[c]);
    spawnPiece(new King(), 4, figureRows[c], colors[c]);
    spawnPiece(new Bishop(), 5, figureRows[c], colors[c]);
    spawnPiece(new Knight(), 6, figureRows[c], colors[c]);
    spawnPiece(new Rook(), 7, figureRows[c], colors[c]);
  }
}

void CheeseAPI::spawnPiece(Piece* piece, int x, int y, int color) {
  piece->setColor(color);
  board[x][y] = piece;
}

bool CheeseAPI::posInRange(int x, int y) {
  return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

int CheeseAPI::posColor(int x, int y) {
  return !board[x][y] ? -1 : board[x][y]->getColor();
}

std::vector<Move> CheeseAPI::getPieceAvailableMoves(int x, int y) {
  if(!posInRange(x, y)) {
    throw std::invalid_argument("Coordinates out of range!");
  }

  std::vector<Move> moves;
  if(!board[x][y]) {
    return moves;
  }

  Piece* piece = board[x][y];
  int c = piece->getColor();
  int cr = c == COLOR_BLACK ? COLOR_WHITE : COLOR_BLACK;

  if(piece->getName() == "p") {
    int d = c == COLOR_BLACK ? 1 : -1;
    int sr = c == COLOR_BLACK ? 1 : 6;
    if(y == sr && posInRange(x, y+2*d) && posColor(x, y+2*d) == -1)
      moves.push_back(Move(0, 2*d));
    if(posInRange(x, y+d) && posColor(x, y+d) == -1)
      moves.push_back(Move(0, d));
    if(posInRange(x+1, y+d) && posColor(x+1, y+d) == cr)
      moves.push_back(Move(1, d));
    if(posInRange(x-1, y+d) && posColor(x-1, y+d) == cr)
      moves.push_back(Move(-1, d));
    return moves;
  }

  for(Move move : piece->getStaticMoves()) {
    if(posInRange(x+move.dx, y+move.dy) && posColor(x+move.dx, y+move.dy) != c) {
      moves.push_back(move);
    }
  }

  for(Move move : piece->getDynamicMoves()) {
    Move sMove = Move(move.dx, move.dy);
    while(posInRange(x+sMove.dx, y+sMove.dy) && posColor(x+sMove.dx, y+sMove.dy) == -1) {
      moves.push_back(sMove);
      sMove += move;
    }
    if(posInRange(x+sMove.dx, y+sMove.dy) && posColor(x+sMove.dx, y+sMove.dy) != c) {
      moves.push_back(sMove);
    }
  }

  return moves;
}

// Moves the piece if move is allowed and returns pointer to the piece
// that was on the field that we moved onto, or nullptr if none such existed
Piece* CheeseAPI::movePiece(int x, int y, int dx, int dy) {
  if(!posInRange(x, y))
    throw std::invalid_argument("Index out of range!");
  if(!posInRange(x+dx, y+dy))
    throw std::invalid_argument("Move out of range!");
  auto allowedMoves = getPieceAvailableMoves(x, y);
  auto found = std::find(allowedMoves.begin(), allowedMoves.end(), Move(dx, dy));
  if(found == allowedMoves.end())
    throw std::invalid_argument("Invalid move!");
  Piece* old = board[x+dx][y+dy];
  board[x+dx][y+dy] = board[x][y];
  board[x][y] = nullptr;
  return old;
}

std::string CheeseAPI::toString() {
  std::string result;
  for(int y = 0; y < 8; ++y) {
    for(int x = 0; x < 8; ++x) {
      Piece* p = board[x][y];
      if(!p) {
        result += "- ";
      } else { 
        result += p->getName()+' ';
      }
    }
    result += '\n';
  }
  return result;
}

void CheeseAPI::printMoves(int x, int y) {
  std::string result = toString();
  std::vector<Move> moves = getPieceAvailableMoves(x, y);
  for(auto m : moves) {
    int idx = 2*(x+m.dx) + 17*(y+m.dy) + 1;
    result[idx] = '<';
  }
  std::cout << result;
}

std::ostream& operator<<(std::ostream& os, CheeseAPI api) {
  return os << api.toString();
}