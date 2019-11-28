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
#include <list>
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
    int newnode[N+1][2];
    for (int i = 0; i < N+1; i++)
    {
        _indegree[i] = 0;
        newnode[i][0] = 1; //份量
        newnode[i][1] = 0; //終點
    }
    for (int i = 1; i <= N; i++)
    {
        cin>>outlist[i];
        _indegree[outlist[i]]++;
    }
    for (int i = 1; i <= N; i++)
    {
        if (_indegree[i] != 1){
            int idol = outlist[i];
            while (_indegree[idol] <= 1 && idol != i){
                //cout<<idol<<" "<<outlist[idol]<<endl;
                newnode[i][0]++;
                idol = outlist[idol];
            }
            newnode[i][1] = idol;
        }
    }
    int Qcount;
    cin>>Qcount;
    int answer[Qcount];
    int indegree_new[N+1];
    for (int i = 0; i <= N; i++) indegree_new[i] = 0;
    list<int> deadidol;

    for (int i = 0; i < Qcount; i++)
    {
        //int indegree[N+1];
        //copy(_indegree, _indegree+N+1, indegree);
        
        int loser; //原本就不是偶像還被刪掉的人
        cin>>loser;
        int ans = 0;
        int empty = 0;  //indegree變成0的idol
        for (int j = 0; j < loser; j++)
        {
            int victim;
            cin>>victim;
            ans += newnode[victim][0];
            int idol = newnode[victim][1];
            while (indegree_new[idol] < _indegree[idol])
            {
                indegree_new[idol]++;
                deadidol.push_back(idol);
                if (indegree_new[idol] < _indegree[idol]) break;
                if (indegree_new[idol] == _indegree[idol]) empty += newnode[idol][0];
                idol = newnode[idol][1];
            }
        }
        ans += empty;
        answer[i] = ans;
        int n = deadidol.size();
        for (int j = 0; j < n; j++)
        {
            indegree_new[deadidol.front()] = 0;
            deadidol.pop_front();
        }
        
        
    }
    
    for (int i = 0; i < Qcount; i++)
    {
        cout<<answer[i]<<"\n";
    }

    return 0;
}