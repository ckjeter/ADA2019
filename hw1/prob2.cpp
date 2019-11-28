#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <limits.h>

using namespace std;

int N, Q;
/*
long long maxcross(long long left, long long right, vector<long long>& segment)
{
	long long left_sum = INT_MIN;
	long long right_sum = INT_MIN;
	long long temp_sum = 0;
	if (left >= pow(2, ceil(log(N)/log(2)))+N && right >= pow(2, ceil(log(N)/log(2)))+N)
	{
		return INT_MIN;
	}
	else
	{
		int k = left+(right - left)/2;
		for (int i = k; i >= left; --i) //從k往左加
		{
			temp_sum += segment[i];
			if (temp_sum > left_sum)
			{
				left_sum = temp_sum;
			}
		}
		temp_sum = 0;
		for (int i = k + 1 ; i <= right; ++i) //從k往右加
		{
			temp_sum += segment[i];
			if (temp_sum > right_sum)
			{
				right_sum = temp_sum;
			}
		}
		
		if (left_sum < 0 && right_sum < 0)
		{
			return max(left_sum, right_sum);
		}

		if (left_sum < 0)
		{
			left_sum = 0;
		}
		if (right_sum < 0)
		{
			right_sum = 0;
		}
		return left_sum + right_sum;
	}
}
*/
void merge(long long k, vector<vector<long long> >& segment)
{
	segment[k][0] = max(segment[2*k][0], segment[2*k][2] + segment[2*k+1][0]);
	segment[k][1] = max(segment[2*k+1][1], segment[2*k+1][2] + segment[2*k][1]);
	segment[k][2] = segment[2*k][2] + segment[2*k+1][2];
	segment[k][3] = max(max(segment[2*k][3], segment[2*k+1][3]), segment[2*k][1] + segment[2*k+1][0]);
	/*
	long long l_sum = segment[2*k];
	long long r_sum = segment[2*k + 1];
	long long left = k, right = k;
	while(left < segment.size() / 2) 
	{
	    left = left * 2;
	}
	while(right < segment.size() / 2) 
	{
	    right = 2 * right + 1;
	}
	long long c_sum = maxcross(left, right, segment);

	return max(max(l_sum, r_sum), c_sum);
	*/
}

void update(long long i, long long value, vector<vector<long long> >& segment)
{
	//A[i-1] = value;
	i += pow(2, ceil(log(N)/log(2))) - 1;
	for (int j = 0; j < 4; ++j)
	{
		segment[i][j] = value;
	}
	while (i > 1)
	{
		i = i / 2;
		merge(i, segment);
	}
}


/*
8 0
-2 -3 4 -1 -2 1 5 -3
*/

/*
10 10
-1 -5 -10 0 7 -1 4 -6 -3 -4
5 -4
3 10
5 -5
10 8
3 -2
8 1
10 7
1 -7
3 4
4 9
*/
int main()
{
	scanf("%d %d", &N, &Q);
	vector<long long> p(Q);
	vector<long long> v(Q);
	vector<vector<long long> > segment(pow(2,ceil((log(N)/log(2))+1)));

/*
0) Maximum Prefix Sum
1) Maximum Suffix Sum
2) Total Sum
3) Maximum Subarray Sum
*/
	for (int i = 0; i < segment.size(); ++i)
	{
		vector<long long> temp(4); 
		for (int j = 0; j < temp.size(); ++j)
		{
			temp[j] = INT_MIN;
		}
		segment[i] = temp;
	}

	for (int i = 0; i < N; ++i)
	{
		long long temp;
		scanf("%lld", &temp);
		for (int j = 0; j < 4; ++j)
		{
			segment[pow(2, ceil(log(N)/log(2)))+i][j] = temp;
		}

	}
	for (int i = 0; i < Q; ++i)
	{
		scanf("%lld %lld", &p[i], &v[i]);
	}


	for (int i = pow(2, ceil(log(N)/log(2)))-1; i > 0; --i)
	{
		merge(i, segment);
	}


	printf("%lld\n", max(1ll*0, segment[1][3]));
	
	for (int i = 0; i < Q; ++i)
	{
		update(p[i], v[i], segment);
		printf("%lld\n", max(1ll*0, segment[1][3]));
	}

	/*
	for (int i = 0; i <= ceil(log(N)/log(2)); ++i) //i=1~4
	{
		for (int j = pow(2, i); j < pow(2, i)+pow(2, i); ++j)
		{
			cout<<segment[j][0]<<" , "<<segment[j][1]<<" , "<<segment[j][2]<<" , "<<segment[j][3]<<" || ";
		}
		cout<<endl;
	}
	*/	
	return 0;
}