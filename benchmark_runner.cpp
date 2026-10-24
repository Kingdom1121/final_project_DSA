#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace std::chrono;

// 1. Plain Solver
bool isSatisfyPlain(int row, int col, int n, 
                    const vector<bool>& cols, 
                    const vector<bool>& diag1, 
                    const vector<bool>& diag2) {
    int d1 = row - col + n - 1;
    int d2 = row + col;
    return (!cols[col] && !diag1[d1] && !diag2[d2]);
}

void solvePlain(int row, int n, vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2, 
                vector<int>& board, long long& solutions, long long& nodes) {
    nodes++;
    if (row == n) {
        solutions++;
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSatisfyPlain(row, col, n, cols, diag1, diag2)) {
            int d1 = row - col + n - 1;
            int d2 = row + col;
            board[row] = col;
            cols[col] = diag1[d1] = diag2[d2] = true;
            solvePlain(row + 1, n, cols, diag1, diag2, board, solutions, nodes);
            cols[col] = diag1[d1] = diag2[d2] = false;
        }
    }
}

// 2. Bitmask Solver
bool isSatisfyBitmask(int bit, int colmask, int ld, int rd) {
    return ((colmask | ld | rd) & bit) == 0;
}

void solveBitmask(int row, int ld, int rd, int colmask, int n, 
                  long long& solutions, long long& nodes) {
    nodes++;
    int all_ones = (1 << n) - 1;
    if (colmask == all_ones) {
        solutions++;
        return;
    }
    int available = ~(colmask | ld | rd) & all_ones;
    while (available) {
        int bit = available & -available;
        available -= bit;
        if (isSatisfyBitmask(bit, colmask, ld, rd)) {
            solveBitmask(row + 1, (ld | bit) << 1, (rd | bit) >> 1, colmask | bit, n, solutions, nodes);
        }
    }
}

struct BenchmarkItem {
    int n;
    long long solutions;
    long long nodes;
    double timePlain;
    double timeBitmask;
    double speedup;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // [Bổ sung Tuần 3]: Khảo sát mở rộng 3 giá trị N tăng dần (N = 12, 13, 14) để thấy rõ xu hướng tăng trưởng
    cout << "=========================================================================\n";
    cout << "   [TUAN 3] RUNNER DO MO RONG N TANG DAN (N = 12, 13, 14)                \n";
    cout << "=========================================================================\n";

    vector<int> test_sizes = {12, 13, 14};
    vector<BenchmarkItem> tableData;

    for (int n : test_sizes) {
        cout << "Dang chay N = " << n << " ... " << flush;

        // 1. Plain
        long long s_plain = 0, nd_plain = 0;
        vector<bool> cols(n, false), diag1(2 * n, false), diag2(2 * n, false);
        vector<int> board(n, 0);

        auto t1 = high_resolution_clock::now();
        solvePlain(0, n, cols, diag1, diag2, board, s_plain, nd_plain);
        auto t2 = high_resolution_clock::now();
        double time_plain = duration<double>(t2 - t1).count();

        // 2. Bitmask
        long long s_bit = 0, nd_bit = 0;
        auto t3 = high_resolution_clock::now();
        solveBitmask(0, 0, 0, 0, n, s_bit, nd_bit);
        auto t4 = high_resolution_clock::now();
        double time_bitmask = duration<double>(t4 - t3).count();

        double speedup = (time_bitmask > 1e-7) ? (time_plain / time_bitmask) : 1.0;

        tableData.push_back({n, s_plain, nd_plain, time_plain, time_bitmask, speedup});
        cout << "Xong!\n"
             << "  -> Plain  : " << fixed << setprecision(6) << time_plain << " s\n"
             << "  -> Bitmask: " << fixed << setprecision(6) << time_bitmask << " s\n"
             << "  -> Speedup: " << fixed << setprecision(2) << speedup << "x nhanh hon\n";
    }

    // [Bổ sung Tuần 3]: Xuất bảng dữ liệu thực nghiệm thô mở rộng ra benchmark_result.txt
    ofstream outFile("benchmark_result.txt");
    if (!outFile.is_open()) {
        cerr << "Khong the mo file benchmark_result.txt de ghi!\n";
        return 1;
    }

    outFile << "====================================================================================================\n";
    outFile << "               KET QUA DO MO RONG N TANG DAN: N = 12, 13, 14 (TUAN 3)\n";
    outFile << "====================================================================================================\n";
    outFile << left << setw(6)  << "N"
            << setw(16) << "So nghiem"
            << setw(18) << "So node da duyet"
            << setw(24) << "Thoi gian Plain (s)"
            << setw(24) << "Thoi gian Bitmask (s)"
            << "Toc do tang (Speedup)\n";
    outFile << "----------------------------------------------------------------------------------------------------\n";

    for (const auto& row : tableData) {
        outFile << left << setw(6)  << row.n
                << setw(16) << row.solutions
                << setw(18) << row.nodes
                << setw(24) << fixed << setprecision(6) << row.timePlain
                << setw(24) << fixed << setprecision(6) << row.timeBitmask
                << fixed << setprecision(2) << row.speedup << "x\n";
    }
    outFile << "----------------------------------------------------------------------------------------------------\n";
    outFile.close();

    cout << "\n>>> DA XUAT TOAN BO KET QUA TUAN 3 VAO FILE benchmark_result.txt! <<<\n";
    return 0;
}
