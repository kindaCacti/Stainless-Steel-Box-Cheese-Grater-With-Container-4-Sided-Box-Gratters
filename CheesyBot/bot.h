#pragma once
#include "../CheesyApi/piece.h"
#include "../CheesyApi/cheeseApi.h"
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>

class CheeseBotAPI{
    std::vector<CheeseAPI> tree;
    std::vector<int> edges, depth;
    std::set<std::string> checked;
    std::vector<double> weighs;

    void copyBoard(CheeseAPI& from, CheeseAPI& to){
        for(int i = 0; i<8; i++){
            for(int j = 0; j<8; j++){
                if(from.at(i, j) == nullptr) continue;

                to.setBoard(new Piece(*from.at(i, j)), i, j);
            }
        }
    }

    void generateTree(CheeseAPI board, int cameFrom){
        for(int i = 0; i<8; i++){
            for(int j = 0; j<8; j++){
                std::vector<Move> moves = board.getPieceAvailableMoves(i, j);
                for(int k = 0; k<moves.size(); k++){
                    try{
                        CheeseAPI tmp(board);
                        copyBoard(board, tmp);
                        tmp.movePiece(i, j, moves[k].dx, moves[k].dy);
                        if(checked.find(tmp.toString()) != checked.end()) continue;
                        checked.insert(tmp.toString());
                        tree.push_back(tmp);
                        depth.push_back(depth[cameFrom]+1);
                        edges.push_back(cameFrom);
                    }catch(std::invalid_argument a){
                        std::cout<<i<<" "<<j<<" to "<<i+moves[k].dx<<" "<<j+moves[k].dy<<" "<<a.what()<<std::endl;
                    }
                }
            }
        }
    }

    void resolveTree(){
        std::vector<bool> done;
        done.assign(tree.size(), 0);


    }

public:
    void getMove(CheeseAPI board, int maxDepth = 4){
        tree.push_back(board);
        depth.push_back(0);
        for(int i = 0; i<tree.size(); i++){
            if(depth[i] == maxDepth) break;
            generateTree(tree[i], i);
        }
    }

    int getTreeSize(){
        return tree.size();
    }
};