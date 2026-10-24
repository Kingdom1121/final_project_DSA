#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// =========================================================================
// 1. PLAIN BACKTRACKING SOLVER
// =========================================================================

/*
Bổ sung: Tách hàm kiểm tra cho solvePlain bao gồm: 
CHECK ĐƯỜNG CHÉO CHÍNH d1
CHECK ĐƯỜNG CHÉO PHỤ d2
CHECK HÀNG VÀ BÌA KHÔNG NẰM Ở NGOÀI BIÊN
*/
bool isSatisfyPlain(int row, int col, int n, 
                    const vector<bool>& cols, 
                    const vector<bool>& diag1, 
                    const vector<bool>& diag2) {
    int d1 = row - col + n - 1; // đường chéo chính
    int d2 = row + col;         // đường chéo phụ

    // Thỏa mãn khi cột và cả 2 đường chéo đều chưa bị quân hậu khác khống chế
    return (!cols[col] && !diag1[d1] && !diag2[d2]);
}

void solvePlain(int row, int n, vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2, 
                vector<int>& board, long long& solutions, long long& nodes) {
    nodes++; // Đếm mỗi node (số trạng thái) được khảo sát

    if (row == n) {
        solutions++;
        // [Bổ sung Tuần 2]: In bàn cờ cho N = 4 (tất cả nghiệm) hoặc N = 8 (nghiệm đầu tiên)
        if ((n == 4) || (n == 8 && solutions == 1)) {
            cout << "\n  [Truc quan hoa ban co " << n << "x" << n << " - Nghiem " << solutions << "]:\n";
            for (int r = 0; r < n; r++) {
                cout << "    ";
                for (int c = 0; c < n; c++) {
                    cout << (board[r] == c ? "Q " : ". ");
                }
                cout << "\n";
            }
        }
        return;
    }

    for (int col = 0; col < n; col++) {
        // Kiểm tra nếu con hậu thỏa mãn các điều kiện để được đặt
        if (isSatisfyPlain(row, col, n, cols, diag1, diag2)) {
            int d1 = row - col + n - 1; // đường chéo chính
            int d2 = row + col;         // đường chéo phụ

            board[row] = col;
            cols[col] = diag1[d1] = diag2[d2] = true;

            solvePlain(row + 1, n, cols, diag1, diag2, board, solutions, nodes);

            // Quay lui (Backtrack)
            cols[col] = diag1[d1] = diag2[d2] = false;
        }
    }
}

// =========================================================================
// 2. BITMASK BACKTRACKING SOLVER (Knuth's Algorithm)
// =========================================================================

/*
Bổ sung: Tách hàm kiểm tra cho solveBitmask bao gồm: 
Cả ba đường chéo chính, chéo phụ và và cột không bị chiếu
*/
bool isSatisfyBitmask(int bit, int colmask, int ld, int rd) {
    return ((colmask | ld | rd) & bit) == 0;
}

void solveBitmask(int row, int ld, int rd, int colmask, int n, 
                  long long& solutions, long long& nodes) {
    nodes++;  // Đếm mỗi node (số trạng thái) được khảo sát

    int all_ones = (1 << n) - 1; // tạo ra số nhị phân có n bit 1 liên tiếp
    if (colmask == all_ones) {
        solutions++;
        return;
    }

    // Các vị trí thỏa mãn được tính song song bằng bitwise
    int available = ~(colmask | ld | rd) & all_ones;

    while (available) {
        // Lấy bit 1 thấp nhất (vị trí hợp lệ)
        int bit = available & -available;
        available -= bit;

        // Vị trí này đã được bảo đảm thỏa mãn điều kiện
        if (isSatisfyBitmask(bit, colmask, ld, rd)) {
            solveBitmask(row + 1, (ld | bit) << 1, (rd | bit) >> 1, colmask | bit, n, solutions, nodes);
        }
    }
}

