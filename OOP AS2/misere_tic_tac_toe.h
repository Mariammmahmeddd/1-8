#ifndef _MISERE_TIC_TAC_TOE_H
#define _MISERE_TIC_TAC_TOE_H

#include "boardgame_classes.h"
#include <iostream>

using namespace std;

class MisereTicTacToe : public Board<char> {
public:
    MisereTicTacToe(int r = 3, int c = 3);

    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

MisereTicTacToe::MisereTicTacToe(int r, int c) {
    rows = r;
    columns = c;
    board = new char* [rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new char[columns];
        for (int j = 0; j < columns; ++j) {
            board[i][j] = ' ';
        }
    }
}

bool MisereTicTacToe::update_board(int x, int y, char symbol) {
    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
        board[x][y] = symbol;
        ++n_moves;
        return true;
    }
    return false;
}

void MisereTicTacToe::display_board() {
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

bool MisereTicTacToe::is_win() {
    for (int i = 0; i < rows; ++i) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return true;
        }
    }
    for (int j = 0; j < columns; ++j) {
        if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            return true;
        }
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return true;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return true;
    }
    return false;
}

bool MisereTicTacToe::is_draw() {
    return n_moves == rows * columns && !is_win();
}

bool MisereTicTacToe::game_is_over() {
    return is_win() || is_draw();
}

#endif