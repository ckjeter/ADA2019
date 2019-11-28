#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

vector<int> P;
vector<vector<int> >pmax;
vector<vector<int> >pmin;



int combine(int mid, int left, int right)
{
	int count = 0;
	for (int i = mid; i >= left; --i)
	{
		for (int j = mid+1; j <= right; ++j)
		{
			if (pmax[i][j] - pmin[i][j] == j - i)
			{
				count++;		
			}
		}
	}
	return count;
	/*
	int count[4] = {0};
	int maxp;
	int minp;
	//min max在右半部
	for (int i = mid; i >= left; --i)
	{
		maxp = 0;
		minp = P.size()+1;
		for (int j = mid+1; j <= right; ++j)
		{
			maxp = max(P[j], maxp);
			minp = min(P[j], minp);
			if (P[i] > maxp || P[i] < minp)
			{
				break;
			}
			if (maxp - minp == j - i)
			{
				count[0]++;		
			}
		}
	}

	//min max在左半部
	maxp = 0;
	minp = P.size()+1;
	for (int i = mid; i >= left; --i)
	{
		maxp = max(P[i], maxp);
		minp = min(P[i], minp);
		for (int j = mid+1; j <= right; ++j)
		{		
			if (P[j] > maxp || P[j] < minp)
			{
				break;
			}
			if (maxp - minp == j - i)
			{
				count[1]++;		
			}
		}
	}

	//min左 max右
	minp = P.size()+1;
	for (int i = mid; i >= left; --i)
	{
		maxp = 0;
		minp = min(P[i], minp);
		for (int j = mid+1; j <= right; ++j)
		{
			maxp = max(P[j], maxp);
			if (P[i] > maxp || P[j] < minp)
			{
				break;
			}
			if (maxp - minp == j - i)
			{
				count[2]++;		
			}
		}
	}
	//else
	maxp = 0;
	for (int i = mid; i >= left; --i)
	{
		minp = P.size()+1;
		maxp = max(P[i], maxp);
		for (int j = mid+1; j <= right; ++j)
		{
			minp = min(P[j], minp);
			if (P[i] < minp || P[j] > maxp)
			{
				break;
			}
			if (maxp - minp == j - i)
			{
				count[3]++;		
			}
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		cout<<count[i]<<" ";
	}
	cout<<endl;
	return count[0]+count[1]+count[2]+count[3];
	*/

}

int d_c(int left, int right)
{
	if (left == right)
	{
		return 1;
	}
	else
	{
		int mid = left + (right - left) / 2;
		return d_c(left, mid) + d_c(mid+1, right) + combine(mid, left, right);
	}
}

/*
5
1 2 3 4 5

5
5 1 2 4 3

10
7 6 5 8 9 10 1 2 3 4

20
1 2 3 4 10 9 8 7 6 5 11 14 13 12 20 19 18 17 16 15
*/



int main()
{
	int N;
	scanf("%d", &N);
	P.resize(N);
	pmax.resize(N);
	pmin.resize(N);
	for (int i = 0; i < N; ++i)
	{
		pmax[i].resize(N);
		pmin[i].resize(N);
	}

	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &P[i]);
	}
	for (int i = 0; i < N; ++i)
	{
		pmax[i][i] = P[i];
		pmin[i][i] = P[i];
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			pmax[i][j] = max(pmax[i][j-1], pmax[j][j]);
			pmin[i][j] = min(pmin[i][j-1], pmin[j][j]);
		}
	}


	printf("%d\n", d_c(0, N-1));

	return 0;
}