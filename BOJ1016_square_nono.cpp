#include <iostream>
#include <vector>
using namespace std;
int main() {
    uint64_t nmin, nmax, i, ii, square_nono_count;
    cin >> nmin >> nmax;
    square_nono_count = nmax - nmin + 1;
    vector<uint64_t> square;
    for (i = 2; ii = i*i, ii <= nmax; ++i) square.push_back(ii);
    vector<bool> square_nono(square_nono_count, true);
    for (uint64_t &ii : square) {
        uint64_t m, iim;
        for (m = nmin/ii + (nmin%ii > 0); iim = ii * m, iim <= nmax; ++m) square_nono[iim-nmin] = false;
    }
    for (bool b : square_nono) if (!b) --square_nono_count;
    cout << square_nono_count << endl;
}