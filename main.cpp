#include "ChessGame.h"
#include <iostream>

void printMenu() {
    std::cout << "1. Wykonaj ruch" << std::endl;
    std::cout << "2. Zapisz grę" << std::endl;
    std::cout << "3. Wczytaj grę" << std::endl;
    std::cout << "4. Wyjdź" << std::endl;
}

int main() {
    ChessGame gra;
    gra.printBoard();

    int option;
    while (true) {
        printMenu();
        std::cin >> option;

        if (option == 1) {
            int startX, startY, endX, endY;
            std::cout << "Wprowadź współrzędną początkową X (0-7): ";
            std::cin >> startX;
            std::cout << "Wprowadź współrzędną początkową Y (0-7): ";
            std::cin >> startY;
            std::cout << "Wprowadź współrzędną końcową X (0-7): ";
            std::cin >> endX;
            std::cout << "Wprowadź współrzędną końcową Y (0-7): ";
            std::cin >> endY;

            if (!gra.movePiece(startX, startY, endX, endY)) {
                std::cout << "Nieprawidłowy ruch. Spróbuj ponownie." << std::endl;
            }

            gra.printBoard();
        } else if (option == 2) {
            std::string filename;
            std::cout << "Podaj nazwę pliku do zapisu: ";
            std::cin >> filename;
            gra.saveGame(filename);
        } else if (option == 3) {
            std::string filename;
            std::cout << "Podaj nazwę pliku do odczytu: ";
            std::cin >> filename;
            gra.loadGame(filename);
            gra.printBoard();
        } else if (option == 4) {
            break;
        } else {
            std::cout << "Nieprawidłowa opcja. Spróbuj ponownie." << std::endl;
        }
    }

    return 0;
}

/*Bicie w przelocie

Ruch piona białego o dwa pola do przodu:
Wprowadź: startX: 4, startY: 1, endX: 4, endY: 3
Ruch piona czarnego o dwa pola do przodu obok białego piona:
Wprowadź: startX: 5, startY: 6, endX: 5, endY: 4
Bicie w przelocie przez białego piona:
Wprowadź: startX: 4, startY: 3, endX: 5, endY: 4
Normalne bicie

Ruch piona białego do przodu:
Wprowadź: startX: 4, startY: 1, endX: 4, endY: 3
Ruch piona czarnego do przodu:
Wprowadź: startX: 3, startY: 6, endX: 3, endY: 4
Normalne bicie przez białego piona:
Wprowadź: startX: 4, startY: 3, endX: 3, endY: 4*/