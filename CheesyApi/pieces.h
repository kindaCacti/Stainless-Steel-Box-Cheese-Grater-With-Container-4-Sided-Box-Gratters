#pragma once
#include <vector>

enum class PIECE_COLOR{
    WHITE, BLACK
};

enum class PIECE_NAMES{
    NO_PIECE, PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING
};

enum class MOVES{
    UP, DOWN, LEFT, RIGHT,
    UL_DIAG, UR_DIAG, DL_DIAG, DR_DIAG,
    LSHAPE1, LSHAPE2, LSHAPE3, LSHAPE4, LSHAPE5, LSHAPE6, LSHAPE7, LSHAPE8,
    PAWN_MOVES, CASTLE
};

struct Move{
    int delta_x;
    int delta_y;

    Move operator*(int a) const{
        return {delta_x * a, delta_y * a};
    }

    bool operator==(Move& mv){
        if(mv.delta_x == delta_x and mv.delta_y == delta_y) return true;
        return false;
    }

    std::string toString() const{
        return std::to_string(delta_x) + "x"+std::to_string(delta_y) + "\n";
    }
};

struct Piece{
    PIECE_NAMES name;
    PIECE_COLOR color;
    int moves_done = 0;
};

struct MovePossibilities{
    std::vector<MOVES> repeatingMoves;
    std::vector<MOVES> singleMoves;
};

char pieceChar(Piece tp){

    int nameCharOffset = (tp.color == PIECE_COLOR::BLACK) * 32;

    int out = '.';

    switch(tp.name){
        case PIECE_NAMES::PAWN:
            out = 'P';
            break;
        case PIECE_NAMES::BISHOP:
            out = 'B';
            break;
        case PIECE_NAMES::KNIGHT:
            out = 'N';
            break;
        case PIECE_NAMES::ROOK:
            out = 'R';
            break;
        case PIECE_NAMES::QUEEN:
            out = 'Q';
            break;
        case PIECE_NAMES::KING:
            out = 'K';
            break;
    }
    
    if(out != '.') out += nameCharOffset;
    return out;
}

MovePossibilities getBaseMoves(PIECE_NAMES pn, int moves_done = 0){
    switch(pn){
        case PIECE_NAMES::PAWN:
            if(!moves_done) return {{}, {MOVES::UP, MOVES::PAWN_MOVES}};
            return {{}, {MOVES::UP}};
        case PIECE_NAMES::BISHOP:
            return {{MOVES::UL_DIAG, MOVES::UR_DIAG, MOVES::DL_DIAG, MOVES::DR_DIAG}, {}};
        case PIECE_NAMES::ROOK:
            return {{MOVES::UP, MOVES::DOWN, MOVES::LEFT, MOVES::RIGHT}, {}};
        case PIECE_NAMES::KNIGHT:
            return {{}, {MOVES::LSHAPE1, MOVES::LSHAPE2, MOVES::LSHAPE3, MOVES::LSHAPE4, MOVES::LSHAPE5, MOVES::LSHAPE6, MOVES::LSHAPE7, MOVES::LSHAPE8}};
        case PIECE_NAMES::QUEEN:
            return {{MOVES::UP, MOVES::DOWN, MOVES::LEFT, MOVES::RIGHT, MOVES::UL_DIAG, MOVES::UR_DIAG, MOVES::DL_DIAG, MOVES::DR_DIAG}, {}};
        case PIECE_NAMES::KING:
            return {{}, {MOVES::UP, MOVES::DOWN, MOVES::LEFT, MOVES::RIGHT, MOVES::UL_DIAG, MOVES::UR_DIAG, MOVES::DL_DIAG, MOVES::DR_DIAG, MOVES::CASTLE}};
    }
    return {{},{}};
}

Move translateMoves(MOVES mov){
    switch(mov){
        case MOVES::UP:
            return {0, 1};
        case MOVES::DOWN:
            return {0, -1};
        case MOVES::LEFT:
            return {-1, 0};
        case MOVES::RIGHT:
            return {1, 0};
        case MOVES::UL_DIAG:
            return {-1, 1};
        case MOVES::DL_DIAG:
            return {-1, -1};
        case MOVES::UR_DIAG:
            return {1, 1};
        case MOVES::DR_DIAG:
            return {1, -1};
        case MOVES::LSHAPE1:
            return {2, 1};
        case MOVES::LSHAPE2:
            return {-2, 1};
        case MOVES::LSHAPE3:
            return {2, -1};
        case MOVES::LSHAPE4:
            return {-2, -1};
        case MOVES::LSHAPE5:
            return {1, 2};
        case MOVES::LSHAPE6:
            return {1, -2};
        case MOVES::LSHAPE7:
            return {-1, 2};
        case MOVES::LSHAPE8:
            return {-1, -2};
        case MOVES::PAWN_MOVES:
            return {0, 2};
    }
    return {0, 0};
}
