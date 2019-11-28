/*
7 7 1
0 1 2 6 5 4 0

8 7 1
0 6 4 3 2 1 5 0
*/
#include "stdio.h"
#include "iostream"
#include "vector"
#include "limits.h"
#include "algorithm"
#include <deque>

using namespace std;

int main()
{
    int N, K, M;
    scanf("%d %d %d", &N, &M, &K);
    vector<int> song(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &song[i]);
    }
    int dp[N][M];
    //initialize
    for (int i = 0; i < M; i++) {
        dp[0][i] = 0;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    //compute
    //int case1 = dp[i-1][k] + max(abs(j-k) - K, 0) + max(abs(song[i] - song[i - 1]) - K, 0)
    //int case2 = dp[i-1][k] + max(abs(song[i] - k) - K, 0) + max(abs(song[i - 1] - j) - K, 0)

    for (int i = 1; i < N; i++) {

        //int case2_1 = INT_MAX;
        int case1[M];
        int case2[M];
        for (int k = 0; k < M; k++) {
            //case2_1 = min(case2_1, dp[i-1][k] + max(abs(song[i]-k)-K, 0));
            case1[k] = INT_MAX;
            case2[k] = INT_MAX;
        }

        int case1_1 = -1;
        int case1_2 = max(abs(song[i] - song[i - 1]) - K, 0);
        int front = 0, back = -1;
        int case2_temp = INT_MAX;
        for (int j = 0; j < M; j++) {
            //int case1 = INT_MAX;
/*
            for (int k = max(0, j - K); k <= min(M - 1, j + K); k++) {
                case1_1 = min(case1_1, dp[i-1][k]);
            }
            */
            if (case1_1 == dp[i-1][j] && j != M-1) {
                back = min(j + K, M - 1);
            }
            else{
                for (int a = front; a <= back; a++){
                    case1[a] = min(case1[a], case1_1+case1_2);
                }
                case1_1  = dp[i-1][j];
                front = max(j - K, 0);
                back = min(j + K, M - 1);
            }
            case2_temp = min(case2_temp, dp[i-1][j] + max(abs(j-song[i]) - K ,0));
            //int case2_2 = max(abs(song[i - 1] - j) - K, 0);
            //int case1 = case1_1 + case1_2;
            //int case2 = case2_1 + case2_2;

        }
        for (int b = max(song[i-1]-K,0); b <= min(song[i-1]+K,M-1) ; b++){
            case2[b] = case2_temp;
        }

        for (size_t j = 0; j < M; j++) {
            dp[i][j] = min(case1[j], case2[j]);
        }

    }

    int ans = dp[N-1][0];
    for (size_t i = 0; i < M; i++) {
        ans = min(ans, dp[N-1][i]);
    }

    printf("%d\n", ans);

    return 0;
}
