#include <iostream>
using namespace std;
typedef uint8_t p;
typedef bool sudoku_counter[10];
p board[9][9];
sudoku_counter r[9], c[9], s[9]; // = {};
/* square_index conversion:
   (w) 0 1 2 3 4 5 6 7 8
(h)
0      0 0 0 1 1 1 2 2 2
1      0 0 0 1 1 1 2 2 2
2      0 0 0 1 1 1 2 2 2
3      3 3 3 4 4 4 5 5 5
4      3 3 3 4 4 4 5 5 5
5      3 3 3 4 4 4 5 5 5
6      6 6 6 7 7 7 8 8 8
7      6 6 6 7 7 7 8 8 8
8      6 6 6 7 7 7 8 8 8
*/
inline p s_i(p h, p w) { return (h / 3 * 3) + (w / 3); }
inline void add_counter(p h, p w, p n) { r[h][n] = c[w][n] = s[s_i(h, w)][n] = true; }
inline void remove_counter(p h, p w, p n) { r[h][n] = c[w][n] = s[s_i(h, w)][n] = false; }
inline void set_board(p h, p w, p n) { board[h][w] = n; add_counter(h, w, n); }
inline void unset_board(p h, p w, p n) { board[h][w] = 0; remove_counter(h, w, n); }
inline bool check_board(p h, p w, p n) { return ((r[h][n] == true) || (c[w][n] == true) || (s[s_i(h, w)][n] == true)); }
bool sudoku_solve(p h, p w) {
    if (w == 9) w = 0, ++h;
    if (h == 9) return true;
    if (board[h][w] != 0) return sudoku_solve(h, w+1);

    for (p n = 1; n <= 9; ++n) {
        if (!check_board(h, w, n)) {
            set_board(h, w, n);
            if (sudoku_solve(h, w+1)) return true;
            unset_board(h, w, n);
        }
    }
    return false;
}
int main() {
    for (p h = 0; h < 9; ++h)
    for (p w = 0; w < 9; ++w) {
        cin >> board[h][w];
        board[h][w] -= '0';
        if (board[h][w]) add_counter(h, w, board[h][w]);
    }
    
    assert(sudoku_solve(0, 0) == true); // 반드시 풀 수 있는 문제였어야 함

    for (p h = 0; h < 9; ++h) {
        for (p w = 0; w < 9; ++w)
            cout << uint16_t(board[h][w]);
        cout << '\n';
    }
}
