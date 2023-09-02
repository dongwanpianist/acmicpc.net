#include <iostream>
#include <bitset>
#include <stack>
using namespace std;
typedef uint8_t char_index;
typedef uint16_t pointer;
struct coordinate {
    pointer         h, w;
    coordinate      offset(const int& h_offset, const int& w_offset) {
        return coordinate{pointer(h + h_offset), pointer(w + w_offset)};
    }
};
struct dfs_data {
    union { coordinate  cursor; struct { pointer h, w; }; };
    bitset<26>      visited;
    dfs_data        neighbor(const int& h_offset, const int& w_offset, const char_index& alphabet) {
        dfs_data result = {cursor.offset(h_offset, w_offset), visited};
        result.visited[alphabet] = true;
        return result;
    }
};
int main() {
    coordinate      mysize;
    char            buf;
    stack<dfs_data> dfs;
    char_index      max_count = 0;

    cin >> mysize.h >> mysize.w;
    char_index      mymap[mysize.h][mysize.w];

    for (pointer h = 0; h < mysize.h; ++h)
    for (pointer w = 0; w < mysize.w; ++w) {
        cin >> buf;
        mymap[h][w] = buf - 'A'; // 0~25
    }

    dfs.push(dfs_data{{0,0}}.neighbor(0,0,mymap[0][0]));
    while (dfs.size()) {
        dfs_data c = dfs.top();
        dfs.pop();
        bool dfs_next = false;
        if (c.h > 0)            if (!c.visited[mymap[c.h-1][c.w]]) { dfs.push(c.neighbor(-1, 0, mymap[c.h-1][c.w])); dfs_next = true; }
        if (c.h < mysize.h - 1) if (!c.visited[mymap[c.h+1][c.w]]) { dfs.push(c.neighbor(+1, 0, mymap[c.h+1][c.w])); dfs_next = true; }
        if (c.w > 0)            if (!c.visited[mymap[c.h][c.w-1]]) { dfs.push(c.neighbor(0, -1, mymap[c.h][c.w-1])); dfs_next = true; }
        if (c.w < mysize.w - 1) if (!c.visited[mymap[c.h][c.w+1]]) { dfs.push(c.neighbor(0, +1, mymap[c.h][c.w+1])); dfs_next = true; }
        if (!dfs_next) max_count = max(max_count, char_index(c.visited.count()));
    }
    cout << uint16_t(max_count);
}