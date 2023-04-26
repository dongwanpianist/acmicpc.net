#include <iostream>
#include <queue>
using namespace std;
int main() {
    uint16_t N, K, i;
    cin >> N >> K;
    queue<uint16_t> circle;
    for (i = 1; i <= N; ++i) circle.push(i);
    cout << '<';
    while (!circle.empty()) {
    	for(i = 1; i <= K; ++i) {
    	    uint16_t cursor = circle.front();
    	    circle.pop();
    	    if (i < K) circle.push(cursor);
    	    else cout << cursor;
    	}
    	if (!circle.empty()) cout << ", ";
    }
    cout << '>';
}