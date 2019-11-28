//####################################
//參考以下網站：https://reurl.cc/jdl74p #
//####################################
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
5
18 0 14 8 12
9 8 14 4 11

10
17 17 10 10 0 1 6 6 17 13
12 16 18 12 16 6 6 16 15 16
*/
long long N;
vector<long long> p;
vector<long long> f;
long long ans = 0;

long long search(long long left, long long right, long long value, int flag)
{
	if (left > right)
	{
		return left;
	}
	long long k = left + (right - left)/2;
	if (value < p[k])
	{
		return search(left, k-1, value, flag);
	}
	else if (value > p[k])
	{ 
		return search(k+1, right, value, flag);
	}
	else if (flag == 1)
	{
		return search(k+1, right, value, flag);
	}
	else return search(left, k-1, value, flag);
}

void merge(long long left, long long right)
{
	
	if (left == right)
	{
		return;
	}

	long long mid = left + (right-left) / 2;
	merge(left, mid);
	merge(mid+1, right);
	long long n = left, m = mid + 1;
	long long tempsize = right - left + 1;
	long long temp[tempsize];
	long long temf[tempsize];
	long long i = 0;
	while(n <= mid || m <= right)
	{
		if (m > right || (n <= mid && p[m] >= p[n])) //p[m] > p[n]
		{
			temf[i] = f[n];
			temp[i++] = p[n++];
		}
		else
		{
			long long pos1 = search(left, mid, p[m] + f[m], 1);
			long long pos2 = search(left, mid, p[m] - f[m], 0);
/*
			for (int k = pos2; k <= pos1 - 1; ++k)
			{
				cout<<p[m]<<" greets to "<<p[k]<<endl;
			}
			*/
			//cout<<p[m]+f[m]<<" pos: "<<pos1<<endl;
			//cout<<p[m]-f[m]<<" pos: "<<pos2<<endl;
			
			ans += pos1 - pos2;
			temf[i] = f[m];
			temp[i++] = p[m++];
		}
	
	}
/*
	for (int j = left; j <= mid; ++j)
	{
		cout<<temp[j]<<" ";
	}
	cout<<"|| ";
	for (int j = mid+1; j <= right; ++j)
	{
		cout<<temp[j]<<" ";
	}
	cout<<endl;
*/
	for (int k = 0; k < tempsize; k++)
	{
		f[left] = temf[k];
		p[left++] = temp[k];
	}


}

int main()
{
	scanf("%lld", &N);
	//sort.resize(N);
	p.resize(N);
	f.resize(N);

	for (int j = 0; j < N; ++j)
	{
		scanf("%lld", &p[j]);
	}
	for (int j = 0; j < N; ++j)
	{
		scanf("%lld", &f[j]);
	}

	merge(0, N-1);
	printf("%lld\n", ans);

	return 0;
}