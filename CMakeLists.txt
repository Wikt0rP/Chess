cmake_minimum_required(VERSION 3.28)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chess main.cpp
        Piece.h
        Piece.cpp
        ChessGame.cpp
        ChessGame.h
)
