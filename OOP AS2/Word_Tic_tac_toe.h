#ifndef Word_Tic_Tac_Toe_H
#define Word_Tic_Tac_Toe_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <cctype>  // for toupper()
#include <fstream>
#include <iomanip>
#include <map>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <set> 
#include <unordered_set>
using namespace std;

template <typename T>
class Word_Board :public Board<T> {
public:
    Word_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Word_Player : public Player<T> {
public:
    Word_Player(string name, T symbol);
    void getmove(int& x, int& y);  
};

template <typename T>
class Word_Random_Player : public RandomPlayer<T> {
public:
    Word_Random_Player(T symbol);
    void getmove(int& x, int& y);
    vector<char>letters;
    //char get_symbol() { return this->symbol };
};

// Constructor for Word_Board
template <typename T>
Word_Board<T>::Word_Board() {
    this->rows = this->columns = 3;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Word_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Word_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool Word_Board<T>::is_win() {
    // Load the dictionary into a static set (loaded only once)
    static set<string> dictionary;

    if (dictionary.empty()) {
        // Load dictionary from file if not already loaded
        ifstream inputFile("Dec.txt");  // Replace "Dec.txt" with your dictionary file name
        if (!inputFile) {
            throw runtime_error("Error opening dictionary file");
        }

        string word;
        while (inputFile >> word) {
            dictionary.insert(word);  // Insert words into the set
        }
    }

    // Check rows for valid words
    for (int i = 0; i < this->rows; i++) {
        string rowWord;
        for (int j = 0; j < this->columns; j++) {
            rowWord += this->board[i][j];
        }
        if (dictionary.count(rowWord)) {  // Check if rowWord is in the dictionary
            return true;
        }
    }

    // Check columns for valid words
    for (int j = 0; j < this->columns; j++) {
        string colWord;
        for (int i = 0; i < this->rows; i++) {
            colWord += this->board[i][j];
        }
        if (dictionary.count(colWord)) {  // Check if colWord is in the dictionary
            return true;
        }
    }

    // Check primary diagonal (top-left to bottom-right) for valid words
    string diagWord1;
    for (int i = 0; i < this->rows; i++) {
        diagWord1 += this->board[i][i];
    }
    if (dictionary.count(diagWord1)) {
        return true;
    }

    // Check secondary diagonal (top-right to bottom-left) for valid words
    string diagWord2;
    for (int i = 0; i < this->rows; i++) {
        diagWord2 += this->board[i][this->columns - i - 1];
    }
    if (dictionary.count(diagWord2)) {
        return true;
    }

    // No winning word found
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Word_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Word_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for Word_Random_Player
template <typename T>
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    this->letters = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M','N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
}

template <typename T>

void Word_Random_Player<T>::getmove(int& x, int& y) {
    int z;
    x = rand() % 3;
    y = rand() % 3;
    z = rand() % this->letters.size();
    this->symbol = this->letters[z];
}

// Constructor for Word_Player
template <typename T>
Word_Player<T>::Word_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Modified getmove to request a symbol along with the coordinates
template <typename T>
void Word_Player<T>::getmove(int& x, int& y) {
    cout << "\n" << this->name << ", enter the coordinates (x and y) separated by a space (0 to 2): ";
    cin >> x >> y;

    cout << "Choose the symbol you want to use for this move: ";
    cin >> this->symbol;  // Update the player's symbol for this move only
}
#endif
