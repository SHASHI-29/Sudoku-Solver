#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>     // For timing
#include <fstream>    // For writing scores
#include <cstdio>     // For deleting file
using namespace std;

// Include puzzle and solution data
#include "puzzles_data.cpp"
#include "solutions_data.cpp"

// Print the Sudoku grid
void print_sudoku(const string& puzzle, int size) {
    int box_size = (size == 9) ? 3 : 2;

    string horizontal_separator;
    for (int i = 0; i < size; ++i) {
        horizontal_separator += "--";
        if ((i + 1) % box_size == 0 && i != size - 1)
            horizontal_separator += "+";
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (j % box_size == 0 && j != 0)
                cout << "| ";
            
            char ch = puzzle[i * size + j];
            cout << (ch == '0' ? "_ " : string(1, ch) + " ");
        }
        cout << '\n';

        // Print separator line after every box row
        if ((i + 1) % box_size == 0 && i != size - 1) {
            cout << horizontal_separator << '\n';
        }
    }
}



// Check if the user's solution is valid
bool is_valid_solution(const string& puzzle, const string& user, int size) {
    for (int i = 0; i < size * size; ++i) {
        if (puzzle[i] != '0' && puzzle[i] != user[i])
            return false;
    }

    for (int i = 0; i < size; ++i) {
        vector<bool> row(size + 1, false), col(size + 1, false);
        for (int j = 0; j < size; ++j) {
            int row_val = user[i * size + j] - '0';
            int col_val = user[j * size + i] - '0';

            if (row_val < 1 || row_val > size || row[row_val])
                return false;
            if (col_val < 1 || col_val > size || col[col_val])
                return false;

            row[row_val] = true;
            col[col_val] = true;
        }
    }

    return true;
}

// Get a random puzzle
string get_random_puzzle(int size, int percent, int& index_out) {
    int index = rand() % 4;
    index_out = index;

    if (size == 4) {
        return (percent == 70) ? puzzles_4x4_70[index] : puzzles_4x4_30[index];
    } else {
        return (percent == 70) ? puzzles_9x9_70[index] : puzzles_9x9_30[index];
    }
}

// Get correct solution
string get_solution(int size, int percent, int index) {
    if (size == 4) {
        return (percent == 70) ? solutions_4x4_70[index] : solutions_4x4_30[index];
    } else {
        return (percent == 70) ? solutions_9x9_70[index] : solutions_9x9_30[index];
    }
}

// Clear the scoreboard file
void clear_scores() {
    ofstream ofs("scores.txt", ofstream::out | ofstream::trunc);
    if (ofs.is_open()) {
        ofs.close();
        cout << "Scores cleared successfully.\n";
    } else {
        cout << "Failed to clear scores.\n";
    }
}

int main() {
    srand(time(0));
    cout << "Welcome to Sudoku Game!\n";

    while (true) {
        cout << "\n1. Play Game\n2. Clear Scores\n3. Exit\nChoose option: ";
        int menu;
        cin >> menu;

        if (menu == 2) {
            clear_scores();
            continue;
        } else if (menu == 3) {
            break;
        } else if (menu != 1) {
            cout << "Invalid option. Try again.\n";
            continue;
        }

        int size, percent;
        cout << "\nEnter grid size (4 or 9): ";
        cin >> size;
        if (size != 4 && size != 9) {
            cout << "Only 4x4 and 9x9 supported.\n";
            continue;
        }

        cout << "Select difficulty (30 or 70% clues): ";
        cin >> percent;
        if (percent != 30 && percent != 70) {
            cout << "Only 30 or 70 accepted.\n";
            continue;
        }

        int puzzle_index;
        string puzzle = get_random_puzzle(size, percent, puzzle_index);
        string correct_solution = get_solution(size, percent, puzzle_index);

        cout << "\nSolve this Sudoku puzzle:\n\n";
        print_sudoku(puzzle, size);

        auto start_time = chrono::steady_clock::now(); // ⏱️ Start timer

        string user_input;
        cout << "\nEnter your solution as a single " << size * size << "-digit string:\n";
        cin >> user_input;

        auto end_time = chrono::steady_clock::now();   // ⏱️ End timer
        auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time).count();

        bool valid = false;
        if (user_input.length() != size * size) {
            cout << "Invalid input length.\n";
        } else if (is_valid_solution(puzzle, user_input, size)) {
            if (user_input == correct_solution) {
                cout << "Correct solution!\n";
                valid = true;
            } else {
                cout << "Structure valid, but values are incorrect.\n";
            }
        } else {
            cout << "Invalid row/column values or incorrect fixed positions.\n";
            cout << "Correct solution was:\n";
            print_sudoku(correct_solution, size);
        }

        cout << "Time taken: " << duration << " seconds\n";

        // Write result to scoreboard
        ofstream fout("scores.txt", ios::app);
        if (fout.is_open()) {
            fout << "Grid: " << size << "x" << size
                 << ", Difficulty: " << percent << "%, "
                 << "Time: " << duration << "s, "
                 << (valid ? "Correct " : "Incorrect ") << "\n";
            fout.close();
        } else {
            cout << "Unable to save score.\n";
        }

        char choice;
        cout << "\nPlay again? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') break;
    }

    cout << "\nThanks for playing!\n";
    return 0;
}