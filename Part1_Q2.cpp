
#include <iostream>
#include <string>
#include <vector>
#define l '\n'
using namespace std;

const int MOD = 1e9 + 7;

int countOriginalStrings(const string& s) {
    int n = s.size();

    for (char c : s) {
        if (c == 'm' || c == 'w') {   // Check for invalid characters
            return 0;        // because the message sender will not send any message contains “w" or "m"
        }
    }

    vector<int> dp(n + 1, 0);//fill it with 0
    dp[0] = 1;
    dp[1] = 1; //(single character is always valid unless it's 'm' or 'w')

    for (int i = 2; i <= n; ++i) { // start with 2
        dp[i] = dp[i - 1];
        if ((s[i - 1] == 'u' && s[i - 2] == 'u') || (s[i - 1] == 'n' && s[i - 2] == 'n')) {
            dp[i] = (dp[i] + dp[i - 2]) % MOD;   //Perform all calculations modulo to avoid overflow and meet the constraints.
        }
    }

    return dp[n];
}

int main() {
    string inp;
    cin >> inp;
    cout<<countOriginalStrings(inp)<<l;
}
