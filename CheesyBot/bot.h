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

    void generateTree(CheeseAPI board, int cameFrom){
        for(int i = 0; i<8; i++){
            for(int j = 0; j<8; j++){
                std::vector<Move> moves = board.getPieceAvailableMoves(i, j);
                for(int k = 0; k<moves.size(); k++){
                    try{
                        std::cout<<k<<" : k\n";
                        CheeseAPI tmp(board);
                        std::cout<<tmp<<std::endl;
                        std::cout<<"move 1 \n";
                        tmp.movePiece(i, j, moves[k].dx, moves[k].dy);
                        std::cout<<"move 2 \n";
                        if(checked.find(tmp.toString()) != checked.end()) continue;
                        std::cout<<"move3\n";
                        checked.insert(tmp.toString());
                        tree.push_back(tmp);
                        depth.push_back(depth[cameFrom]+1);
                        edges.push_back(cameFrom);
                        std::cout<<depth.back()<<" : depth\n";
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
    void getMove(CheeseAPI board, int maxDepth = 2){
        tree.push_back(board);
        depth.push_back(0);
        for(int i = 0; i<tree.size(); i++){
            if(depth[i] == maxDepth) break;
            generateTree(tree[i], i);
            std::cout<<tree.size()<<" :siz"<<"\n";
        }
    }

    int getTreeSize(){
        return tree.size();
    }
};