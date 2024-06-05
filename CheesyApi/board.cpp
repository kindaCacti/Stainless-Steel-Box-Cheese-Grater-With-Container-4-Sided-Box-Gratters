#include "board.h"

Board::Board(Piece* _board){
    for(int i = 0; i<64; i++){
        board[i] = Piece(_board[i].name, _board[i].color, _board[i].moves_done);
    }
}

void Board::setPieces(){
    int resolve = 0;

    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            board[resolve] = Piece(PIECE_NAMES::NO_PIECE);
            resolve++;
        }
    }

    for(int i = 0; i<8; i++){
        board[8 + i] =  {PIECE_NAMES::PAWN, PIECE_COLOR::BLACK};
        board[48 + i] = {PIECE_NAMES::PAWN, PIECE_COLOR::WHITE};
    }

    board[0] = {PIECE_NAMES::ROOK,      PIECE_COLOR::BLACK};
    board[1] = {PIECE_NAMES::KNIGHT,    PIECE_COLOR::BLACK};
    board[2] = {PIECE_NAMES::BISHOP,    PIECE_COLOR::BLACK};
    board[3] = {PIECE_NAMES::QUEEN,     PIECE_COLOR::BLACK};
    board[4] = {PIECE_NAMES::KING,      PIECE_COLOR::BLACK};
    board[5] = {PIECE_NAMES::BISHOP,    PIECE_COLOR::BLACK};
    board[6] = {PIECE_NAMES::KNIGHT,    PIECE_COLOR::BLACK};
    board[7] = {PIECE_NAMES::ROOK,      PIECE_COLOR::BLACK};

    board[56] = {PIECE_NAMES::ROOK,     PIECE_COLOR::WHITE};
    board[57] = {PIECE_NAMES::KNIGHT,   PIECE_COLOR::WHITE};
    board[58] = {PIECE_NAMES::BISHOP,   PIECE_COLOR::WHITE};
    board[59] = {PIECE_NAMES::QUEEN,    PIECE_COLOR::WHITE};
    board[60] = {PIECE_NAMES::KING,     PIECE_COLOR::WHITE};
    board[61] = {PIECE_NAMES::BISHOP,   PIECE_COLOR::WHITE};
    board[62] = {PIECE_NAMES::KNIGHT,   PIECE_COLOR::WHITE};
    board[63] = {PIECE_NAMES::ROOK,     PIECE_COLOR::WHITE};
}

std::string Board::toString() const{
    int resolve = 0;
    std::string out = "";

    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            out.push_back(pieceChar(board[resolve]));
            out.push_back(' ');
            resolve++;
        }
        out.pop_back();
        out.push_back('\n');
    }
    out.pop_back();

    return out;
}

Piece Board::at(int x, int y){
    if(x<0 or x > 7 or y<0 or y>7) return Piece(PIECE_NAMES::NO_PIECE);
    int index = y*8 + x;
    return board[index];
}

std::vector<Move> Board::generateMoves(Move mv, int fx, int fy, int amm, bool check){
    std::vector<Move> out;

    for(int i = 1; i<=amm; i++){
        Move nm(mv*i);
        int nx = fx + nm.delta_x;
        int ny = fy + nm.delta_y;

        if(nx < 0 or nx > 7 or ny < 0 or ny > 7) break;

        Board nextBoard(this->board);
        nextBoard.makeMove(fx, fy, nm);
        PIECE_COLOR pc = board[fx + fy*8].color;

        if(at(nx, ny).name == PIECE_NAMES::NO_PIECE){
            out.push_back(nm);
            if(check and nextBoard.isKingUnderAttack(pc, false)) out.pop_back();
            continue;
        }

        out.push_back(nm);
        if(at(fx, fy).color == at(nx, ny).color) out.pop_back();
        else if(at(fx, fy).name == PIECE_NAMES::PAWN) out.pop_back();
        else if(check and nextBoard.isKingUnderAttack(pc, false)) out.pop_back();

        break;
    }

    return out;
}

