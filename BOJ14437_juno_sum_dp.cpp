#include <iostream>
using namespace std;
typedef uint16_t n;
typedef uint64_t N;
char str[3001];
N dp[3001][3001];
const uint64_t MOD = 1000000007ULL;
inline n strlen(char* str){n i;while(str[i]!=0)++i;return i;}
int main() {
    n goalsum, len, i, j;
    cin >> goalsum >> str;
    len = strlen(str);
    dp[0][0] = 1;
    for (i = 1; i <= len; ++i) {
        N sum = 0;
        for (j = 0; j <= goalsum; ++j) {
            sum += dp[i-1][j];
            sum %= MOD;
            if (j > 25) {
                sum += MOD; // 언더플로 방지
                sum -= dp[i-1][j-26];
                sum %= MOD;
            }
            dp[i][j] = sum;
        }
    }
    cout << dp[len][goalsum] << endl;
    for (i = 0; i <= len; ++i) {
        for (j = 0; j <= goalsum; ++j) cout << dp[i][j] << " ";
        cout << "\n";
    }
}
