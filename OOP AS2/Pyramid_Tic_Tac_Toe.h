#ifndef Pyramic_Tic_Tac_Toe_H
#define Pyramic_Tic_Tac_Toe_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
//-----------------------------
// Function to delete an item from the vector
vector<string> vec = { "02","11","12","13","20","21","22","23","24" };
void del_vec(int x, int y, vector<string>& vec) {
    string cell = to_string(x) + to_string(y);
    auto it = find(vec.begin(), vec.end(), cell);
    if (it != vec.end()) {
        vec.erase(it);  // Remove the selected cell from the vector
    }
}
//-------------------------
template <typename T>
class PyramidBoard : public Board<T> {
public:
    PyramidBoard(int levels); 
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void del_vec(int x, int y, vector<string>& vec);
private:
    vector<pair<int, int>> row_ranges; // Stores start and end column indices for each row
};
//--------------------------------------------------
//Pyramid_Player
template <typename T>
class Pyramid_Player : public Player<T> {
public:
    Pyramid_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << " (" << this->getsymbol() << ") - Enter row and column: ";
        cin >> x >> y;
        del_vec(x, y, vec);
    }
};
//---------------------------------------------------
//Pyramid_Random_Player
template <typename T>
class Pyramid_Random_Player : public RandomPlayer<T> {
public:
    Pyramid_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
        srand(time(0)); // Seed for randomness
    }

    void getmove(int& x, int& y) override {
        if (!vec.empty()) {
            // Select the vector element from the vector
            int index = rand() % vec.size();
            string cell = vec[index];

            x = cell[0] - '0';
            y = cell[1] - '0';

            vec.erase(vec.begin() + index);

            cout << "Computer chooses: (" << x << ", " << y << ")\n";
        }
        else {
            cout << "No more moves available in vector.\n";
        }
    }
};


// Constructor for PyramidBoard
template <typename T>
PyramidBoard<T>::PyramidBoard(int levels) {
    this->rows = levels;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        int start_col = this->rows - i - 1;
        int end_col = this->rows + i - 1;
        row_ranges.push_back({ start_col, end_col });

        int row_size = end_col - start_col + 1;
        this->board[i] = new char[row_size];
        for (int j = 0; j < row_size; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool PyramidBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows) return false;
    int start_col = row_ranges[x].first;
    int end_col = row_ranges[x].second;

    if (y < start_col || y > end_col || this->board[x][y - start_col] != 0) {
        return false;
    }

    this->board[x][y - start_col] = toupper(symbol);
    this->n_moves++;
    return true;
}

template <typename T>
void PyramidBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        // Print leading spaces for alignment
        cout << string(this->rows - i - 1, ' '); 

        int start_col = row_ranges[i].first;
        int end_col = row_ranges[i].second;

        for (int j = start_col; j <= end_col; j++) {
            cout << "(" << i << "," << j << ")";
            char cell = this->board[i][j - start_col];
            cout << (cell ? cell : '.');
            if (j != end_col) {
                cout << "|";
            }
        }
        cout << endl; 
    }
}


template <typename T>
bool PyramidBoard<T>::is_win() {
    // Check the rows (horizontal direction)
    for (int i = 0; i < this->rows; i++) {
        int start_col = row_ranges[i].first;
        int end_col = row_ranges[i].second;
        for (int j = start_col; j < end_col - 1; j++) { // Adjusted range
            if (this->board[i][j - start_col] != 0 &&
                this->board[i][j - start_col] == this->board[i][j - start_col + 1] &&
                this->board[i][j - start_col] == this->board[i][j - start_col + 2]) {
                return true;
            }
        }
    }


    // Check the columns (vertical direction)
    for (int i = 0; i < this->rows - 2; i++) {
        int start_col = row_ranges[i].first;
        int end_col = row_ranges[i].second;
        for (int j = start_col; j <= end_col; j++) {
            if (this->board[i][j - start_col] != 0 &&
                this->board[i][j - start_col] == this->board[i + 1][j - start_col] &&
                this->board[i][j - start_col] == this->board[i + 2][j - start_col]) {
                return true;
            }
        }
    }


    // Check both diagonals
    // Check bottom-left to top-right diagonals
    for (int i = 0; i < this->rows - 2; i++) {
        for (int j = row_ranges[i].first; j <= row_ranges[i].second; j++) {
            if (this->board[i][j - row_ranges[i].first] != 0 &&
                this->board[i][j - row_ranges[i].first] == this->board[i + 1][j - row_ranges[i + 1].first] &&
                this->board[i][j - row_ranges[i].first] == this->board[i + 2][j - row_ranges[i + 2].first]) {
                return true;
            }
        }
    }
    // Check diagonal from top-left to bottom-right
    for (int i = 0; i < this->rows - 2; i++) {
        for (int j = row_ranges[i].first; j <= row_ranges[i].second; j++) {
            if (this->board[i][j - row_ranges[i].first] != 0 &&
                this->board[i][j - row_ranges[i].first] == this->board[i + 1][j - row_ranges[i + 1].first + 1] &&
                this->board[i][j - row_ranges[i].first] == this->board[i + 2][j - row_ranges[i + 2].first + 2]) {
                return true;
            }
        }
    }
    return false; // No winner found
}

template <typename T>
bool PyramidBoard<T>::is_draw() {
    // Check if all cells are filled
    int total_cells = 0;
    for (int i = 0; i < this->rows; i++) {
        total_cells += row_ranges[i].second - row_ranges[i].first + 1;
    }

    // If all cells are filled and there is no winner, it's a draw
    return (this->n_moves == total_cells) && !is_win();
}

template <typename T>
bool PyramidBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//---------------------------------------

#endif
