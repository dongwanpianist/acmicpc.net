#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
typedef enum direction: uint8_t { N, W, S, E } direction;
typedef struct coordinate {
    int h, w;
    coordinate move(direction d) {
        switch (d) {
            case N:  return {h-1, w};
            case W:  return {h, w-1};
            case S:  return {h+1, w};
            default: return {h, w+1};
        }
    }
    inline coordinate &operator--() { --h; --w; return *this; }
    inline friend bool operator==(coordinate &a, coordinate &b) { return ((a.h == b.h) && (a.w == b.w)); }
    inline friend istream &operator>>(istream &ist, coordinate &c) { return ist >> c.h >> c.w;}
} coordinate;
typedef struct map {
    vector<vector<bool>> _data, _visited;
    coordinate cursor, goal;
    queue<coordinate> bfsq;
    uint16_t countstep = 0;
    map &inputsize() {
        cin >> goal;
        _data.resize(goal.h, vector<bool>(goal.w));
        _visited.resize(goal.h, vector<bool>(goal.w, false));
        --goal;
        return *this;
    }
    map &inputdata() {
        char input;
        for (int h = 0; h <= goal.h; ++h)
        for (int w = 0; w <= goal.w; ++w) {
            cin >> input; _data[h][w] = input-'0';
        }
        return *this;
    }
    inline vector<bool>::reference data(coordinate c) { return _data[c.h][c.w]; }
    inline vector<bool>::reference visited(coordinate c) { return _visited[c.h][c.w]; }
    inline void bfsq_push(coordinate c) { bfsq.push(c); _visited[c.h][c.w] = true; }
    inline coordinate bfsq_pop() { coordinate c = bfsq.front(); bfsq.pop(); return c; }
    map &move2goal() { // bfs
        bfsq_push({0, 0});
        size_t i = 0;
        coordinate c;
        while (++countstep, (i = bfsq.size())) while (i--) {
            cursor = bfsq_pop();
            if (cursor == goal) return *this;
            if (cursor.h != 0)      { c = cursor.move(N); if (data(c)) if (!visited(c)) bfsq_push(c); }
            if (cursor.w != 0)      { c = cursor.move(W); if (data(c)) if (!visited(c)) bfsq_push(c); }
            if (cursor.h != goal.h) { c = cursor.move(S); if (data(c)) if (!visited(c)) bfsq_push(c); }
            if (cursor.w != goal.w) { c = cursor.move(E); if (data(c)) if (!visited(c)) bfsq_push(c); }
        }
        return *this;
    }
} map;
int main() {
    map mymap;
    mymap.inputsize().inputdata().move2goal();
    cout << mymap.countstep << endl;
}