/*
8
1 6 6 6 1 2 3 4
12
2 5 7
2 7 8
1 5
1 8
1 8
2 5 7
1 5
2 7 8
1 7
1 5
1 8
1 5
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin>>N;
    int outlist[N+1];
    int _indegree[N+1];
    for (int i = 0; i < N+1; i++)
    {
        _indegree[i] = 0;
    }
    for (int i = 1; i <= N; i++)
    {
        cin>>outlist[i];
        _indegree[outlist[i]]++;
    }
    int Qcount;
    cin>>Qcount;
    int answer[Qcount];
    for (int i = 0; i < Qcount; i++)
    {
        int indegree[N+1];
        copy(_indegree, _indegree+N+1, indegree);
        
        int loser; //原本就不是偶像還被刪掉的人
        cin>>loser;
        int ans = 0;
        int empty = 0;  //indegree變成0的idol
        for (int j = 0; j < loser; j++)
        {
            int victim;
            cin>>victim;
            int idol = outlist[victim];
            while (indegree[idol] > 0)
            {
                indegree[idol]--;
                if (indegree[idol] >= 1) break;
                if (indegree[idol] == 0) empty++;
                idol = outlist[idol];
            }
        }
        ans = empty + loser;
        answer[i] = ans;
    }
    
    for (int i = 0; i < Qcount; i++)
    {
        cout<<answer[i]<<"\n";
    }

    return 0;
}