#pragma once
#include "../CheesyApi/board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>


class Bot {

  struct MovePackage {
    int fx, fy;
    Move mv;
  };

  std::vector<Piece *> tree;
  std::vector<double> score, evalScore;
  std::vector<int> depth, parent;
  std::vector<MovePackage> toHere;
  std::vector<bool> done;
  std::vector<MovePackage> bestMove;

public:
  Bot() = default;
  Bot(Board &board) {
    tree.push_back(board.getBoard());
    depth.push_back(0);
    parent.push_back(-1);
    toHere.push_back({0, 0, {0, 0}});
  }

  void addBranches(int round, int from) {
    // std::cout<<"for round: "<<depth[from]<<std::endl;
    Board board(tree[from]);

    PIECE_COLOR currentColor =
        (round % 2) ? PIECE_COLOR::WHITE : PIECE_COLOR::BLACK;

    // std::cout<<"hi\n";

    for (int i = 0; i < 64; i++) {
      // std::cout<<"starting "<<i<<std::endl;
      int x = i % 8;
      int y = i / 8;

      if (board.at(i).name == PIECE_NAMES::NO_PIECE)
        continue;
      if (board.at(i).color != currentColor)
        continue;

      // std::cout<<"getting moves\n";
      std::vector<Move> moves = board.getMoves(x, y);
      // std::cout<<"movs: "<<moves.size()<<std::endl;
      // std::cout<<"hihi\n";
      for (Move mv : moves) {
        // std::cout<<board.toString()<<std::endl;
        // std::cout<<"trying: "<<x<<"x"<<y<<"
        // "<<mv.delta_x<<"x"<<mv.delta_y<<std::endl;
        depth.push_back(depth[from] + 1);
        parent.push_back(from);
        Board tmp(board.getBoard());
        tmp.makeMove(x, y, mv);
        // std::cout<<tmp.toString()<<std::endl;
        tree.push_back(tmp.getBoard());
        toHere.push_back({x, y, mv});
      }
      // std::cout<<"ended\n";
    }
  }

  void fillTree(int round, int maxDepth = 2) {
    for (int i = 0; i < tree.size(); i++) {
      // std::cout<<depth[i]<<" : dep\n";
      // std::cout<<"hello2\n";
      if (depth[i] >= maxDepth)
        break;
      addBranches(round + depth[i], i);
    }
  }

  int evalutateBranch(int branchIndex) {
    int out = 0;
    for (int i = 0; i < 64; i++) {
      int tmp = pieceValues(tree[branchIndex][i].name);
      if (!depth[branchIndex] % 2)
        tmp *= -1;

      out += tmp;
    }

    return out;
  }

  void evaluateTree() {
    score.assign(tree.size(), 0);

    for (int i = 1; i < tree.size(); i++) {
      score[i] = evalutateBranch(i);
    }

    done.assign(tree.size(), 0);
    bestMove.assign(tree.size(), {});
    evalScore.assign(tree.size(), 0);

    for (int i = tree.size() - 1; i > 0; i--) {
      // std::cout<<"hello\n";
      int prev = parent[i];
      if (!done[prev]) {
        evalScore[prev] = score[i] * ((depth[i] % 2) ? 1 : -1);
        bestMove[prev] = toHere[i];
        done[prev] = 1;
      }

      if (evalScore[i] * ((depth[i] % 2) ? 1 : -1) > evalScore[prev]) {
        evalScore[prev] = evalScore[i];
        bestMove[prev] = toHere[i];
      }
    }
  }

  std::vector<int> getBestMove(int round, int dep = 2) {
    fillTree(round, dep);

    // std::cout<<"eval\n";
    evaluateTree();

    return {bestMove[0].fx, bestMove[0].fy,
            bestMove[0].fx + bestMove[0].mv.delta_x,
            bestMove[0].fy + bestMove[0].mv.delta_y};
  }

  std::vector<int> getRandomMove(int round) {
    srand(time(NULL));
    Board tmp(tree[0]);

    std::vector<MovePackage> possibleMoves;
    PIECE_COLOR currentColor =
        (round % 2) ? PIECE_COLOR::WHITE : PIECE_COLOR::BLACK;
    for (int i = 0; i < 64; i++) {
      if (tmp.at(i).name == PIECE_NAMES::NO_PIECE)
        continue;
      if (tmp.at(i).color != currentColor)
        continue;

      int x = i % 8;
      int y = i / 8;
      std::vector<Move> moves = tmp.getMoves(x, y);
      for (int i = 0; i < moves.size(); i++) {
        possibleMoves.push_back({x, y, moves[i]});
      }
    }

    int choosen = rand() % possibleMoves.size();
    int ex = possibleMoves[choosen].fx + possibleMoves[choosen].mv.delta_x;
    int ey = possibleMoves[choosen].fy + possibleMoves[choosen].mv.delta_y;

    return {possibleMoves[choosen].fx, possibleMoves[choosen].fy, ex, ey};
  }

  std::string convertToChessNotation(int x, int y) {
    y = 7 - y;

    std::string out = "";
    out.push_back('a' + x);
    out.push_back('1' + y);

    return out;
  }
};