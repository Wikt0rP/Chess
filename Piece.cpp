#include "Piece.h"

bool King::isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) {
    return (abs(startX - endX) <= 1 && abs(startY - endY) <= 1);
}

bool Queen::isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) {
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    return (dx == dy || startX == endX || startY == endY);
}

bool Rook::isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) {
    return (startX == endX || startY == endY);
}

bool Bishop::isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) {
    return (abs(startX - endX) == abs(startY - endY));
}

bool Knight::isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) {
    int dx = abs(startX - endX);
    int dy = abs(startY - endY);
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        return board[endX][endY] == nullptr || board[endX][endY]->color != this->color;
    }
    return false;
}

bool Pawn::isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) {
    if (color == Color::WHITE) {
        if (startX == endX && startY == endY - 1 && board[endX][endY] == nullptr) return true;
        if (startX == endX && startY == 1 && endY == 3 && board[endX][2] == nullptr && board[endX][3] == nullptr) return true;
    } else {
        if (startX == endX && startY == endY + 1 && board[endX][endY] == nullptr) return true;
        if (startX == endX && startY == 6 && endY == 4 && board[endX][5] == nullptr && board[endX][4] == nullptr) return true;
    }
    return false;
}

bool Pawn::isValidCapture(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) {
    if (color == Color::WHITE) {
        if (abs(startX - endX) == 1 && startY == endY - 1 && board[endX][endY] != nullptr && board[endX][endY]->color == Color::BLACK) return true;
    } else {
        if (abs(startX - endX) == 1 && startY == endY + 1 && board[endX][endY] != nullptr && board[endX][endY]->color == Color::WHITE) return true;
    }
    return false;
}

bool Pawn::canEnPassant(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board, pair<int, int> enPassantTarget) {
    if (color == Color::WHITE) {
        if (startY == 4 && endY == 5 && abs(startX - endX) == 1 && endX == enPassantTarget.first && endY == enPassantTarget.second) {
            return true;
        }
    } else {
        if (startY == 3 && endY == 2 && abs(startX - endX) == 1 && endX == enPassantTarget.first && endY == enPassantTarget.second) {
            return true;
        }
    }
    return false;
}
