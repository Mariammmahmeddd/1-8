#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
#include "Pyramid_Tic_Tac_Toe.h"
#include "Word_Tic_tac_toe.h"
#include "ultimate_tic_tac_toe.h"
#include "tictactoe_5x5.h"
#include "misere_tic_tac_toe.h"
#include "Four_in_a_row.h"
#include "Numerical_Tic_Tac_Toe.h"
#include "7tic_tac.h"
using namespace std;

//-------------------------------------
//Game 3
class HumanPlayer1 : public Player<char> {
public:
    HumanPlayer1(string n, char symbol) : Player(n, symbol) {}
    HumanPlayer1(char symbol) : Player(symbol) {}

    void getmove(int& x, int& y) override {
        cout << "Enter your move (row and column): ";
        cin >> x >> y;
        x--;
        y--;
    }
};

class RandomAIPlayer1 : public RandomPlayer<char> {
public:
    RandomAIPlayer1(char symbol) : RandomPlayer(symbol) {
        srand(time(0));
    }

    void getmove(int& x, int& y) override {
        x = rand() % 5;
        y = rand() % 5;
    }
};
//-------------------------------------
//Game 6
class HumanPlayer2 : public Player<char> {
public:
    HumanPlayer2(string n, char symbol) : Player(n, symbol) {}
    HumanPlayer2(char symbol) : Player(symbol) {}

    void getmove(int& x, int& y) override {
        cout << "Enter your move (row and column): ";
        cin >> x >> y;
        x--;
        y--;
    }
};

class RandomAIPlayer2 : public RandomPlayer<char> {
public:
    RandomAIPlayer2(char symbol) : RandomPlayer(symbol) {
        srand(time(0));
    }