// =========================================================================
// 3. MAIN BENCHMARK PIPELINE
// =========================================================================
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // [Bổ sung Tuần 2]: Kiểm tra các trường hợp biên N = 1, 2, 3 và mẫu nhỏ N = 4
    cout << "=========================================================================\n";
    cout << "   [TUAN 2] KIEM THU TRUONG HOP BIEN (N = 1, 2, 3) VA MAU NHO (N = 4)   \n";
    cout << "=========================================================================\n";
    vector<int> edge_cases = {1, 2, 3, 4};
    for (int n : edge_cases) {
        long long s_plain = 0, nd_plain = 0;
        vector<bool> cols(n, false), diag1(2 * n, false), diag2(2 * n, false);
        vector<int> board(n, 0);
        solvePlain(0, n, cols, diag1, diag2, board, s_plain, nd_plain);

        long long s_bit = 0, nd_bit = 0;
        solveBitmask(0, 0, 0, 0, n, s_bit, nd_bit);

        cout << ">>> Ket qua voi N = " << n << " <<<\n"
             << "  - Plain   : " << s_plain << " nghiem | " << nd_plain << " nodes\n"
             << "  - Bitmask : " << s_bit << " nghiem | " << nd_bit << " nodes\n";
        if (n == 2 || n == 3) cout << "  => Nhan xet: Vo nghiem dung voi ly thuyet to hop.\n";
        cout << "-------------------------------------------------------------------------\n";
    }

    // Benchmark đo đạc N = 8, 10, 12, 14
    vector<int> test_sizes = {8, 10, 12, 14};

    cout << "\n=========================================================================\n";
    cout << "          N-QUEENS BENCHMARK: PLAIN VS BITMASK (C++ VERSION)             \n";
    cout << "=========================================================================\n\n";

    for (int n : test_sizes) {
        cout << ">>> KHAO SAT VOI N = " << n << " <<<\n";

        // 1. Plain Backtracking
        long long plain_sols = 0, plain_nodes = 0;
        vector<bool> cols(n, false), diag1(2 * n, false), diag2(2 * n, false);
        vector<int> board(n, 0);
        
        auto t1 = high_resolution_clock::now();
        solvePlain(0, n, cols, diag1, diag2, board, plain_sols, plain_nodes);
        auto t2 = high_resolution_clock::now();
        double time_plain = duration<double>(t2 - t1).count();

        cout << "  [Plain Backtracking]\n"
             << "    - So nghiem tim duoc : " << plain_sols << "\n"
             << "    - So node khao sat   : " << plain_nodes << "\n"
             << "    - Thoi gian          : " << fixed << setprecision(6) << time_plain << " s\n";

        // 2. Bitmask Backtracking
        long long bitmask_sols = 0, bitmask_nodes = 0;
        
        auto t3 = high_resolution_clock::now();
        solveBitmask(0, 0, 0, 0, n, bitmask_sols, bitmask_nodes);
        auto t4 = high_resolution_clock::now();
        double time_bitmask = duration<double>(t4 - t3).count();

        cout << "  [Bitmask Backtracking (Optimized)]\n"
             << "    - So nghiem tim duoc : " << bitmask_sols << "\n"
             << "    - So node khao sat   : " << bitmask_nodes << "\n"
             << "    - Thoi gian          : " << fixed << setprecision(6) << time_bitmask << " s\n";

        if (time_bitmask > 1e-6) {
            cout << "  => Speedup (Thoi gian) : " << setprecision(2) << (time_plain / time_bitmask) << "x nhanh hon\n";
        }
        cout << "-------------------------------------------------------------------------\n\n";
    }

    // [Bổ sung Tuần 3]: Khảo sát bổ sung mốc N = 13 để kết hợp với N = 12 và N = 14 tạo thành bộ 3 giá trị tăng dần liên tiếp (12 -> 13 -> 14)
    cout << "=========================================================================\n";
    cout << "   [TUAN 3] KHAO SAT MO RONG BO SUNG N = 13 (DANH GIA XU HUONG 12->13->14)\n";
    cout << "=========================================================================\n\n";
    vector<int> extended_sizes = {13};
    for (int n : extended_sizes) {
        cout << ">>> KHAO SAT BO SUNG VOI N = " << n << " <<<\n";

        long long plain_sols = 0, plain_nodes = 0;
        vector<bool> cols(n, false), diag1(2 * n, false), diag2(2 * n, false);
        vector<int> board(n, 0);

        auto t1 = high_resolution_clock::now();
        solvePlain(0, n, cols, diag1, diag2, board, plain_sols, plain_nodes);
        auto t2 = high_resolution_clock::now();
        double time_plain = duration<double>(t2 - t1).count();

        cout << "  [Plain Backtracking]\n"
             << "    - So nghiem tim duoc : " << plain_sols << "\n"
             << "    - So node khao sat   : " << plain_nodes << "\n"
             << "    - Thoi gian          : " << fixed << setprecision(6) << time_plain << " s\n";

        long long bitmask_sols = 0, bitmask_nodes = 0;
        auto t3 = high_resolution_clock::now();
        solveBitmask(0, 0, 0, 0, n, bitmask_sols, bitmask_nodes);
        auto t4 = high_resolution_clock::now();
        double time_bitmask = duration<double>(t4 - t3).count();

        cout << "  [Bitmask Backtracking (Optimized)]\n"
             << "    - So nghiem tim duoc : " << bitmask_sols << "\n"
             << "    - So node khao sat   : " << bitmask_nodes << "\n"
             << "    - Thoi gian          : " << fixed << setprecision(6) << time_bitmask << " s\n";

        if (time_bitmask > 1e-6) {
            cout << "  => Speedup (Thoi gian) : " << setprecision(2) << (time_plain / time_bitmask) << "x nhanh hon\n";
        }
        cout << "-------------------------------------------------------------------------\n\n";
    }

    return 0;
}
