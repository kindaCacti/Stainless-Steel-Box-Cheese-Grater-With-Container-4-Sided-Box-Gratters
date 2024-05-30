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
  blackKingPos = Move(4, 0);
  whiteKingPos = Move(4, 7);
}

void CheeseAPI::spawnPiece(Piece* piece, int x, int y, int color) {
  piece->setColor(color);
  board[x][y] = piece;
}

bool CheeseAPI::posInRange(int x, int y) const {
  return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

int CheeseAPI::posColor(int x, int y) const {
  return !board[x][y] ? -1 : board[x][y]->getColor();
}

bool CheeseAPI::isKingInDanger(int color) const {
  Move kingPos = color == COLOR_BLACK ? blackKingPos : whiteKingPos;
  int cr = color == COLOR_BLACK ? COLOR_WHITE : COLOR_BLACK;
  int x = kingPos.dx;
  int y = kingPos.dy;
  auto knightMoves = Knight().getStaticMoves();
  for(auto m : knightMoves) {
    if(posInRange(x+m.dx, y+m.dy)
        && posColor(x+m.dx, y+m.dy) == cr
        && board[x+m.dx][y+m.dy]->getName() == "n"
    ) {
      return true;
    }
  }
  auto kingMoves = King().getStaticMoves();
  for(auto m : kingMoves) {
    if(posInRange(x+m.dx, y+m.dy)
        && posColor(x+m.dx, y+m.dy) == cr
        && board[x+m.dx][y+m.dy]->getName() == "k"
    ) {
      return true;
    }
  }
  int d = color == COLOR_BLACK ? -1 : 1;
  Move pawnMoves[2] = {{-1, d}, {1, d}};
  for(auto m : pawnMoves) {
    if(posInRange(x+m.dx, y+m.dy)
        && posColor(x+m.dx, y+m.dy) == cr
        && board[x+m.dx][y+m.dy]->getName() == "p"
    ) {
      return true;
    }
  }
  auto bishopMoves = Bishop().getDynamicMoves();
  for(auto m : bishopMoves) {
    Move sMove = m;
    while(posInRange(x+sMove.dx, y+sMove.dy) && posColor(x+sMove.dx, y+sMove.dy) == -1) {
      m += m;
    }
    if(posInRange(x+sMove.dx, y+sMove.dy)
        && posColor(x+sMove.dx, y+sMove.dy) == cr
        && (board[x+sMove.dx][y+sMove.dy]->getName() == "b"
            || board[x+sMove.dx][y+sMove.dy]->getName() == "q")
    ) {
      return true;
    }
  }
  auto rookMoves = Rook().getDynamicMoves();
  for(auto m : rookMoves) {
    Move sMove = m;
    while(posInRange(x+sMove.dx, y+sMove.dy) && posColor(x+sMove.dx, y+sMove.dy) == -1) {
      m += m;
    }
    if(posInRange(x+sMove.dx, y+sMove.dy)
        && posColor(x+sMove.dx, y+sMove.dy) == cr
        && (board[x+sMove.dx][y+sMove.dy]->getName() == "r"
            || board[x+sMove.dx][y+sMove.dy]->getName() == "q")
    ) {
      return true;
    }
  }
  return false;
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
  if(posColor(x, y) == -1)
    throw std::invalid_argument("No piece at specified coordinates!");
  if(!posInRange(x+dx, y+dy))
    throw std::invalid_argument("Move out of range!");
  auto allowedMoves = getPieceAvailableMoves(x, y);
  auto found = std::find(allowedMoves.begin(), allowedMoves.end(), Move(dx, dy));
  if(found == allowedMoves.end())
    throw std::invalid_argument("Invalid move!");

  int color = board[x][y]->getColor();
  Piece* old = board[x+dx][y+dy];
  board[x+dx][y+dy] = board[x][y];
  board[x][y] = nullptr;
  if(isKingInDanger(color))
    board[x][y] = board[x+dx][y+dy];
    board[x+dx][y+dy] = old;
    throw std::invalid_argument("King in danger!");
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

std::string CheeseAPI::uniqueStamp(){
  std::string result = "";
  for(int i = 0; i<8; i++)
    for(int j = 0; j<8; j++)
      result+=board[i][j]->uniqueStamp();
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