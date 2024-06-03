#include "ChessGame.h"

int main() {
    ChessGame gra;
    gra.printBoard();

    int startX, startY, endX, endY;
    while (true) {
        cout << "Wprowadź współrzędną początkową X (0-7): ";
        cin >> startX;
        cout << "Wprowadź współrzędną początkową Y (0-7): ";
        cin >> startY;
        cout << "Wprowadź współrzędną końcową X (0-7): ";
        cin >> endX;
        cout << "Wprowadź współrzędną końcową Y (0-7): ";
        cin >> endY;

        if (!gra.movePiece(startX, startY, endX, endY)) {
            cout << "Nieprawidłowy ruch. Spróbuj ponownie." << endl;
        }

        gra.printBoard();
    }

    return 0;
}
