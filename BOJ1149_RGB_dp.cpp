#include <iostream>
#include <vector>
using namespace std;
const uint32_t inf = 0xFFFFFFFFU;
typedef enum color : uint8_t { R, G, B } color;
typedef struct _house {
    uint16_t cost[3];
    inline uint16_t& operator[](color c) { return cost[c]; }
    inline friend istream& operator>>(istream &ist, _house &h) {
        ist >> h.cost[0] >> h.cost[1] >> h.cost[2];
        return ist;
    }
} _house;
vector<_house> house;
uint16_t N, i;
typedef struct _dpmemo {
    uint32_t totalcost[3] = {inf, inf, inf};
    inline uint32_t& operator[](color c) { return totalcost[c]; }
} _dpmemo;
vector<_dpmemo> dpmemo;
uint32_t dp(uint16_t cursor, color color) {
    if (dpmemo[cursor][color] != inf) return dpmemo[cursor][color];
    dpmemo[cursor][color] = house[cursor][color];
    if (cursor < N-1) {
        uint32_t nextdpmin = inf;
        if (color != R) nextdpmin = min(nextdpmin, dp(cursor+1, R));
        if (color != G) nextdpmin = min(nextdpmin, dp(cursor+1, G));
        if (color != B) nextdpmin = min(nextdpmin, dp(cursor+1, B));
        dpmemo[cursor][color] += nextdpmin;
    }
    return dpmemo[cursor][color];
}
int main() {
    cin >> N;
    house.resize(N);
    for (i = 0; i < N; ++i) cin >> house[i];
    dpmemo.resize(N);
    cout << min({dp(0, R), dp(0, G), dp(0, B)}) << endl;
}