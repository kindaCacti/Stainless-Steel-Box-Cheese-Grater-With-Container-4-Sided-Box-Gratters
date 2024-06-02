#pragma once
#include "../CheesyApi/piece.h"
#include "../CheesyApi/cheeseApi.h"
#include "eval_tables.h"
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>


class CheeseBotAPI{
    int color = 1;
    std::vector<std::pair<CheeseAPI, Move>> tree;
    std::vector<int> edges, depth;
    std::set<std::string> checked;
    std::vector<double> weighs;
    std::vector<std::pair<double, int>> eval;

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
                        tree.push_back({tmp, Move(moves[k])});
                        depth.push_back(depth[cameFrom]+1);
                        edges.push_back(cameFrom);
                    }catch(std::invalid_argument a){
                        std::cout<<i<<" "<<j<<" to "<<i+moves[k].dx<<" "<<j+moves[k].dy<<" "<<a.what()<<std::endl;
                    }
                }
            }
        }
    }

    double evaluate(CheeseAPI& board){
        double out = 0;
        for(int i = 0; i<8; i++){
            for(int j = 0; j<8; j++){
                auto tmp = board.at(i, j);
                if(tmp == nullptr) continue;

                out += tmp->getWeight() * (color == tmp->getColor()? 1 : -1);
            }
        }

        return out;
    }

    void resolveTree(){
        eval.assign(tree.size(), {{}, -1});
        std::vector<bool> done;
        done.assign(tree.size(), 0);

        for(int i = tree.size() - 1; i>0; i--){
            double tmp = evaluate(tree[i].first);
            int prev = edges[i];
            if(depth[i] % 2){
                if(eval[prev].first < tmp or !done[prev]){
                    eval[prev] = {tmp, i};
                    done[prev] = true;
                }
                continue;
            }

            if(eval[prev].first > tmp or !done[prev]){
                eval[prev] = {tmp, i};
                done[prev] = true;
            }
        }
    }

public:
    Move getMove(CheeseAPI board, int maxDepth = 2){
        tree.push_back({board, {}});
        depth.push_back(0);
        for(int i = 0; i<tree.size(); i++){
            if(depth[i] == maxDepth) break;
            generateTree(tree[i].first, i);
        }

        resolveTree();
        return tree[0].second;
    }

    void showResolvedTree(){
        int cpos = 0;
        while(eval[cpos].second != -1){
            cpos = eval[cpos].second;
            std::cout<<tree[cpos].second<<std::endl;
        }
    }

    int getTreeSize(){
        return tree.size();
    }
};