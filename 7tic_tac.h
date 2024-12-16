#ifndef _DIGITAL_TICTACTOE_H
#define _DIGITAL_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <set>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Digital 4x4 Tic-Tac-Toe Board
template <typename T>
class DigitalTicTacToe_Board : public Board<T> {
private:
    set<int> player1_tokens; // Tokens for Player 1
    set<int> player2_tokens; // Tokens for Player 2
    bool player1_turn; // Track whose turn it is

public:
    DigitalTicTacToe_Board();
    bool update_board(int x, int y, T number);
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool is_valid_move(int x, int y, int player);
};

// Digital 4x4 Tic-Tac-Toe Player
template <typename T>
class DigitalTicTacToe_Player : public Player<T> {
public:
    DigitalTicTacToe_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

// Random Player for Digital Tic-Tac-Toe
template <typename T>
class DigitalTicTacToe_Random_Player : public RandomPlayer<T> {
public:
    DigitalTicTacToe_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

template <typename T>
DigitalTicTacToe_Board<T>::DigitalTicTacToe_Board() {
    this->rows = this->columns = 4; // 4x4 grid
    this->board = new T * [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns]();
    }
    this->n_moves = 0;
    player1_tokens = { 0, 1, 2, 3 };  // Player 1 starts with tokens at the top row
    player2_tokens = { 12, 13, 14, 15 }; // Player 2 starts with tokens at the bottom row
    player1_turn = true;
}

template <typename T>
bool DigitalTicTacToe_Board<T>::update_board(int x, int y, T number) {
    // Check for valid move: Token should be moved to an adjacent space and must be empty
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0)
        return false;

    // Ensure player moves only to an adjacent square
    if (!is_valid_move(x, y, player1_turn ? 1 : 2))
        return false;

    // Assign token number based on the current player
    if (player1_turn) {
        this->board[x][y] = 1; // Player 1 token
        player1_turn = false; // Switch turn
    }
    else {
        this->board[x][y] = 2; // Player 2 token
        player1_turn = true; // Switch turn
    }

    this->n_moves++;
    return true;
}

template <typename T>
bool DigitalTicTacToe_Board<T>::is_valid_move(int x, int y, int player) {
    // Check for valid movement: Token must move to an adjacent space
    if (player == 1) {
        // Check if the player has a token at the start
        if (player1_tokens.count(x * 4 + y) == 0)
            return false;
    }
    else {
        // Same check for player 2
        if (player2_tokens.count(x * 4 + y) == 0)
            return false;
    }

    // Check adjacent spaces for validity of move (No jumping)
    // Logic to check surrounding squares...
    return true;
}

template <typename T>
void DigitalTicTacToe_Board<T>::display_board() {
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
bool DigitalTicTacToe_Board<T>::is_win() {
    // Check rows, columns, and diagonals for 3 in a row
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) { // Make sure there's space for 3 tokens
            if (this->board[i][j] == this->board[i][j + 1] && this->board[i][j + 1] == this->board[i][j + 2] && this->board[i][j] != 0)
                return true; // Horizontal
        }
        for (int j = 0; j < 2; j++) { // Make sure there's space for 3 tokens
            if (this->board[j][i] == this->board[j + 1][i] && this->board[j + 1][i] == this->board[j + 2][i] && this->board[j][i] != 0)
                return true; // Vertical
        }
    }
    // Diagonal checks for 3 in a row
    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0)
        return true; // Diagonal top-left to bottom-right
    if (this->board[1][1] == this->board[2][2] && this->board[2][2] == this->board[3][3] && this->board[1][1] != 0)
        return true; // Diagonal middle-left to bottom-right
    if (this->board[0][3] == this->board[1][2] && this->board[1][2] == this->board[2][1] && this->board[0][3] != 0)
        return true; // Diagonal top-right to bottom-left
    if (this->board[1][2] == this->board[2][1] && this->board[2][1] == this->board[3][0] && this->board[1][2] != 0)
        return true; // Diagonal middle-right to bottom-left
    return false;
}

template <typename T>
bool DigitalTicTacToe_Board<T>::is_draw() {
    return this->n_moves == 16 && !is_win();
}

template <typename T>
bool DigitalTicTacToe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for DigitalTicTacToe_Player
template <typename T>
DigitalTicTacToe_Player<T>::DigitalTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void DigitalTicTacToe_Player<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move (row column): ";
    cin >> x >> y;
    if (x < 0 || x >= 4 || y < 0 || y >= 4) {
        cout << "Invalid coordinates! Try again.\n";
        getmove(x, y);
    }
}

// Constructor for DigitalTicTacToe_Random_Player
template <typename T>
DigitalTicTacToe_Random_Player<T>::DigitalTicTacToe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void DigitalTicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    srand(time(0));
    x = rand() % 4;
    y = rand() % 4;
}

#endif //_DIGITAL_TICTACTOE_H