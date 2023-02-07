bool debug = false;
#include <iostream>
#include <vector>
using namespace std;
typedef struct node {
    int target;
    int time;
} node;
vector<vector<node>> graph;
vector<bool> visited;
int N, farthestcursor, maxquiz, maxquizmintime;
inline void dfsinit() {
    visited = vector<bool>(N+1, false);
    maxquiz = 1;
    maxquizmintime = 0;
}
void dfs(int cursor, int totalquiz, int totaltime) {
    if (debug) cout << " - dfs (cursor = " << cursor << ", totalquiz = " << totalquiz << ", totaltime = " << totaltime << ")\n";
    if (maxquiz < totalquiz) {
        farthestcursor = cursor;
        maxquiz = totalquiz;
        maxquizmintime = totaltime;
    } else if (maxquiz == totalquiz) if (maxquizmintime > totaltime) {
        farthestcursor = cursor;
        maxquizmintime = totaltime;
    }
    visited[cursor] = true;
    for (node n : graph[cursor]) if (!visited[n.target]) dfs(n.target, totalquiz + 1, totaltime + n.time);
}
int main() {
    int i, T, A, B, C;
    cin >> N >> T;
    graph.resize(N+1);
    for (i = 1; i < N; ++i) {
        cin >> A >> B >> C;
        graph[A].push_back({B, C});
        graph[B].push_back({A, C});
    }
    // 입력을 잘하면 반은 가므로, 잘 입력되었는지 출력(debugging process)
    if (debug) for (i = 1; i <= N; ++i) {
        cout << "Node #" << i << " has " << graph[i].size() << " targets. { ";
        for (node n : graph[i]) cout << n.target << "(" << n.time << ") ";
        cout << "}\n";
    }

    dfsinit();
    dfs(1, 1, 0);

    dfsinit();
    dfs(farthestcursor, 1, 0);

    if (debug) cout << "maxquiz mintime = " << maxquizmintime << endl;
    cout << (maxquizmintime / T) + (maxquizmintime % T > 0) << endl;
}