void Board::reverseMove(Move& mv){
    mv.delta_x *= -1;
    mv.delta_y *= -1;
}

int Board::getKingPosition(PIECE_COLOR pc){
    for(int i = 0; i<64; i++){
        if(board[i].name == PIECE_NAMES::KING and board[i].color == pc){
            return i;
        }
    }
    return -1;
}

bool Board::isKingUnderAttack(PIECE_COLOR pc, bool check){
    int kingPos = getKingPosition(pc);
    for(int i = 0; i<64; i++){
        if(board[i].name == PIECE_NAMES::NO_PIECE) continue;
        if(pc != board[i].color){
            int x = i%8;
            int y = i/8;
            std::vector<Move> tmp = getMoves(x, y, check);

            for(int j = 0; j<tmp.size(); j++){
                int nx = x + tmp[j].delta_x;
                int ny = y + tmp[j].delta_y;
                if(nx + ny*8 == kingPos) return true;
            }
        }
    }
    return false;
}

void Board::makeMove(int fx, int fy, Move mv){
    Piece tmp = board[fx + fy*8];
    board[fx + fy*8] = Piece(PIECE_NAMES::NO_PIECE);
    tmp.moves_done++;
    int tx = mv.delta_x + fx;
    int ty = mv.delta_y + fy;
    board[tx + ty*8] = tmp;

    if(at(tx, ty).name == PIECE_NAMES::KING and mv.delta_x == 2){
        Piece tmp = at(7, fy);
        setAt(5, fy, tmp);
        board[fy*8+5].moves_done = -1;
        board[7+8*fy] = Piece(PIECE_NAMES::NO_PIECE);
    }

    if(at(tx, ty).name == PIECE_NAMES::KING and mv.delta_x == -2){
        Piece tmp = at(0, fy);
        setAt(3, fy, tmp);
        board[fy*8+3].moves_done = -1;
        board[0+8*fy] = Piece(PIECE_NAMES::NO_PIECE);
    }

    promote();
}

bool Board::canPawnTake(int x, int y, int way, bool check){
    Piece cp = at(x, y);

    if(cp.name != PIECE_NAMES::PAWN) return false;

    Move tm = {1,1};
    if(way < 0) tm.delta_x *= -1;
    if(cp.color == PIECE_COLOR::WHITE) tm.delta_y *= -1;

    int ex = x + tm.delta_x;
    int ey = y + tm.delta_y;

    if(ex < 0 or ey < 0 or ex > 7 or ey > 7) return false;
    if(at(ex, ey).name == PIECE_NAMES::NO_PIECE) return false;
    if(cp.color == at(ex, ey).color) return false;

    Board nextBoard(this->board);
    nextBoard.makeMove(x, y, tm);
    if(check and nextBoard.isKingUnderAttack(cp.color)) return false;

    return true;
}

bool Board::canPawnDoubleMove(int x, int y, bool check){
    Piece cp = at(x, y);

    if(cp.name != PIECE_NAMES::PAWN) return false;
    if(cp.moves_done != 0) return false;

    Move smv = {0, 1};
    Move dmv = {0, 2};
    if(cp.color == PIECE_COLOR::WHITE){
        reverseMove(smv);
        reverseMove(dmv);
    }

    if(at(x, y+smv.delta_y).name != PIECE_NAMES::NO_PIECE) return false;
    if(at(x, y+dmv.delta_y).name != PIECE_NAMES::NO_PIECE) return false;

    Board nextBoard(this->board);
    nextBoard.makeMove(x, y, dmv);

    if(check and isKingUnderAttack(cp.color)) return false;

    return true;
}

bool Board::canCastle(int x, int y, int way, bool check){
    Piece cp = at(x, y);

    if(cp.name != PIECE_NAMES::KING) return false;
    if(cp.moves_done != 0) return false;

    Move mv = {1, 0};
    int k = ((way < 0)? 3 : 4);
    int mul = ((way < 0)? -1 : 1);
    for(int i = 1; i<k; i++){
        if(at(x + i*mul, y).name != PIECE_NAMES::NO_PIECE) return false;
    }

    for(int i = 0; i<k; i++){
        Board nextBoard(this->board);
        nextBoard.makeMove(x, y, mv * (i*mul));
        if(nextBoard.isKingUnderAttack(cp.color)) return false;
    }

    return true;
}

