#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef struct coordinate { int64_t h, w; } coordinate;
vector<coordinate> db;
size_t dbsize;
coordinate sum;
vector<uint8_t> combination;
double calc_combination(uint8_t cursor, uint8_t rest, coordinate tempsum) {
    if (rest == 0) return sqrt(pow(sum.h - tempsum.h*2, 2) + pow(sum.w - tempsum.w*2, 2));
    double calc = -1;
    for (uint8_t i = cursor; i <= dbsize - rest; ++i) {
        combination.push_back(i);
        double recursive = calc_combination(i + 1, rest - 1, (coordinate){tempsum.h + db[i].h, tempsum.w + db[i].w});
        if ((calc == -1) || (recursive < calc)) calc = recursive;
        combination.pop_back();
    }
    return calc;
}
inline void db_init() {
    db.clear();
    combination = vector<uint8_t>();
    sum = (coordinate){0, 0};
}
int main() {
    (cout << fixed).precision(8);
    int T;
    cin >> T;
    while (T--) {
        db_init();
        cin >> dbsize;
        db.resize(dbsize);
        while (dbsize--) cin >> db[dbsize].h >> db[dbsize].w, sum.h += db[dbsize].h, sum.w += db[dbsize].w;
        dbsize = db.size();
        cout << calc_combination(0, dbsize / 2, (coordinate){0, 0}) << '\n';
    }
}