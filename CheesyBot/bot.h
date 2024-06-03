#pragma once
#include "../CheesyApi/board.h"
#include <vector>

class Bot{

    struct MovePackage{
        int fx, fy;
        Move mv;
    };

    std::vector<Piece*> tree;
    std::vector<double> score;
    std::vector<int> depth, parent;
    std::vector<MovePackage> toHere; 

public:
    Bot() = default;
    Bot(Board& board){
        tree.push_back(board.getBoard());
        depth.push_back(0);
        parent.push_back(-1);
        toHere.push_back({0,0,{0,0}});
    }

    void addBranches(int round, Piece* pieces, int from){
        Board board(pieces);

        PIECE_COLOR currentColor = (round%2) ? PIECE_COLOR::WHITE : PIECE_COLOR::BLACK;

        for(int i = 0; i<64; i++){
            int x = i%8;
            int y = i/8;

            if(board.at(i).name == PIECE_NAMES::NO_PIECE) continue;
            if(board.at(i).color != currentColor) continue;

            std::vector<Move> moves = board.getMoves(x, y);

            for(Move mv : moves){
                depth.push_back(depth[from] + 1);
                parent.push_back(from);
                Board tmp(pieces);
                tmp.makeMove(x, y, mv);
                tree.push_back(tmp.getBoard());
            }
        }
    }

    void fillTree(int round, int maxDepth = 2){
        for(int i = 0; i<tree.size(); i++){
            if(depth[i] == maxDepth) break;
            addBranches(round + depth[i], tree[i]);
        }
    }

    int evalutateBranch(int branchIndex){
        int out = 0;
        for(int i = 0; i<64; i++){
            int tmp = pieceValues(tree[branchIndex][i].name);
            if(!depth[branchIndex]%2) tmp *= -1;

            out += tmp; 
        }

        return out;
    }

    void evaluateTree(){
        score.assign(tree.size(), 0);

        for(int i = 1; i<tree.size(); i++){
            score[i] = evalutateBranch(tree[i]);
        }
    }
};