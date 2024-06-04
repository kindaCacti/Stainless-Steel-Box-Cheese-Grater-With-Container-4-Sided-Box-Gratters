#pragma once
#include "board.h"
#include "pieces.h"
#include <string>
#include <vector>

class Game {
  int round;
  PIECE_COLOR turn;
  Board gameBoard;
  bool ongoing;
  int selectedPieceIndex;
  std::vector<Move> possibleMoves;

public:
  Game();
  int getRound() { return round; }
  PIECE_COLOR turnOf() { return turn; }
  std::string showGame() const;
  bool isOngoing() { return ongoing; }
  std::string askForMovement() {
    return std::string("Choose a piece, which you want to move (type location "
                       "of the piece you want to move e.g. a5): ");
  }
  int translateToMoveIndex(char, char);
  bool choosePiece(char, char, std::ostream&);
  bool choosePiece(char, char);
  bool movePiece(std::string, std::string);
  std::string translateToChessCoordinates(Move);
  void showPossibleMoves(std::ostream&);
  void loadPossibleMoves();
  std::vector<Move>& getPossibleMoves() { return possibleMoves; };
  void nextTurn();
  bool makeMove(char, char);
  bool isEnd(std::ostream&);
  Board &getBoard() { return gameBoard; }
  friend std::ostream &operator<<(std::ostream &os, const Game game) { return os << game.showGame(); }
  Move& revInY(Move& a) { a.delta_y *= -1; return a; }
};