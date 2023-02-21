#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<bool> visited;
queue<int> bfsq;
inline void bfs_push(int num) {
    if (!visited[num]) {
        visited[num] = true;
        bfsq.push(num);
    }
}
int bfs(int &from, int &to) {
    int i, num, counter = -1;
    visited.resize(max(from, to) + 2);
    bfsq.push(from);
    while (++counter, (i = bfsq.size())) {
        while (i--) {
            num = bfsq.front(); bfsq.pop();
            if (num == to) return counter;
            if (num >= 1) bfs_push(num - 1);
            if (num <= to) bfs_push(num + 1);
            if (num * 2 <= to + 1) bfs_push(num * 2);
        }
    }
    return counter;
}
int main() {
    int from, to;
    cin >> from >> to;
    cout << bfs(from, to) << endl;
}