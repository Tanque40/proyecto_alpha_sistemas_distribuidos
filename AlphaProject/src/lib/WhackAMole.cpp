#include "WhackAMole.h"

#include <stdlib.h>
#include <time.h>

WhackAMole::WhackAMole(int boardSize) : boardSize(boardSize) {
    std::vector<int> row;

    for (size_t i = 0; i < this->boardSize; i++) {
        row = std::vector<int>(this->boardSize);
        for (size_t j = 0; j < this->boardSize; j++) {
            row[j] = 0;
        }
        board.push_back(row);
    }
}

void WhackAMole::setBoardSize(int boardSize) {
    this->boardSize = boardSize;
}

int WhackAMole::getBoardSideSize() {
    return this->boardSize;
}

std::string WhackAMole::getBoard() {
    std::string boardString = "{ \n";

    for (std::vector row : board) {
        boardString += "{ ";
        for (int element : row) {
            boardString += std::to_string(element) + ", ";
        }
        boardString += "}\n";
    }
    boardString += "}\n";

    return boardString;
}

bool WhackAMole::setNewUserPuntuation(int userId) {
    if (!userPuntuation.contains(userId)) {
        userPuntuation[userId] = 0;
        return true;
    }
    return false;
}

int WhackAMole::getNewMolePosition() {
    srand(time(NULL));
    return rand() % 99;
}

bool WhackAMole::setUserPuntuation(int userId) {
    if (userPuntuation.contains(userId)) {
        userPuntuation[userId] += 1;
        return true;
    }
    return false;
}
