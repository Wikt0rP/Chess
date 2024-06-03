#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Piece.h"

class ChessGame {
private:
    vector<vector<Piece*>> board;
    Color currentPlayer;

public:
    ChessGame();
    ~ChessGame();
    void initializeBoard();
    bool movePiece(int startX, int startY, int endX, int endY);
    void printBoard();
};

#endif // CHESSGAME_H
