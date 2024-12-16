#ifndef _NUMERICAL_TICTACTOE_H
#define _NUMERICAL_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <set>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Numerical Tic-Tac-Toe Board
template <typename T>
class NumericalTicTacToe_Board : public Board<T> {
private:
    set<int> player1_numbers; // Odd numbers for Player 1
    set<int> player2_numbers; // Even numbers for Player 2

public:
    NumericalTicTacToe_Board();
    bool update_board(int x, int y, T number);
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

// Numerical Tic-Tac-Toe Player
template <typename T>
class NumericalTicTacToe_Player : public Player<T> {
public:
    NumericalTicTacToe_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

// Random Player for Numerical Tic-Tac-Toe
template <typename T>
class NumericalTicTacToe_Random_Player : public RandomPlayer<T> {
public:
    NumericalTicTacToe_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

template <typename T>
NumericalTicTacToe_Board<T>::NumericalTicTacToe_Board() {
    this->rows = this->columns = 3;
    this->board = new T * [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns]();
    }
    this->n_moves = 0;
    player1_numbers = { 1, 3, 5, 7, 9 }; // Odd numbers for Player 1
    player2_numbers = { 2, 4, 6, 8 };    // Even numbers for Player 2
}

template <typename T>
bool NumericalTicTacToe_Board<T>::update_board(int x, int y, T number) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0)
        return false;

    // Check if the number is between 1 and 9
    if (number < 1 || number > 9) {
        cout << "make sure that your input is betwen 1,9" << endl;
        return false;
    }

    // Ensure player 1 only uses odd numbers, player 2 only uses even numbers
    if (player1_numbers.count(number) && number % 2 != 1) {
        cout << "only odd inputs for firt player!" << endl;
        return false;
    }
    if (player2_numbers.count(number) && number % 2 != 0) {
        cout << "only even inputs for second player!" << endl;
        return false;
    }

    // Update the board
    this->board[x][y] = number;
    if (player1_numbers.count(number)) player1_numbers.erase(number);
    if (player2_numbers.count(number)) player2_numbers.erase(number);
    this->n_moves++;
    return true;
}

template <typename T>
void NumericalTicTacToe_Board<T>::display_board() {
    cout << "\nCurrent Board:\n";
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0)
                cout << "   .";
            else
                cout << setw(4) << this->board[i][j];
        }
        cout << "\n";
    }
}

template <typename T>
bool NumericalTicTacToe_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) &&
            this->board[i][0] && this->board[i][1] && this->board[i][2])
            return true;

        if ((this->board[0][i] + this->board[1][i] + this->board[2][i] == 15) &&
            this->board[0][i] && this->board[1][i] && this->board[2][i])
            return true;
    }

    // Check diagonals
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) &&
        this->board[0][0] && this->board[1][1] && this->board[2][2])
        return true;

    if ((this->board[0][2] + this->board[1][1] + this->board[2][0] == 15) &&
        this->board[0][2] && this->board[1][1] && this->board[2][0])
        return true;

    return false;
}

template <typename T>
bool NumericalTicTacToe_Board<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

template <typename T>
bool NumericalTicTacToe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for NumericalTicTacToe_Player
template <typename T>
NumericalTicTacToe_Player<T>::NumericalTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void NumericalTicTacToe_Player<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move (row column number): ";
    int number;
    cin >> x >> y >> number;

    // Ensure the number is between 1 and 9
    if (number < 1 || number > 9) {
        cout << "make sure that your input is betwen 1,9." << endl;
        getmove(x, y); // Request input again if invalid
        return;
    }

    // Ensure player 1 only enters odd numbers
    if (this->symbol == 1 && number % 2 == 0) {
        cout << "only odd inputs for firt player!!" << endl;
        getmove(x, y); // Request input again if invalid
        return;
    }

    // Ensure player 2 only enters even numbers
    if (this->symbol == 2 && number % 2 != 0) {
        cout << "only even inputs for second player!!" << endl;
        getmove(x, y); // Request input again if invalid
        return;
    }

    this->symbol = number;  // Assign the entered number as the player's symbol
}

// Constructor for NumericalTicTacToe_Random_Player
template <typename T>
NumericalTicTacToe_Random_Player<T>::NumericalTicTacToe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void NumericalTicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    srand(time(0));
    x = rand() % 3;
    y = rand() % 3;

    // Randomly choose a number between 1 and 9
    int number = (rand() % 9) + 1;

    // Ensure player 1 picks odd numbers only, player 2 picks even numbers only
    if (this->symbol == 1 && number % 2 == 0) {
        number = (rand() % 5) * 2 + 1;  // Choose an odd number
    }
    else if (this->symbol == 2 && number % 2 != 0) {
        number = (rand() % 4) * 2 + 2;  // Choose an even number
    }

    // Here we only need to return the number chosen, as it will be used in the operation
}
#endif //_NUMERICAL_TICTACTOE_H
