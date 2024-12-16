#ifndef _FOUR_IN_A_RO_H
#define _FOUR_IN_A_RO_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class ConnectFour_Board : public Board<T> {
public:
    ConnectFour_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

template <typename T>
class ConnectFour_Player : public Player<T> {
public:
    ConnectFour_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class ConnectFour_Random_Player : public RandomPlayer<T> {
public:
    ConnectFour_Random_Player(T symbol);
    void getmove(int& x, int& y) override;
};

// Implementations

template <typename T>
ConnectFour_Board<T>::ConnectFour_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new T * [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns]();
    }
    this->n_moves = 0;
}

template <typename T>
bool ConnectFour_Board<T>::update_board(int x, int y, T symbol) {
    if (y >= 0 && y < this->columns) {
        for (int i = this->rows - 1; i >= 0; i--) {
            if (this->board[i][y] == 0) {
                this->board[i][y] = toupper(symbol);
                this->n_moves++;
                return true;
            }
        }
    }
    return false;
}

template <typename T>
void ConnectFour_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(2) << (this->board[i][j] ? this->board[i][j] : '.') << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool ConnectFour_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0) continue;

            if (j + 3 < this->columns &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2] &&
                this->board[i][j] == this->board[i][j + 3]) {
                return true;
            }

            if (i + 3 < this->rows &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j] &&
                this->board[i][j] == this->board[i + 3][j]) {
                return true;
            }

            if (i + 3 < this->rows && j + 3 < this->columns &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2] &&
                this->board[i][j] == this->board[i + 3][j + 3]) {
                return true;
            }

            if (i + 3 < this->rows && j - 3 >= 0 &&
                this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i][j] == this->board[i + 2][j - 2] &&
                this->board[i][j] == this->board[i + 3][j - 3]) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool ConnectFour_Board<T>::is_draw() {
    return (this->n_moves == this->rows * this->columns && !is_win());
}

template <typename T>
bool ConnectFour_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
ConnectFour_Player<T>::ConnectFour_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void ConnectFour_Player<T>::getmove(int& x, int& y) {
    cout << "Enter column (0 to 6): ";
    cin >> y;
    x = 0;
}

template <typename T>
ConnectFour_Random_Player<T>::ConnectFour_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void ConnectFour_Random_Player<T>::getmove(int& x, int& y) {
    y = rand() % 7;
    x = 0;
}

#endif
