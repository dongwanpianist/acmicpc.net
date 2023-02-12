#include <iostream>
using namespace std;
int main() {
    uint32_t X, i;
    cin >> X;
    uint16_t dp[X+1];
    dp[1] = 0;
    for (i = 2; i <= X; ++i) {
        dp[i] = dp[i-1] + 1;
        if (i % 3 == 0) dp[i] = min(dp[i], uint16_t(dp[i/3]+1));
        if (i % 2 == 0) dp[i] = min(dp[i], uint16_t(dp[i/2]+1));
    }
    cout << dp[X] << endl;
}