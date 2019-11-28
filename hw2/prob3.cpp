#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
using namespace std;

int dp[2][100][100*100];
int main()
{
	int N, K;
	scanf("%d %d", &N, &K);
	int _A[N], A[N];
	int _B[N], B[N];
	int Bsum[N];

	multimap<float, int> ratio;
	multimap<float, int>::iterator it;
	for (int i = 0; i < N; ++i)
	{
		scanf("%d %d", &_A[i], &_B[i]);
		ratio.insert(pair<float, int>((float)_A[i]/_B[i], i));
	}

	int count = 0;
	for (it = ratio.begin(); it != ratio.end(); it++) {
		A[count] = _A[it->second];
		B[count] = _B[it->second];
		count++;
	}


	Bsum[0] = B[0];
	for (size_t i = 1; i < N; i++) {
		Bsum[i] = Bsum[i-1] + B[i];
	}

	//initialize
	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < K; j++) {
			for (size_t k = 0; k < 100 * N; k++) {
				dp[i][j][k] = -1;
			}
		}
	}
	dp[0][0][B[0]] = 0;

	//calculate
	for (int i = 1; i < N; i++) {
		//initialize
		for (size_t b = 0; b <= i; b++) {
			dp[i % 2][0][B[b]] = 0;
		}
		for (int j = 1; j < K; j++) {
			if (i < j) break;
			for (int b = 0; b < 100 * N; b++) {
				if (b - B[i] >= 0 && dp[(i - 1) % 2][j - 1][b - B[i]] != -1) {
					dp[i % 2][j][b] = max(dp[(i - 1) % 2][j][b], dp[(i - 1) % 2][j - 1][b - B[i]]+((b - B[i]) * A[i]));
				}
				else dp[i % 2][j][b] = dp[(i - 1) % 2][j][b];
			}
		}
	}

	int answer = 0;
	for (size_t k = 0; k < 100 * N; k++) {
		answer = max(answer, dp[(N - 1) % 2][K - 1][k]);
	}
	cout<<answer<<endl;


	return 0;
}
