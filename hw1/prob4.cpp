#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void reverseStr(string& str) 
{ 
    int n = str.length(); 
  
    for (int i = 0; i < n / 2; i++) 
        swap(str[i], str[n - i - 1]); 
} 

int main()
{
	string s1;
	string s2;
	cin>>s1;
	cin>>s2;
	if (s2.size() > s1.size())
	{
		string temp;
		temp = s1;
		s1 = s2;
		s2 = temp;
	}
	//reverse字串參考連少甫同學的想法
	reverseStr(s1);
	reverseStr(s2);

	vector<vector<int> > dp(s1.size()+1);
	for (int i = 0; i < dp.size(); ++i)
	{
		dp[i].resize(s2.size()+1);
	}

	//initialize
	/*
	if (s1[0] == s2[0])
	{
		dp[0][0] = 1;
	}
	else dp[0][0] = 0;
	*/
	for (int i = 0; i < dp.size(); ++i)
	{
		/*
		if (s1[i] == s2[0])
		{
			dp[i][0] = dp[i-1][0] + 1;
		}
		else dp[i][0] = dp[i-1][0];
		*/
		//dp[i][0] = dp[i-1][0];
		dp[i][0] = 0;
	}
	for (int i = 0; i < dp[0].size(); ++i)
	{
		/*
		if (s1[0] == s2[i])
		{
			dp[0][i] = dp[0][i-1] + 1;
		}
		else dp[0][i] = dp[0][i-1];
		*/
		//dp[0][i] = dp[0][i-1];
		dp[0][i] = 0;
	}

	//compute
	
	for (int i = 1; i < dp.size(); ++i)
	{
		for (int j = 1; j < dp[i].size(); ++j)
		{
			if (s1[i-1] == s2[j-1])
			{
				dp[i][j] = min(min(dp[i][j-1], dp[i-1][j]), dp[i-1][j-1])+1;
			}
			else dp[i][j] = dp[i-1][j-1];
		}
	}
	
	//find min
	int ans = dp[s1.size()][s2.size()];
/*
	if (s1.size() > s2.size())
	{
		for (int i = s2.size()-1; i <= s1.size()-1; ++i)
		{
			ans = min(ans, dp[i][s2.size()]);
		}
	}
	
	if(s1.size() < s2.size())
	{
		int len = s2.size() - s1.size();
		for (int i = s1.size() - 1; i < s2.size(); ++i)
		{
			ans = min(ans, dp[s1.size()-1][i]);
		}
	}

	else //s1.size()==s2.size()
	{
		for (int i = s1.size()-1; i >= s1.size()-2; --i)
		{
			for (int j = s2.size()-1; j >= s2.size()-2; --j)
			{
				ans = min(ans, dp[i][j]);
			}
		}
	}

	for (int i = 0; i < dp.size(); ++i)
	{
		for (int j = 0; j < dp[i].size(); ++j)
		{
			cout<<dp[i][j]<<" ";
		}
		cout<<endl;
	}
*/
	cout<<ans<<endl;
	return 0;
	
}