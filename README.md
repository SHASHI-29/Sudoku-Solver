# 🧩 Sudoku Solver Game in C++

A terminal-based Sudoku Game built in C++ that supports solving 4x4 and 9x9 puzzles with difficulty levels, timer, scoreboard, and validation of your answers. All puzzles and solutions are **hardcoded in C++ files**, so no external data files are required at runtime.

---

## 🚀 Features

- ✅ Supports **4x4 and 9x9 Sudoku puzzles**
- 🎮 **Interactive** terminal-based gameplay
- 🧠 **Backtracking algorithm** for auto-solving (internal use)
- ⏱️ **Timer** to measure completion time
- 📊 **Scoreboard** (stored in `scores.txt`)
- 🔄 **Replay or exit** after solving
- 💾 **All puzzles and solutions are embedded in `.cpp` files**
- 🔐 Includes **solution checker** to validate user input

---

## 📁 Project Structure


---

## 🧠 Key DSA Concepts

- ✅ **Backtracking Algorithm**
- ✅ **2D Array Traversal & Validation**
- ✅ **Input Matching & Rule Checking**
- ✅ **Chrono Library for Timer**
- ✅ **File Handling** for scoreboard
- ✅ **String/Array operations** for grid validation

---

## 🕹️ How to Play

1. Choose Sudoku grid size (4x4 or 9x9).
2. Select difficulty (Easy or Hard).
3. A puzzle is displayed from internal data.
4. Fill in the puzzle interactively.
5. Game validates your input using the correct solution.
6. Timer stops and time is saved to `scores.txt` if it's your best.


---
## 🌱 Future Scope
Here are some ideas to enhance the game further:

1. 🧠 Auto-solver Mode: Allow the system to auto-solve any valid input using backtracking.

2. 🌐 Web Version: Convert the logic to JavaScript/WebAssembly for a browser-based game.

3. 📈 Leaderboard: Add user profiles and display top scores.

4. 🎯 Hint System: Add a feature that reveals valid values for a random cell.

5. 🔄 Save & Resume: Implement save states to resume incomplete games later.


## 🚀 Getting Started

### Requirements
- C++ compiler (g++, clang++, etc.)
- Windows/Linux/macOS terminal
- VS Code