    void getmove(int& x, int& y) override {
        x = rand() % 3;
        y = rand() % 3;
    }
};
//-----------------------------------------
//game 8
class HumanPlayer3 : public Player<char> {
public:
    HumanPlayer3(string n, char symbol) : Player(n, symbol) {}
    HumanPlayer3(char symbol) : Player(symbol) {}

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

class RandomAIPlayer3 : public RandomPlayer<char> {
public:
    RandomAIPlayer3(char symbol) : RandomPlayer(symbol) {
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
//-----------------------------------------


int main() {
    int choice ,n;
    do {
        cout << "For Exit the program Enter 0:" << endl;
        cout << "For Pyramic Tic-Tac-Toe Enter 1:" << endl;
        cout << "For Four-in-a-row Enter 2:" << endl;
        cout << "For 5 x 5 Tic Tac Toe Enter 3:" << endl;
        cout << "For Word Tic-tac-toe  Enter 4:" << endl;
        cout << "For Numerical Tic-Tac-Toe Enter 5:" << endl;
        cout << "For Misere Tic-Tac-Toe Enter 6:" << endl;
        cout << "For 4 x 4 Tic-Tac-Toe Enter 7:" << endl;
        cout << "For Ultimate Tic-Tac-Toe Enter 8:" << endl;

        while (true) {
            cin >> n;
            if (n >= 0 && n <= 8) {
                break;
            }
            cout << "Invalid choice. Please enter a number between 0 and 8: ";
        }

        switch (n)
        {
        case 1:
        {
            Player<char>* players[2];
            PyramidBoard<char>* B = new PyramidBoard<char>(3);
            string playerXName, player2Name;

            cout << "Welcome to FCAI Pyramid X-O Game. :)\n";

            // player1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";

            // Validation of input for Player X
            while (true) {
                cin >> choice;
                if (choice == 1 || choice == 2) {
                    break;
                }
                cout << "Invalid choice for Player 1. Please choose 1 or 2: ";
            }

            switch (choice) {
            case 1:
                players[0] = new Pyramid_Player<char>(playerXName, 'X');
                break;
            case 2:
                players[0] = new Pyramid_Random_Player<char>('X');
                break;
            }

            // player2
            cout << "Enter Player O name: ";
            cin >> player2Name;
            cout << "Choose Player O type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";

            // Validation of input for Player O
            while (true) {
                cin >> choice;
                if (choice == 1 || choice == 2) {
                    break;
                }
                cout << "Invalid choice for Player 2. Please choose 1 or 2: ";
            }

            switch (choice) {
            case 1:
                players[1] = new Pyramid_Player<char>(player2Name, 'O');
                break;
            case 2:
                players[1] = new Pyramid_Random_Player<char>('O');
                break;
            }

            // Assuming GameManager is properly defined
            GameManager<char> pyramid_x_o_game(B, players);
            pyramid_x_o_game.run();

            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            break;

            break;
        }
        case 2: {
            // Create the board
            ConnectFour_Board<char> board;

            // Create player 1 (always human)
            ConnectFour_Player<char> player1("Player 1", 'X');

            // Prompt for the type of player 2
            int player2_type;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Computer (Random)\n";
            cout << "Enter your choice: ";
            cin >> player2_type;

            // Create player 2 based on user input
            Player<char>* player2;
            if (player2_type == 1) {
                player2 = new ConnectFour_Player<char>("Player 2", 'O');
            }
            else {
                player2 = new ConnectFour_Random_Player<char>('O');
            }

            // Set the board for the players
            player1.setBoard(&board);
            player2->setBoard(&board);

            // Add players to the game manager
            Player<char>* players[2] = { &player1, player2 };

            // Create the game manager
            GameManager<char> game(&board, players);

            // Run the game
            game.run();

            // Clean up memory if player 2 is a computer
            if (player2_type == 2) {
                delete player2;
            }

            break;
        }
        case 3: {
            TicTacToe5x5 board;

            cout << "Welcome to 5x5 Tic Tac Toe!\n";
            cout << "Choose your opponent:\n";
            cout << "1. Play against another player\n";
            cout << "2. Play against the computer\n";

            cin >> choice;

            Player<char>* player1 = new HumanPlayer1("Player 1", 'X');
            Player<char>* player2;

            if (choice == 1) {
                player2 = new HumanPlayer1("Player 2", 'O');
            }
            else {
                player2 = new RandomAIPlayer1('O');
            }

            Player<char>* players[] = { player1, player2 };

            GameManager<char> game(&board, players);
            game.run();

            int player1_score = board.count_three_in_a_row('X');
            int player2_score = board.count_three_in_a_row('O');

            if (player1_score > player2_score) {
                cout << player1->getname() << " wins with " << player1_score << " three-in-a-rows\n";
            }
            else if (player2_score > player1_score) {
                cout << player2->getname() << " wins with " << player2_score << " three-in-a-rows\n";
            }
            else {
                cout << "It's a draw!\n";
            }

            delete player1;
            delete player2;

            break;
        }
        case 4:
        {
            string player1Name, player2Name;
            char player1Symbol, player2Symbol;

            // Create the game board
            Word_Board<char>* board = new Word_Board<char>();
            Player<char>* players[2];  // Array for players

            cout << "Welcome to Word Tic-Tac-Toe Game! :)\n";

            // Get the name of player 1
            cout << "Enter Player 1 name: ";
            cin >> player1Name;

            // Choose the type of player 1
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";

            // Validation of input for Player 1
            while (true) {
                cin >> choice;
                if (choice == 1 || choice == 2) {
                    break;
                }
                cout << "Invalid choice for Player 1. Please choose 1 or 2: ";
            }

            // Set up player 1
            if (choice == 1) {
                players[0] = new Word_Player<char>(player1Name, ' ');
            }
            else {
                players[0] = new Word_Random_Player<char>('X');  // Player 1 is a random computer player
            }

            // Get the name of player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;

            // Choose the type of player 2
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            while (true) {
                cin >> choice;
                if (choice == 1 || choice == 2) {
                    break;
                }
                cout << "Invalid choice. Please choose 1 or 2: ";
            }

            // Set up player 2
            if (choice == 1) {
                players[1] = new Word_Player<char>(player2Name, ' ');  // ÖÚ ÑãÒðÇ ÇÝÊÑÇÖíðÇ 
            }
            else {
                players[1] = new Word_Random_Player<char>('O');  // Player 2 is a random computer player
            }


            // Start the game with the chosen board and players
            GameManager<char> word_game(board, players);
            word_game.run();

            // Clean up memory after the game
            delete board;
            delete players[0];
            delete players[1];

            break;
        }
        case 5: {
            Player<int>* players[2];
            NumericalTicTacToe_Board<int>* B = new NumericalTicTacToe_Board<int>();
            string player1Name, player2Name;

            cout << "Welcome to FCAI Numerical Tic-Tac-Toe Game. :)\n";

            // Set up player 1
            cout << "Enter Player 1 name (Odd numbers): ";
            cin >> player1Name;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
            case 1:
                players[0] = new NumericalTicTacToe_Player <int>(player1Name, 1);
                break;
            case 2:
                players[0] = new NumericalTicTacToe_Random_Player <int>(1);
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
            }

            // Set up player 2
            cout << "Enter Player 2 name (Even numbers): ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
            case 1:
                players[1] = new NumericalTicTacToe_Player <int>(player2Name, 2);
                break;
            case 2:
                players[1] = new NumericalTicTacToe_Random_Player <int>(2);
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
            }

            // Create the game manager and run the game
            GameManager<int> numerical_game(B, players);
            numerical_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

            break;
        }
        case 6: {
            MisereTicTacToe board;

            cout << "Welcome to Misere Tic Tac Toe!\n";
            cout << "Choose your opponent:\n";
            cout << "1. Play against another player\n";
            cout << "2. Play against the computer\n";

            cin >> choice;

            Player<char>* player1 = new HumanPlayer2("Player 1", 'X');
            Player<char>* player2;

            if (choice == 1) {
                player2 = new HumanPlayer2("Player 2", 'O');
            }
            else {
                player2 = new RandomAIPlayer2('O');
            }

            Player<char>* players[] = { player1, player2 };

            GameManager<char> game(&board, players);
            game.run();

            delete player1;
            delete player2;

            break;
        }
        case 7: {
            Player<int>* players[2];
            DigitalTicTacToe_Board<int>* B = new DigitalTicTacToe_Board<int>();
            string player1Name, player2Name;

            cout << "Welcome to FCAI Digital Tic-Tac-Toe Game. :)\n";

            // Set up player 1
            cout << "Enter Player 1 name (Odd numbers): ";
            cin >> player1Name;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
            case 1:
                players[0] = new DigitalTicTacToe_Player<int>(player1Name, 1);
                break;
            case 2:
                players[0] = new DigitalTicTacToe_Random_Player<int>(1);
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
            }

            // Set up player 2
            cout << "Enter Player 2 name (Even numbers): ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
            case 1:
                players[1] = new DigitalTicTacToe_Player<int>(player2Name, 2);
                break;
            case 2:
                players[1] = new DigitalTicTacToe_Random_Player<int>(2);
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
            }

            // Create the game manager and run the game
            GameManager<int> digital_game(B, players);
            digital_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

            break;
        }
        case 8:
        {
            UltimateTicTacToe board;

            cout << "Welcome to Ultimate Tic Tac Toe!\n";
            cout << "Choose your opponent:\n";
            cout << "1. Play against another player\n";
            cout << "2. Play against the computer\n";

            int choice;
            cin >> choice;

            Player<char>* player1 = new HumanPlayer3("Player 1", 'X');
            Player<char>* player2;

            if (choice == 1) {
                player2 = new HumanPlayer3("Player 2", 'O');
            }
            else {
                player2 = new RandomAIPlayer3('O');
            }

            Player<char>* players[] = { player1, player2 };

            GameManager<char> game(&board, players);
            game.run();

            delete player1;
            delete player2;

            break;
        }
        case 0: {
            cout << "Exiting..." << endl;
            break;
        }
        }
    } while (n != 0);
    return 0;
}