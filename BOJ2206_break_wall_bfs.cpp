#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef struct qdata { uint16_t h, w; bool broken; } qdata;
int main() {
    uint16_t n, m;
    cin >> n >> m;
    bool mymap[2][n][m];
    --n; --m;
    for (uint16_t i = 0; i <= n; ++i)
    for (uint16_t j = 0; j <= m; ++j) {
        char input;
        cin >> input;
        mymap[0][i][j] = mymap[1][i][j] = input-'0';
    }
    queue<qdata> bfsq;
    size_t qsize, turn = 0;
    bfsq.push((qdata){0, 0, 0});
    while (++turn, /*cout << "Turn " << turn << endl,*/ qsize = bfsq.size()) while (qsize--) {
        qdata q = bfsq.front(); bfsq.pop();
        //cout << " - Q (" << q.h << ", " << q.w << ") [" << (q.broken ? "V" : " ") << "]broken\n";
        if ((q.h == n) && (q.w == m)) goto print;
        if (q.h > 0) { if (mymap[q.broken][q.h-1][q.w] == 0) bfsq.push((qdata){q.h-1, q.w, q.broken}), mymap[q.broken][q.h-1][q.w] = 1;
                       else if (!q.broken)         bfsq.push((qdata){q.h-1, q.w, 1}),                  mymap[1][q.h-1][q.w] = 1; }
        if (q.w > 0) { if (mymap[q.broken][q.h][q.w-1] == 0) bfsq.push((qdata){q.h, q.w-1, q.broken}), mymap[q.broken][q.h][q.w-1] = 1;
                       else if (!q.broken)         bfsq.push((qdata){q.h, q.w-1, 1}),                  mymap[1][q.h][q.w-1] = 1; }
        if (q.h < n) { if (mymap[q.broken][q.h+1][q.w] == 0) bfsq.push((qdata){q.h+1, q.w, q.broken}), mymap[q.broken][q.h+1][q.w] = 1;
                       else if (!q.broken)         bfsq.push((qdata){q.h+1, q.w, 1}),                  mymap[1][q.h+1][q.w] = 1; }
        if (q.w < m) { if (mymap[q.broken][q.h][q.w+1] == 0) bfsq.push((qdata){q.h, q.w+1, q.broken}), mymap[q.broken][q.h][q.w+1] = 1;
                       else if (!q.broken)         bfsq.push((qdata){q.h, q.w+1, 1}),                  mymap[1][q.h][q.w+1] = 1; }
    }
    cout << "-1" << endl;
    return 0;
    print:
    cout << turn << endl;
}