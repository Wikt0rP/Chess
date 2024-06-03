#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

enum class PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN, NONE };
enum class Color { WHITE, BLACK, NONE };

class Piece {
public:
    PieceType type;
    Color color;
    bool hasMoved;
    Piece(PieceType t = PieceType::NONE, Color c = Color::NONE) : type(t), color(c), hasMoved(false) {}
    virtual bool isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) = 0;
};

class King : public Piece {
public:
    King(Color c) : Piece(PieceType::KING, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) override;
};

class Queen : public Piece {
public:
    Queen(Color c) : Piece(PieceType::QUEEN, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) override;
};

class Rook : public Piece {
public:
    Rook(Color c) : Piece(PieceType::ROOK, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) override;
};

class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(PieceType::BISHOP, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) override;
};

class Knight : public Piece {
public:
    Knight(Color c) : Piece(PieceType::KNIGHT, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) override;
};

class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(PieceType::PAWN, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) override;
    bool isValidCapture(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board);
    bool canEnPassant(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board, pair<int, int> enPassantTarget);
};

#endif // PIECE_H