std::vector<Move> Board::getMoves(int x, int y, bool check){
    int index = y*8 + x;
    if(board[index].name == PIECE_NAMES::NO_PIECE) return {};

    std::vector<Move> out;
    MovePossibilities mp = getBaseMoves(board[index].name, board[index].moves_done);

    for(int i = 0; i<mp.singleMoves.size(); i++){
        Move translatedMove = translateMoves(mp.singleMoves[i]);
        if(board[index].color == PIECE_COLOR::WHITE) reverseMove(translatedMove);
        std::vector<Move> tmp = generateMoves(translatedMove, x, y, 1, check);
        std::copy(tmp.begin(), tmp.end(), std::back_inserter(out));
    }

    for(int i = 0; i<mp.repeatingMoves.size(); i++){
        Move translatedMove = translateMoves(mp.repeatingMoves[i]);
        if(board[index].color == PIECE_COLOR::WHITE) reverseMove(translatedMove);
        std::vector<Move> tmp = generateMoves(translatedMove, x, y, 8, check);
        std::copy(tmp.begin(), tmp.end(), std::back_inserter(out));
    }

    if(at(x, y).name == PIECE_NAMES::PAWN){

        Move mv1 = { 1, 1};
        Move mv2 = {-1, 1};
        Move dmv = {0, 2};

        if(at(x, y).color == PIECE_COLOR::WHITE){
            mv1.delta_y *= -1;
            mv2.delta_y *= -1;
            reverseMove(dmv);
        }

        if(canPawnTake(x, y,  1, check)) out.push_back(mv1);
        if(canPawnTake(x, y, -1, check)) out.push_back(mv2);
        if(canPawnDoubleMove(x, y, check)) out.push_back(dmv);
    }

    if(at(x, y).name == PIECE_NAMES::KING){
        Move castleMove = {1, 0};
        if(canCastle(x, y, -1, check)) out.push_back(castleMove * (-2));
        if(canCastle(x, y,  1, check)) out.push_back(castleMove * 2);
    }

    return out;
}

std::vector<Move> Board::getMovesOfColor(PIECE_COLOR pc, bool check){
    std::vector<Move> out;
    for(int i = 0; i<64; i++){
        if(board[i].name == PIECE_NAMES::NO_PIECE) continue;
        if(board[i].color != pc) continue;

        int x = i%8;
        int y = i/8;
        std::vector<Move> tmp = getMoves(x, y, check);
        std::copy(tmp.begin(), tmp.end(), std::back_inserter(out));
    }

    return out;
}

bool Board::isCheckmate(PIECE_COLOR pc){
    int kingPos = getKingPosition(pc);
    int kx = kingPos%8;
    int ky = kingPos/8;
    if(isKingUnderAttack(pc) and getMovesOfColor(pc).size() == 0) return true;
    return false;
}

bool Board::isStalemate(PIECE_COLOR pc){
    int kingPos = getKingPosition(pc);
    int kx = kingPos%8;
    int ky = kingPos/8;
    if(!isKingUnderAttack(pc) and getMovesOfColor(pc).size() == 0) return true;
    return false;
}

void Board::setAt(int x, int y, Piece _piece){
    int index = y*8 + x;
    board[index] = _piece;
}

void Board::promote(){
    for(int i = 0; i<8; i++){
        if(at(i, 0).name == PIECE_NAMES::PAWN){
            Piece tmp = at(i, 0);
            tmp.name = PIECE_NAMES::QUEEN;
            tmp.moves_done = -1;
            setAt(i, 0, tmp);
        }

        if(at(i, 7).name == PIECE_NAMES::PAWN){
            Piece tmp = at(i, 7);
            tmp.name = PIECE_NAMES::QUEEN;
            tmp.moves_done = -1;
            setAt(i, 7, tmp);
        }
    }
}