#include <iostream>
using namespace std;
typedef uint64_t n;
#define F(i,a) for (i = a; i <= N; ++i)
int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    n N, M, input, i, j, fromh, fromw, toh, tow;
    cin >> N >> M;
    n sum[N+1][N+1];
    F(i,0) sum[i][0] = sum[0][i] = 0; // 0번배열값을 0으로 초기화 = 2N
    F(i,1) F(j,1) {
        cin >> input;
        sum[i][j] = input + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1]; // 입력한 값을 곧바로 누적합배열에 계산 = 연산 O(1) x 배열크기 N^2
    }
    while (M--) {
        cin >> fromh >> fromw >> toh >> tow;
        cout << sum[toh][tow] + sum[fromh-1][fromw-1] - sum[toh][fromw-1] - sum[fromh-1][tow] << "\n"; // 바로 계산하여 출력 = 연산 O(1) x 문제수 M
    }
}