#ifndef _TICTACTOE_5X5_H
#define _TICTACTOE_5X5_H

#include "boardgame_classes.h"
#include <iostream>

using namespace std;

class TicTacToe5x5 : public Board<char> {
public:
    TicTacToe5x5(int r = 5, int c = 5);

    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    int count_three_in_a_row(char symbol);
};

TicTacToe5x5::TicTacToe5x5(int r, int c) {
    rows = r;
    columns = c;
    board = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new char[columns];
        for (int j = 0; j < columns; ++j) {
            board[i][j] = ' ';
        }
    }
}

bool TicTacToe5x5::update_board(int x, int y, char symbol) {
    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
        board[x][y] = symbol;
        ++n_moves;
        return true;
    }
    return false;
}

void TicTacToe5x5::display_board() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << board[i][j];
            if (j < columns - 1) cout << "|";
        }
        cout << endl;
        if (i < rows - 1) {
            for (int k = 0; k < columns; ++k) {
                cout << "-";
                if (k < columns - 1) cout << "+";
            }
            cout << endl;
        }
    }
}

bool TicTacToe5x5::is_win() {
    return count_three_in_a_row('X') > count_three_in_a_row('O');
}

bool TicTacToe5x5::is_draw() {
    return n_moves == rows * columns;
}

bool TicTacToe5x5::game_is_over() {
    return is_draw();
}

int TicTacToe5x5::count_three_in_a_row(char symbol) {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns - 2; ++j) {
            if (board[i][j] == symbol && board[i][j+1] == symbol && board[i][j+2] == symbol) {
                count++;
            }
        }
    }
    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == symbol && board[i+1][j] == symbol && board[i+2][j] == symbol) {
                count++;
            }
        }
    }
    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 0; j < columns - 2; ++j) {
            if (board[i][j] == symbol && board[i+1][j+1] == symbol && board[i+2][j+2] == symbol) {
                count++;
            }
        }
    }
    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 2; j < columns; ++j) {
            if (board[i][j] == symbol && board[i+1][j-1] == symbol && board[i+2][j-2] == symbol) {
                count++;
            }
        }
    }
    return count;
}

#endif