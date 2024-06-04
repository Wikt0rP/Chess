#include "ChessGame.h"
#include <fstream>

ChessGame::ChessGame() : board(8, std::vector<Piece*>(8, nullptr)), currentPlayer(Color::WHITE), enPassantTarget({-1, -1}) {
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
    if (piece == nullptr || piece->color != currentPlayer) {
        return false;
    }

    // Obsługa bicia w przelocie
    if (piece->type == PieceType::PAWN) {
        Pawn* pawn = static_cast<Pawn*>(piece);
        if (pawn->canEnPassant(startX, startY, endX, endY, board, enPassantTarget)) {
            delete board[endX][endY];
            board[endX][endY] = piece;
            board[startX][startY] = nullptr;
            delete board[enPassantTarget.first][enPassantTarget.second];
            board[enPassantTarget.first][enPassantTarget.second] = nullptr;
            currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
            enPassantTarget = {-1, -1}; // Resetowanie celu bicia w przelocie
            return true;
        }
    }

    if (!piece->isValidMove(startX, startY, endX, endY, board) &&
        !(piece->type == PieceType::PAWN && static_cast<Pawn*>(piece)->isValidCapture(startX, startY, endX, endY, board))) {
        return false;
    }

    delete board[endX][endY];
    board[endX][endY] = piece;
    board[startX][startY] = nullptr;
    piece->hasMoved = true;
    currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;

    if (piece->type == PieceType::PAWN && abs(startY - endY) == 2) {
        enPassantTarget = {endX, (startY + endY) / 2};
    } else {
        enPassantTarget = {-1, -1};
    }

    return true;
}

void ChessGame::printBoard() {
    std::cout << "  0 1 2 3 4 5 6 7" << std::endl;
    for (int y = 7; y >= 0; --y) {
        std::cout << y << " ";
        for (int x = 0; x < 8; ++x) {
            if (board[x][y] == nullptr) {
                std::cout << ".";
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
                std::cout << symbol;
            }
            std::cout << " ";
        }
        std::cout << y << std::endl;
    }
    std::cout << "  0 1 2 3 4 5 6 7" << std::endl << std::endl;
    std::cout << "Tura gracza: " << (currentPlayer == Color::WHITE ? "Białe" : "Czarne") << std::endl << std::endl;

}

void ChessGame::saveGame(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Nie można otworzyć pliku do zapisu!" << std::endl;
        return;
    }

    outFile << (currentPlayer == Color::WHITE ? "WHITE" : "BLACK") << std::endl;
    outFile << enPassantTarget.first << " " << enPassantTarget.second << std::endl;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (board[x][y] == nullptr) {
                outFile << ".";
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
                outFile << symbol;
            }
        }
        outFile << std::endl;
    }

    outFile.close();
}

void ChessGame::loadGame(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Nie można otworzyć pliku do odczytu!" << std::endl;
        return;
    }

    std::string currentPlayerStr;
    inFile >> currentPlayerStr;
    currentPlayer = (currentPlayerStr == "WHITE") ? Color::WHITE : Color::BLACK;

    inFile >> enPassantTarget.first >> enPassantTarget.second;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            char symbol;
            inFile >> symbol;
            if (symbol == '.') {
                delete board[x][y];
                board[x][y] = nullptr;
            } else {
                Color color = isupper(symbol) ? Color::WHITE : Color::BLACK;
                switch (tolower(symbol)) {
                    case 'k': board[x][y] = new King(color); break;
                    case 'q': board[x][y] = new Queen(color); break;
                    case 'r': board[x][y] = new Rook(color); break;
                    case 'b': board[x][y] = new Bishop(color); break;
                    case 'n': board[x][y] = new Knight(color); break;
                    case 'p': board[x][y] = new Pawn(color); break;
                    default: board[x][y] = nullptr; break;
                }
            }
        }
    }

    inFile.close();
}
