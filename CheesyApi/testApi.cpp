#include <gtest/gtest.h>
#include "pieces.h"
#include "board.h"
#include "game.h"
#include <string>
#include <iostream>

TEST(TEST_PIECES, CREATE_PIECE){
    Piece tmp = {PIECE_NAMES::BISHOP, PIECE_COLOR::BLACK};

    ASSERT_EQ(tmp.name, PIECE_NAMES::BISHOP);
    ASSERT_EQ(tmp.color, PIECE_COLOR::BLACK);
}

TEST(TEST_PIECES, PIECE_CHAR){
    ASSERT_EQ(pieceChar({PIECE_NAMES::BISHOP, PIECE_COLOR::WHITE}), 'B');
    ASSERT_EQ(pieceChar({PIECE_NAMES::KING, PIECE_COLOR::WHITE}), 'K');
    ASSERT_EQ(pieceChar({PIECE_NAMES::KNIGHT, PIECE_COLOR::WHITE}), 'N');
    ASSERT_EQ(pieceChar({PIECE_NAMES::ROOK, PIECE_COLOR::WHITE}), 'R');
    ASSERT_EQ(pieceChar({PIECE_NAMES::QUEEN, PIECE_COLOR::WHITE}), 'Q');
    ASSERT_EQ(pieceChar({PIECE_NAMES::PAWN, PIECE_COLOR::WHITE}), 'P');
    ASSERT_EQ(pieceChar({PIECE_NAMES::BISHOP, PIECE_COLOR::BLACK}), 'b');
    ASSERT_EQ(pieceChar({PIECE_NAMES::KING, PIECE_COLOR::BLACK}), 'k');
    ASSERT_EQ(pieceChar({PIECE_NAMES::KNIGHT, PIECE_COLOR::BLACK}), 'n');
    ASSERT_EQ(pieceChar({PIECE_NAMES::ROOK, PIECE_COLOR::BLACK}), 'r');
    ASSERT_EQ(pieceChar({PIECE_NAMES::QUEEN, PIECE_COLOR::BLACK}), 'q');
    ASSERT_EQ(pieceChar({PIECE_NAMES::PAWN, PIECE_COLOR::BLACK}), 'p');
}

TEST(TEST_PIECES, TEST_MOVE_OPERATORS){
    Move mv = {1,-1};
    mv = mv*-1;

    ASSERT_EQ(mv.delta_x, -1);
    ASSERT_EQ(mv.delta_y, 1);

    Move tmp1 = {-1,1};
    Move tmp2 = {2,0};

    ASSERT_EQ((mv ==tmp1), true);
    ASSERT_EQ((mv ==tmp2), false);
}

TEST(TEST_PIECES, TEST_MOVE_TO_STRING){
    Move mv = {1,-1};
    ASSERT_EQ(mv.toString(), std::string("1x-1\n"));
}

TEST(TEST_BOARD, SET_PIECES){
    Board b;
    b.setPieces();

    ASSERT_EQ(b.at(0).name, PIECE_NAMES::ROOK);
    ASSERT_EQ(b.at(1).name, PIECE_NAMES::KNIGHT);
    ASSERT_EQ(b.at(2).name, PIECE_NAMES::BISHOP);
    ASSERT_EQ(b.at(3).name, PIECE_NAMES::QUEEN);
    ASSERT_EQ(b.at(4).name, PIECE_NAMES::KING);
    ASSERT_EQ(b.at(5).name, PIECE_NAMES::BISHOP);
    ASSERT_EQ(b.at(6).name, PIECE_NAMES::KNIGHT);
    ASSERT_EQ(b.at(7).name, PIECE_NAMES::ROOK);

    ASSERT_EQ(b.at(56).name, PIECE_NAMES::ROOK);
    ASSERT_EQ(b.at(57).name, PIECE_NAMES::KNIGHT);
    ASSERT_EQ(b.at(58).name, PIECE_NAMES::BISHOP);
    ASSERT_EQ(b.at(59).name, PIECE_NAMES::QUEEN);
    ASSERT_EQ(b.at(60).name, PIECE_NAMES::KING);
    ASSERT_EQ(b.at(61).name, PIECE_NAMES::BISHOP);
    ASSERT_EQ(b.at(62).name, PIECE_NAMES::KNIGHT);
    ASSERT_EQ(b.at(63).name, PIECE_NAMES::ROOK);

    ASSERT_EQ(b.at(8).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(9).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(10).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(11).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(12).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(13).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(14).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(15).name, PIECE_NAMES::PAWN);

    ASSERT_EQ(b.at(48).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(49).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(50).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(51).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(52).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(53).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(54).name, PIECE_NAMES::PAWN);
    ASSERT_EQ(b.at(55).name, PIECE_NAMES::PAWN);
}

