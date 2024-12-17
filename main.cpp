#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// بررسی امنیت وزیر در موقعیت فعلی
bool isSafe(const vector<vector<int>>& board, int row, int col) {
    int rows = board.size();
    int cols = board[0].size();

    // بررسی ستون
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) return false;
    }

    // بررسی قطر چپ به بالا
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) return false;
    }

    // بررسی قطر راست به بالا
    for (int i = row, j = col; i >= 0 && j < cols; i--, j++) {
        if (board[i][j] == 1) return false;
    }

    return true;
}

// حل مسئله n-Queens با استفاده از بک‌ترکینگ
bool solveNQueens(vector<vector<int>>& board, int row, vector<vector<vector<int>>>& solutions) {
    int rows = board.size();
    int cols = board[0].size();

    if (row == rows) {
        solutions.push_back(board);
        return true;
    }

    bool foundSolution = false;
    for (int col = 0; col < cols; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;
            foundSolution = solveNQueens(board, row + 1, solutions) || foundSolution;
            board[row][col] = 0;
        }
    }

    return foundSolution;
}

int main() {
    int rows, cols;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    vector<vector<int>> board(rows, vector<int>(cols, 0));
    vector<vector<vector<int>>> solutions;

    solveNQueens(board, 0, solutions);

    ofstream outFile("solutions.txt");
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    outFile << "Total Solutions: " << solutions.size() << "\n\n";
    for (const auto& solution : solutions) {
        for (const auto& row : solution) {
            for (int cell : row) {
                outFile << (cell == 1 ? "Q" : ".") << " ";
            }
            outFile << "\n";
        }
        outFile << string(20, '-') << "\n";
    }

    outFile.close();

    cout << "Solutions saved to solutions.txt\n";
    return 0;
}