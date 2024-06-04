#include "game.h"

Game::Game(){
    round = 1;
    gameBoard.setPieces();
    turn = PIECE_COLOR::WHITE;
    ongoing = true;
}

std::string Game::showGame() const {
    std::string out = "Round number: " + std::to_string(round);
    out += "\nTurn of: ";
    if (turn == PIECE_COLOR::WHITE)
        out += "White\n";
    else
        out += "Black\n";
    out += "\n";
    out += gameBoard.toString();
    return out;
}

int Game::translateToMoveIndex(char movX, char movY) {
    int out = movX - 'a';
    if (out < 0 or out > 7) return -1;

    int ypos = movY - '1';
    if (ypos < 0 or ypos > 7) return -1;

    out += (7 - ypos) * 8;
    return out;
}

bool Game::choosePiece(char movX, char movY, std::ostream &os) {
    possibleMoves.clear();
    int index = translateToMoveIndex(movX, movY);

    if (index == -1) {
      os << "Position does not exist!!" << std::endl;
      return false;
    }

    if (gameBoard.at(index).name == PIECE_NAMES::NO_PIECE) {
      os << "no piece at given position" << std::endl;
      return false;
    }

    if (gameBoard.at(index).color != turn) {
      os << "Incorrect piece selected!!" << std::endl;
      return false;
    }

    selectedPieceIndex = index;
    return true;
}

std::string Game::translateToChessCoordinates(Move mv) {
    int movX = selectedPieceIndex % 8;
    int movY = selectedPieceIndex / 8;

    int addx = movX + mv.delta_x;
    int addy = movY + mv.delta_y;

    addy = 7 - addy;

    std::string out = "";
    out.push_back('a' + addx);
    out.push_back('1' + addy);

    return out;
}

void Game::showPossibleMoves(std::ostream &os) {
    possibleMoves.clear();
    int movX = selectedPieceIndex % 8;
    int movY = selectedPieceIndex / 8;

    std::vector<Move> moves = gameBoard.getMoves(movX, movY);

    for (Move mv : moves) {
      possibleMoves.push_back(mv);
      os << translateToChessCoordinates(mv) << std::endl;
    }
}

void Game::nextTurn() {
    round++;
    turn = (turn == PIECE_COLOR::WHITE) ? PIECE_COLOR::BLACK : PIECE_COLOR::WHITE;
}

bool Game::makeMove(char x, char y) {
    int sx = selectedPieceIndex % 8;
    int sy = selectedPieceIndex / 8;

    int endingIndex = translateToMoveIndex(x, y);
    int ex = endingIndex % 8;
    int ey = endingIndex / 8;

    Move mv = {ex - sx, ey - sy};

    for (int i = 0; i < possibleMoves.size(); i++) {
      if (possibleMoves[i] == mv) {
        gameBoard.makeMove(sx, sy, mv);
        nextTurn();
        return true;
      }
    }
    return false;
}

bool Game::isEnd(std::ostream &os) {
    if (gameBoard.isCheckmate(turn)) {
      os << "CHECKMATE!!" << std::endl;
      ongoing = false;
      return true;
    }

    if (gameBoard.isStalemate(turn)) {
      os << "STALEMATE!!" << std::endl;
      ongoing = false;
      return true;
    }

    if (gameBoard.isKingUnderAttack(turn)) {
      os << "CHECK!!" << std::endl;
      return false;
    }

    return !ongoing;
}