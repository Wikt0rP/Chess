#include "ChessGame.h"

ChessGame::ChessGame() : board(8, vector<Piece*>(8, nullptr)), currentPlayer(Color::WHITE) {
    initializeBoard();
}

ChessGame::~ChessGame() {
    for (auto& row : board) {
        for (auto& piece : row) {
            delete piece;
        }
    }
}

void ChessGame::initializeBoard() {
    for (int i = 0; i < 8; ++i) {
        board[i][1] = new Pawn(Color::WHITE);
        board[i][6] = new Pawn(Color::BLACK);
    }

    board[0][0] = board[7][0] = new Rook(Color::WHITE);
    board[1][0] = board[6][0] = new Knight(Color::WHITE);
    board[2][0] = board[5][0] = new Bishop(Color::WHITE);
    board[3][0] = new Queen(Color::WHITE);
    board[4][0] = new King(Color::WHITE);

    board[0][7] = board[7][7] = new Rook(Color::BLACK);
    board[1][7] = board[6][7] = new Knight(Color::BLACK);
    board[2][7] = board[5][7] = new Bishop(Color::BLACK);
    board[3][7] = new Queen(Color::BLACK);
    board[4][7] = new King(Color::BLACK);
}

bool ChessGame::movePiece(int startX, int startY, int endX, int endY) {
    if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 || endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        return false;
    }

    Piece* piece = board[startX][startY];
    if (piece == nullptr || piece->color != currentPlayer || !piece->isValidMove(startX, startY, endX, endY, board)) {
        return false;
    }

    delete board[endX][endY];
    board[endX][endY] = piece;
    board[startX][startY] = nullptr;
    currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
    return true;
}

void ChessGame::printBoard() {
    cout << "  0 1 2 3 4 5 6 7" << endl;
    for (int y = 7; y >= 0; --y) {
        cout << y << " ";
        for (int x = 0; x < 8; ++x) {
            if (board[x][y] == nullptr) {
                cout << ".";
            } else {
                char symbol = '?';
                switch (board[x][y]->type) {
                    case PieceType::KING:   symbol = 'K'; break;
                    case PieceType::QUEEN:  symbol = 'Q'; break;
                    case PieceType::ROOK:   symbol = 'R'; break;
                    case PieceType::BISHOP: symbol = 'B'; break;
                    case PieceType::KNIGHT: symbol = 'N'; break;
                    case PieceType::PAWN:   symbol = 'P'; break;
                    default:                symbol = '?'; break;
                }
                if (board[x][y]->color == Color::BLACK) {
                    symbol = tolower(symbol);
                }
                cout << symbol;
            }
            cout << " ";
        }
        cout << y << endl;
    }
    cout << "  0 1 2 3 4 5 6 7" << endl << endl;
}
