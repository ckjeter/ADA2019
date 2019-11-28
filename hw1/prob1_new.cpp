#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

vector<long long> p;
vector<long long> f;
vector<long long> sort;

int greet(int k, int i)
{
	/*
	-1: 在範圍左邊
	0:在範圍內
	1: 在範圍右邊
	*/
	if (p[i]+f[i] < sort[k])
	{
		return 1;
	}
	else if (p[i]-f[i] > sort[k])
	{
		return -1;
	}
	else return 0;

}

long long find_right(int left, int right, int i)
{
	if (left > right)
	{
		if (greet(right, i) == 0)
		{
			return right;
		}
		else return -1;
	}
	int k = left + (right - left)/2;
	if (greet(k, i) == -1 && k < sort.size()-1)
	{
		return find_right(k + 1, right, i);
	}
	else if (greet(k, i) == 1 && k > 0)
	{
		return find_right(left, k - 1, i);
	}
	else
	{
		if (k == sort.size()-1)
		{
			return k;
		}
		else
		{
			if (greet(k+1, i) == 1)
			{
				return k;
			}
			else return find_right(k + 1, right, i);
		}
	}


}

long long find_left(int left, int right, int i)
{
	if (left > right)
	{
		return right;
	}
	int k = left + (right - left)/2;
	//cout<<"k: "<<k<<endl;
	if (greet(k, i) == -1 && k < sort.size()-1)
	{
		return find_left(k + 1, right, i);
	}
	else if (greet(k, i) == 1 && k > 0)
	{
		return find_left(left, k - 1, i);
	}
	else if (greet(k, i) == 0)
	{
		if (k == 0)
		{
			return k;
		}
		else
		{
			if (greet(k-1, i) == -1)
			{
				//cout<<"asd"<<endl;
				return k;
			}
			else return find_left(left, k-1, i);
		}
	}


}

int search(int left, int right, int i)
{
	if (left > right)
	{
		return left;
	}
	int k = left + (right - left)/2;
	if (p[i] <= sort[k])
	{
		return search(left, k-1, i);
	}
	else return search(k+1, right, i);

}

/*
5
18 0 14 8 12
9 8 14 4 11

10
17 17 10 10 0 1 6 6 17 13
12 16 18 12 16 6 6 16 15 16
*/
int main(int argc, char const *argv[])
{
	int N;

	scanf("%d", &N);
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

	long long count = 0;
	sort.push_back(p[0]);
	for (int i = 1; i < N; ++i)
	{
		count += max(1ll * 0, find_right(0, sort.size()-1, i) - find_left(0, sort.size()-1, i) + 1);
		//cout<<find_left(0, sort.size()-1, i)<<endl;
		//cout<<find_right(0, sort.size()-1, i)<<endl;
		sort.insert(sort.begin()+search(0, sort.size()-1, i), p[i]);
		/*
		for (int j = 0; j < sort.size(); ++j)
		{
			cout<<sort[j]<<" ";
		}
		//cout<<endl;
		//cout<<"count: "<<count<<endl;
		//cout<<"-----------------"<<endl;
		*/
	}

	//cout<<find_left(0, sort.size()-1, N-2)<<endl;
	//cout<<find_right(0, sort.size()-1, N-2)<<endl;
	printf("%lld\n", count);
/*
	for (int j = 0; j < sort.size(); ++j)
	{
		cout<<sort[j]<<" ";
	}
	cout<<endl;
*/

	return 0;
}