#include <iostream>
using namespace std;
uint32_t dpmemo[1001] = {0,1,2};
uint32_t dp(uint32_t n) {
    if (dpmemo[n] > 0) return dpmemo[n];
    dpmemo[n] = (dp(n-1) + dp(n-2)) % 10007;
    return dpmemo[n];
}
int main() {
    uint32_t n;
    cin >> n;
    cout << dp(n) << endl;
}