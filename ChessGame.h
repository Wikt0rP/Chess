#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Piece.h"
#include <vector>
#include <utility>
#include <string>

class ChessGame {
private:
    std::vector<std::vector<Piece*>> board;
    Color currentPlayer;
    std::pair<int, int> enPassantTarget;

public:
    ChessGame();
    ~ChessGame();
    void initializeBoard();
    bool movePiece(int startX, int startY, int endX, int endY);
    void printBoard();
    void saveGame(const std::string& filename);
    void loadGame(const std::string& filename);
};

#endif // CHESSGAME_H
