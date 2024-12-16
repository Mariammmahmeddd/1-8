#ifndef _ULTIMATE_TIC_TAC_TOE_H
#define _ULTIMATE_TIC_TAC_TOE_H

#include "boardgame_classes.h"
#include <iostream>

using namespace std;

class SmallTicTacToeBoard : public Board<char> {
public:
    SmallTicTacToeBoard(int r = 3, int c = 3);

    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

class UltimateTicTacToe : public Board<char> {
private:
    SmallTicTacToeBoard* small_boards[3][3];

public:
    UltimateTicTacToe();

    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool update_small_board(int bx, int by, int sx, int sy, char symbol);
    bool small_board_is_win(int bx, int by, char symbol);
    bool small_board_is_draw(int bx, int by);
};


SmallTicTacToeBoard::SmallTicTacToeBoard(int r, int c) {
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

class HumanPlayer : public Player<char> {
public:
    HumanPlayer(string n, char symbol) : Player(n, symbol) {}
    HumanPlayer(char symbol) : Player(symbol) {}

    void getmove(int& x, int& y) override {
        cout << "Enter your move (row and column): ";
        cin >> x >> y;
        x--;
        y--;
    }

    void get_small_move(int& bx, int& by, int& sx, int& sy) {
        cout << "Enter your board coordinates (row and column): ";
        cin >> bx >> by;
        bx--;
        by--;
        cout << "Enter your move coordinates (row and column): ";
        cin >> sx >> sy;
        sx--;
        sy--;
    }
};

class RandomAIPlayer : public RandomPlayer<char> {
public:
    RandomAIPlayer(char symbol) : RandomPlayer(symbol) {
        srand(time(0));
    }

    void getmove(int& x, int& y) override {
        x = rand() % 3;
        y = rand() % 3;
    }

    void get_small_move(int& bx, int& by, int& sx, int& sy) {
        bx = rand() % 3;
        by = rand() % 3;
        sx = rand() % 3;
        sy = rand() % 3;
    }
};

bool SmallTicTacToeBoard::update_board(int x, int y, char symbol) {
    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
        board[x][y] = symbol;
        ++n_moves;
        return true;
    }
    return false;
}

void SmallTicTacToeBoard::display_board() {
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

bool SmallTicTacToeBoard::is_win() {
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

bool SmallTicTacToeBoard::is_draw() {
    return n_moves == rows * columns && !is_win();
}

bool SmallTicTacToeBoard::game_is_over() {
    return is_win() || is_draw();
}
UltimateTicTacToe::UltimateTicTacToe() {
    rows = 3;
    columns = 3;
    board = new char* [rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new char[columns];
        for (int j = 0; j < columns; ++j) {
            board[i][j] = ' ';
            small_boards[i][j] = new SmallTicTacToeBoard(3, 3);
        }
    }
}

bool UltimateTicTacToe::update_board(int x, int y, char symbol) {
    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
        board[x][y] = symbol;
        ++n_moves;
        return true;
    }
    return false;
}

void UltimateTicTacToe::display_board() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] != ' ') {
                cout << board[i][j];
            }
            else {
                small_boards[i][j]->display_board();
            }
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

bool UltimateTicTacToe::is_win() {
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

bool UltimateTicTacToe::is_draw() {
    return n_moves == rows * columns && !is_win();
}

bool UltimateTicTacToe::game_is_over() {
    return is_win() || is_draw();
}

bool UltimateTicTacToe::update_small_board(int bx, int by, int sx, int sy, char symbol) {
    if (bx >= 0 && bx < 3 && by >= 0 && by < 3) {
        return small_boards[bx][by]->update_board(sx, sy, symbol);
    }
    return false;
}

bool UltimateTicTacToe::small_board_is_win(int bx, int by, char symbol) {
    if (bx >= 0 && bx < 3 && by >= 0 && by < 3) {
        return small_boards[bx][by]->is_win();
    }
    return false;
}

bool UltimateTicTacToe::small_board_is_draw(int bx, int by) {
    if (bx >= 0 && bx < 3 && by >= 0 && by < 3) {
        return small_boards[bx][by]->is_draw();
    }
    return false;
}

#endif