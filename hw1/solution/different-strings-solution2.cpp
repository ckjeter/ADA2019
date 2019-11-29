#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
string s1, s2;
int dp[4001][4001];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> s1 >> s2;
    n = (int)s1.size(); m = (int)s2.size();
    s1 += string(m, '@');
    s2 += string(n, '$');
    for (int i = 0; i <= n + m; ++i)
        dp[i][0] = i;
    for (int j = 0; j <= n + m; ++j)
        dp[0][j] = j;
    for (int i = 1; i <= n + m; ++i)
        for (int j = 1; j <= n + m; ++j)
        {
            if (s1[i-1] != s2[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = min({dp[i-1][j-1] + 1, dp[i-1][j] + 1, dp[i][j-1] + 1});
        }
    int ans = n + m;
    for (int i = n; i <= n + m; ++i)
        for (int j = m; j <= n + m; ++j)
            ans = min(ans, dp[i][j]);
    cout << ans << endl;
}
