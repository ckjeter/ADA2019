#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
string s1, s2;
int dp[2000][2000];
int solve(int i, int j)
{
    if (i == n || j == m) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (s1[i] != s2[j]) return dp[i][j] = solve(i+1, j+1);
    else return dp[i][j] = min({solve(i+1, j) + 1, solve(i, j+1) + 1, solve(i+1, j+1) + 1});
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> s1 >> s2;
    n = (int)s1.size(); m = (int)s2.size();
    memset(dp, -1, sizeof dp);
    cout << solve(0, 0) << endl;
}
