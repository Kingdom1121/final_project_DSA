# BÁO CÁO TIẾN ĐỘ TUẦN 1 — ĐỒ ÁN CUỐI KỲ

> **Học phần:** Cấu trúc dữ liệu và Giải thuật (Data Structures and Algorithms)  
> **Mã lớp học phần:** `DASA230179_Dot1` — HK1 2026-2027  
> **Giảng viên hướng dẫn (GVHD):** ThS. Huỳnh Xuân Phụng  
> **Đề tài:** Backtracking Search for the N-Queens Problem  
> **Kho lưu trữ (Repository):** [Kingdom1121/DSA_Cuoi_Ky_Final_Project](https://github.com/Kingdom1121/DSA_Cuoi_Ky_Final_Project)  
> **Trạng thái:** Đã cập nhật và chỉnh sửa theo góp ý của GVHD

## 1. Giới thiệu đề tài

Bài toán **N-Queens** là bài toán kinh điển trong lý thuyết tìm kiếm tổ hợp (Combinatorial Search) được Donald Knuth chọn làm ví dụ nền tảng trong tài liệu **TAOCP (Vol. 4A/4B)** để phân tích kỹ thuật cắt tỉa (Pruning). 

Dự án tập trung xây dựng, đánh giá thực nghiệm và phân tích hiệu năng giữa hai phương pháp:
1. **Plain Backtracking:** Duyệt đặt quân hậu theo từng hàng, kiểm tra xung đột cột và đường chéo bằng bảng tra cứu mảng đánh dấu `vector<bool>` trong thời gian O(1).
2. **Bitmask Backtracking (Knuth's Algorithm):** Biểu diễn trạng thái cột và các đường chéo bằng các số nguyên (bitmask), sử dụng các phép toán bitwise cấp độ thanh ghi CPU (`available & -available`, dịch bit `<< 1`, `>> 1`) để cắt tỉa tối đa các nhánh thừa.

---
## 2. Các nội dung đã chỉnh sửa & tối ưu trong mã nguồn

Dựa trên mã nguồn ban đầu và yêu cầu làm rõ điều kiện đặt quân hậu, các thay đổi cụ thể gồm:

* **Tách riêng hàm kiểm tra điều kiện cho Plain Backtracking (`isSatisfyPlain`):**
  * Gom toàn bộ logic kiểm tra cột và hai đường chéo (`d1`, `d2`) ra hàm riêng thay vì viết gộp trong vòng lặp.
  * Giúp mã nguồn thể hiện rõ điều kiện an toàn $O(1)$ trước khi đặt quân hậu: `!cols[col] && !diag1[d1] && !diag2[d2]`.

* **Tách riêng hàm kiểm tra cho Bitmask Backtracking (`isSatisfyBitmask`):**
  * Tách biểu thức logic `((colmask | ld | rd) & bit) == 0` thành hàm riêng để làm rõ điều kiện bất biến (vị trí bit không giao với bất kỳ tia chiếu nào).

* **Đồng bộ hóa quy ước đếm node (`nodes++`):**
  * Đặt biến đếm `nodes++` ngay tại đầu mỗi hàm đệ quy của cả hai phương pháp để đảm bảo đo đạc công bằng trên cùng một không gian trạng thái.

* **Bổ sung chú thích giải trình thuật toán:**
  * Ghi chú rõ ý nghĩa hình học của đường chéo chính ($d_1 = row - col + n - 1$), đường chéo phụ ($d_2 = row + col$) và mặt nạ bit `all_ones = (1 << n) - 1`.
---

# BÁO CÁO TIẾN ĐỘ TUẦN 2 — HOÀN THIỆN THỰC NGHIỆM VÀ PHÂN TÍCH

Trạng thái: Hoàn thành 100% nhiệm vụ Tuần 2 theo nhận xét của GVHD.
### Bảng phân công nhiệm vụ

| STT | Họ và tên | MSSV | Vai trò | Nhiệm vụ đảm nhiệm |
| :---: | :--- | :---: | :---: | :--- |
| **1** | **Nguyễn Trọng Đại** | **25110015** | Nhóm trưởng | - Lần vết thủ công (hand-trace) và vẽ sơ đồ cây tìm kiếm vét cạn cho $N = 4$ minh họa vết cắt tỉa ([Draw_N=4_Tree.jpg](https://github.com/Kingdom1121/final_project_DSA/blob/main/Draw_N%3D4_Tree.jpg)).<br>- Kiểm tra chéo độ chính xác của bảng số liệu thực nghiệm và đối chiếu với lý thuyết Knuth TAOCP.<br>- Soạn thảo và cập nhật nội dung báo cáo tiến độ tuần 2 vào file [README.md](https://github.com/Kingdom1121/final_project_DSA/blob/main/README.md). |
| **2** | **Phan Hữu Tình** | **25110065** | Thành viên | - Bổ sung khối kiểm thử các trường hợp biên $N = 1, 2, 3$ và trực quan hóa nghiệm $N = 4$ vào mã nguồn [nqueen.cpp](https://github.com/Kingdom1121/final_project_DSA/blob/main/nqueen.cpp).[cite: 13]<br>- Xây dựng chương trình [benchmark_runner.cpp](https://github.com/Kingdom1121/final_project_DSA/blob/main/benchmark_runner.cpp) đo đạc tự động với cờ `-O3`, xuất dữ liệu thô sang [benchmark_result.txt](https://github.com/Kingdom1121/final_project_DSA/blob/main/benchmark_result.txt).<br>- Phân tích độ phức tạp $O(N!)$ so với không gian cắt tỉa thực tế $O(c^N)$ vào file [tableanalysis.txt](https://github.com/Kingdom1121/final_project_DSA/blob/main/tableanalysis.txt).[cite: 8]<br>- Quản lý repository, thực hiện commit và push mã nguồn lên GitHub. |

## Các nội dung bổ sung và chỉnh sửa trong Tuần 2 (theo góp ý của GVHD)
### 1. Bổ sung kiểm thử các trường hợp biên và mẫu nhỏ trong mã nguồn (`nqueen.cpp`)
- **Kiểm thử biên $N = 1, 2, 3$:**
  - $N = 1$: Cho ra đúng 1 nghiệm duy nhất (đặt tại ô `(0, 0)`).
  - $N = 2$ và $N = 3$: Thuật toán dừng sớm sau 3 nodes ($N=2$) và 6 nodes ($N=3$), kết luận 0 nghiệm (vô nghiệm), phản ánh chính xác lý thuyết toán tổ hợp.
- **Trực quan hóa bàn cờ mẫu nhỏ $N = 4$:**
  - Tự động in trực quan cấu hình bàn cờ của 2 nghiệm đối xứng: `[1, 3, 0, 2]` và `[2, 0, 3, 1]`.
  - Giữ nguyên toàn bộ cấu trúc và các hàm kiểm tra `isSatisfyPlain`, `isSatisfyBitmask` đã hoàn thiện từ Tuần 1.

---

### 2. Sơ đồ cây tìm kiếm vét cạn và cơ chế cắt tỉa ($N = 4$)
- Đã thực hiện lần vết thủ công (Hand-trace) và vẽ chi tiết cây tìm kiếm trạng thái đầy đủ trong file `Draw_N=4_Tree.jpg`.
- **Tổng số node duyệt:** Đúng 17 nodes (bao gồm node gốc `row = 0`).
- **Phân tích cơ chế cắt tỉa (Pruning):**
  - Tại `row = 0`, nhánh đặt hậu ở 2 biên `col = 0` hoặc `col = 3` nhanh chóng bị bế tắc ở `row = 2` do bị khống chế toàn bộ cột và đường chéo $\to$ Cắt tỉa sớm (Early Pruning).
  - Thuật toán chỉ tìm ra nghiệm khi bắt đầu tại 2 ô giữa `col = 1` hoặc `col = 2`, tạo nên 2 cấu hình nghiệm đối xứng qua trục dọc.

---

### 3. Chương trình đo đạc thực nghiệm tự động (`benchmark_runner.cpp`)
- Tách riêng file `benchmark_runner.cpp` để chạy thực nghiệm tự động trên máy cho $N \in \{8, 10, 12, 14\}$ với cờ tối ưu `g++ -O3 -std=c++11`.
- Trích xuất dữ liệu đo thời gian thuần túy (không qua lệnh in `cout`) vào file `benchmark_result.txt` để đảm bảo tính khách quan của phần cứng.

---

### 4. Bảng số liệu thực nghiệm và đối chiếu (`tableanalysis.txt`)

Bảng kết quả đo đạc thực tế trên máy:

| $N$ | Nghiệm chuẩn | Nghiệm tìm được | Số node duyệt | Thời gian Plain (s) | Thời gian Bitmask (s) | Tốc độ tăng (Speedup) |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **8** | 92 | 92 | 2,057 | 0.000107 | 0.000014 | **7.83x** |
| **10** | 724 | 724 | 35,539 | 0.001810 | 0.000184 | **9.85x** |
| **12** | 14,200 | 14,200 | 856,189 | 0.037233 | 0.003387 | **10.99x** |
| **14** | 365,596 | 365,596 | 27,358,553 | 1.217558 | 0.109270 | **11.14x** |

**Đánh giá & Nhận xét:**
- **Tính chính xác:** Số nghiệm tìm được khớp 100% với tài liệu của Donald Knuth (TAOCP Vol. 4B).
- **Tính đồng nhất:** Số node khảo sát giữa Plain và Bitmask bằng nhau tuyệt đối ở mọi kích thước $N$, chứng minh hai phương pháp duyệt trên cùng một cây trạng thái.
- **Hiệu năng:** Mức tăng tốc dao động từ `7.83x` đến `11.14x` phù hợp với các kết quả thực nghiệm chuẩn công bố trên Rosetta Code.

---

### 5. Phân tích độ phức tạp thuật toán (Complexity Analysis)
1. **Không gian hoán vị lý thuyết:** $O(N!)$ khi mỗi hàng và cột chỉ đặt đúng 1 quân hậu (với $N=14$ là $14! \approx 8.71 \times 10^{10}$ trạng thái).
2. **Không gian thực tế sau khi cắt tỉa:** Nhờ kiểm tra xung đột đường chéo $d_1, d_2$ tức thời, số node duyệt thực tế tại $N = 14$ chỉ còn $27,358,553$ nodes (chỉ chiếm $\approx 0.0314\%$ so với $14!$). Tốc độ tăng trưởng số node thực tế tuân theo hàm mũ cơ số nhỏ $O(c^N)$ với $c \approx 2.54 < 3$.
3. **Độ phức tạp không gian (Space Complexity):** $O(N)$ theo độ sâu Call Stack đệ quy tối đa $N$ tầng.
---

# BÁO CÁO TIẾN ĐỘ TUẦN 3 — MỞ RỘNG KHẢO SÁT VÀ PHÂN TÍCH XU HƯỚNG TĂNG TRƯỞNG

Trạng thái: Hoàn thành 100% nhiệm vụ Tuần 3 theo góp ý của GVHD.

### Bảng phân công nhiệm vụ

| STT | Họ và tên | MSSV | Vai trò | Nhiệm vụ đảm nhiệm |
| :---: | :--- | :---: | :---: | :--- |
| **1** | **Nguyễn Trọng Đại** | **25110015** | Nhóm trưởng | - Đối chiếu xu hướng thời gian tăng trưởng với lý thuyết giải tích hàm mũ.<br>- Phân tích và hoàn thiện đánh giá hiệu năng trong file [tableanalysis.txt](https://github.com/Kingdom1121/final_project_DSA/blob/main/tableanalysis.txt).<br>- Cập nhật nội dung báo cáo tiến độ Tuần 3 vào file [README.md](https://github.com/Kingdom1121/final_project_DSA/blob/main/README.md). |
| **2** | **Phan Hữu Tình** | **25110065** | Thành viên | - Cập nhật [benchmark_runner.cpp](https://github.com/Kingdom1121/final_project_DSA/blob/main/benchmark_runner.cpp) và [nqueen.cpp](https://github.com/Kingdom1121/final_project_DSA/blob/main/nqueen.cpp) để đo 3 mốc liên tiếp (N = 12, 13, 14) với cờ `-O3`.<br>- Thực thi kiểm thử thực tế trên máy, xuất dữ liệu thô sang [benchmark_result.txt](https://github.com/Kingdom1121/final_project_DSA/blob/main/benchmark_result.txt).<br>- Quản lý repository, thực hiện commit và push mã nguồn lên GitHub. |

---

### Các nội dung bổ sung và chỉnh sửa trong Tuần 3 (theo góp ý của GVHD)
* **Khảo sát chuỗi giá trị $N$ tăng dần liên tiếp:** Thay vì chỉ khảo sát một điểm mở rộng đơn lẻ, nhóm đã mở rộng đo đạc tại 3 mốc liên tiếp $N \in \{12, 13, 14\}$ với bước nhảy đơn vị (+1) để làm rõ xu hướng tăng trưởng thời gian.
* **Cập nhật chương trình đo đạc tự động:** Nâng cấp [benchmark_runner.cpp](https://github.com/Kingdom1121/final_project_DSA/blob/main/benchmark_runner.cpp) và bổ sung mốc $N = 13$ vào cuối mã nguồn [nqueen.cpp](https://github.com/Kingdom1121/final_project_DSA/blob/main/nqueen.cpp) (giữ nguyên 100% logic và các hàm kiểm tra từ các tuần trước).
* **Xuất dữ liệu thực nghiệm thô:** Tự động trích xuất bảng kết quả đo thực tế từ máy cá nhân vào file [benchmark_result.txt](https://github.com/Kingdom1121/final_project_DSA/blob/main/benchmark_result.txt).
* **Phân tích xu hướng tăng trưởng (Growth Trend Analysis):** Bổ sung Mục III trong file [tableanalysis.txt](https://github.com/Kingdom1121/final_project_DSA/blob/main/tableanalysis.txt), tính toán chi tiết hệ số gia tăng số node/thời gian và chứng minh không gian trạng thái thực tế bị chặn bởi hàm mũ $O(c^N)$ thay vì $O(N!)$.

---

### Bảng số liệu thực nghiệm mở rộng qua 3 mốc liên tiếp ($N = 12, 13, 14$)

Bảng kết quả đo thực tế trên máy với cờ biên dịch `g++ -O3 -std=c++11`:

| $N$ | Số nghiệm | Số node duyệt | Thời gian Plain (s) | Thời gian Bitmask (s) | Tốc độ tăng (Speedup) |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **12** | 14,200 | 856,189 | 0.038165 | 0.003396 | **11.24x** |
| **13** | 73,712 | 4,674,890 | 0.201991 | 0.017775 | **11.36x** |
| **14** | 365,596 | 27,358,553 | 1.209164 | 0.104610 | **11.56x** |

---

### Đánh giá và nhận xét xu hướng tăng trưởng

1. **Bản chất tăng trưởng hàm mũ $O(c^N)$:**
   * Khi $N$ tăng 1 đơn vị:
     * $N = 12 \to 13$: Số node tăng $\approx 5.46\text{x}$, thời gian Plain tăng $\approx 5.29\text{x}$, Bitmask tăng $\approx 5.23\text{x}$.
     * $N = 13 \to 14$: Số node tăng $\approx 5.85\text{x}$, thời gian Plain tăng $\approx 5.99\text{x}$, Bitmask tăng $\approx 5.89\text{x}$.
   * Tỷ lệ tăng trưởng qua các bước nhảy đều ổn định quanh mức $\approx 5.5\text{x}$, thấp hơn rất nhiều so với cấp số nhân hoán vị không cắt tỉa $O(N!)$ (vốn phải tăng gấp $13$ lần và $14$ lần). Điều này chứng minh thuật toán đã triệt tiêu hầu hết các nhánh bế tắc và ghìm không gian trạng thái về dạng hàm mũ cơ số nhỏ $O(c^N)$ với $c \approx 2.54$.
2. **Tính đồng pha giữa số node và thời gian:**
   * Tỷ lệ tăng thời gian thực thi của cả hai phương pháp bám rất sát tốc độ mở rộng số node duyệt trên cây tìm kiếm, phản ánh đúng chi phí xử lý trên mỗi trạng thái đệ quy.
3. **Ưu thế bền vững của Bitmask:**
   * Tỷ số tăng tốc (Speedup) tăng đều đặn từ `11.24x` $\to$ `11.36x` $\to$ `11.56x`.
   * Khẳng định việc xử lý trực tiếp trên thanh ghi CPU (bitwise) không hề suy giảm hiệu năng khi kích thước bàn cờ mở rộng, giúp tiết kiệm hơn $91\%$ thời gian so với phương pháp mảng đánh dấu truyền thống.
