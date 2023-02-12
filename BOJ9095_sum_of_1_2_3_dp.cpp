#include <iostream>
using namespace std;
int main() {
    uint16_t T, i;
    cin >> T;
    uint16_t dp[11] = {0, 1, 2, 4};
    for (i = 4; i <= 11; ++i) dp[i] = dp[i-1] + dp[i-2] + dp[i-3];
    while (T--) {
        cin >> i;
        cout << dp[i] << endl;
    }
}