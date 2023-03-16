bool debug = true;
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
    int64_t nmin, nmax, i, ii, square_nono_count;
    cin >> nmin >> nmax;
    square_nono_count = nmax - nmin + 1;
    vector<int64_t> square;
    for (i = 2; ii = i*i, ii <= nmax; ++i)
        square.push_back(ii);
                                                                                                    //if (debug) { cout << "Current squares: { "; for (auto &n : square) cout << n << ' '; cout << "}\n"; }
    vector<bool> square_nono(square_nono_count, true);
                                                                                                    //if (debug) { cout << "test range :    " << nmin << "~" << nmax << " [" << nmax - nmin + 1 << "]\nreduced range : " << 0 << "~" << square_nono_count-1 << " [" << square_nono.size() << "]\n"; }
    for (int64_t &ii : square) {
        int64_t m, iim;
        for (m = nmin/ii + (nmin%ii > 0); iim = ii * m, iim <= nmax; ++m) {
            square_nono[iim-nmin] = false;
            //cout << "square_nono = " << iim << " ( " << iim-nmin << " )\n";
        }
        //if (ii >= nmin) if (ii <= nmax) --square_nono_count;
        //for (i = ceil((double)nmin/(double)ii); i <= ceil((double)nmax/(double)ii); i += ii) {
                                                                                                    //if (debug) { cout << " - checking i(" << i << ") and ii(" << ii << ")\n"; }
        //    square_nono[i-nmin+1] = false;
        //}
                                                                                                    //if (debug) { cout << "Tested square_nono: { "; for (bool b : square_nono) cout << b << ' '; cout << "}\n"; }
    }
    for (bool b : square_nono) if (!b) --square_nono_count;
    cout << square_nono_count << endl;
}