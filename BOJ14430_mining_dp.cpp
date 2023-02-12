#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<bool> > field;
field mymap;
istream &operator>>(istream &ist, vector<bool>::reference bit) {
    bool boolinput;
    ist >> boolinput;
    bit = boolinput;
    return ist;
}
vector<vector<uint32_t> > dpmemo;
uint32_t dp(uint16_t h, uint16_t w) {
    if (h == mymap.size()) return 0;
    if (w == mymap[0].size()) return 0;
    if (dpmemo[h][w] == 0) dpmemo[h][w] = mymap[h][w] + max(dp(h+1, w), dp(h, w+1));
    return dpmemo[h][w];
}
int main() {
    uint16_t n, m, ni, mi;
    cin >> n >> m;
    mymap.resize(n, vector<bool>(m));
    dpmemo.resize(n, vector<uint32_t>(m, 0));
    for (ni = 0; ni < n; ++ni)
    for (mi = 0; mi < m; ++mi)
        cin >> mymap[ni][mi];
    cout << dp(0, 0) << endl;
}