TEST(TEST_BOARD, TO_STRING){
    Board b;
    b.setPieces();

    std::string tmp = "r n b q k b n r\np p p p p p p p\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\nP P P P P P P P\nR N B Q K B N R";
    ASSERT_EQ(b.toString(), tmp);
}

TEST(TEST_BOARD, GENERATE_MOVES){
    Board b;
    b.setPieces();

    std::vector<Move> tmp = b.getMoves(0, 1);
    ASSERT_EQ(tmp.size(), 2);

    tmp = b.getMoves(0,0);
    ASSERT_EQ(tmp.size(), 0);

    tmp = b.getMoves(1, 0);
    ASSERT_EQ(tmp.size(), 2);
}

TEST(TEST_BOARD, GET_MOVES_OF_COLOR){
    Board b;
    b.setPieces();
    int tmp = b.getMovesOfColor(PIECE_COLOR::WHITE).size();

    ASSERT_EQ(tmp, 20);
}

TEST(TEST_BOARD, MAKE_MOVE){
    Board b;
    b.setPieces();

    b.makeMove(0,0, {2, 2});

    ASSERT_EQ(b.at(2,2).name, PIECE_NAMES::ROOK);
}

TEST(TEST_BOARD, IS_KING_UNDER_ATTACK){
    Board b;
    b.setPieces();
    
    ASSERT_EQ(b.isKingUnderAttack(PIECE_COLOR::BLACK), false);
    b.makeMove(3,7, {0, -7});

    ASSERT_EQ(b.isKingUnderAttack(PIECE_COLOR::BLACK), true);
}

TEST(TEST_BOARD, IS_CHECKMATE){
    Board b;
    b.setPieces();
    
    ASSERT_EQ(b.isCheckmate(PIECE_COLOR::BLACK), false);
    b.makeMove(3,7, {0, -7});
    b.makeMove(3,6, {1, -5});

    ASSERT_EQ(b.isCheckmate(PIECE_COLOR::BLACK), true);
}

TEST(TEST_GAME, CREATE_GAME){
    Game g;
    ASSERT_EQ(g.getRound(), 1);
    ASSERT_EQ(g.isOngoing(), true);
    ASSERT_EQ(g.turnOf(), PIECE_COLOR::WHITE);
}

TEST(TEST_GAME, NEXT_TURN){
    Game g;
    g.nextTurn();
    g.nextTurn();
    g.nextTurn();
    g.nextTurn();
    g.nextTurn();
    ASSERT_EQ(g.getRound(), 6);
    ASSERT_EQ(g.isOngoing(), true);
    ASSERT_EQ(g.turnOf(), PIECE_COLOR::BLACK);
}

TEST(TEST_GAME, TRANSATE_TO_MOVE_INDEX){
    Game g;
    int tmp = g.translateToMoveIndex('c', '5');
    ASSERT_EQ(tmp, 26);
    tmp = g.translateToMoveIndex('e', '1');
    ASSERT_EQ(tmp, 60);
}

TEST(TEST_GAME, MAKE_MOVE){
    Game g;
    bool tmp = g.choosePiece('c', '3', std::cout);
    ASSERT_EQ(tmp, false);
    tmp = g.choosePiece('c', '2', std::cout);
    ASSERT_EQ(tmp, true);
    tmp = g.makeMove('c', '2');
    ASSERT_EQ(tmp, false);
    tmp = g.makeMove('c', '3');
    ASSERT_EQ(tmp, false);
}

TEST(TEST_GAME, IS_END){
    Game g;
    g.isEnd(std::cout);
    ASSERT_EQ(g.isOngoing(), true);
    Board& b = g.getBoard();
    b.makeMove(3,7, {0, -7});
    b.makeMove(3,6, {1, -5});
    g.nextTurn();
    g.isEnd(std::cout);
    ASSERT_EQ(g.isOngoing(), false);
}

