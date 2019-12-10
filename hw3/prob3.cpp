/*
6
3 0
10 10 20
3 1
10 15 20
1 6 1 10
10 4
3 4 5 6 7 8 9 100 22 55
6 2 1 2
8 99 10 1
2 1 8 10
10 20 9 15
3 3
10 10 10
1 5 2 3
2 7 1 6
2 3 3 5
1 1
10
1 6 1 3
2 2
10 10
1 3 2 6
2 7 1 2
*/
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <stack>
using namespace std;

struct node
{
    int to,dist;
    node(int t,int d):to(t),dist(d){}
};
class Graph
{
private:
	int num_vertex;
	vector<vector<node> > AdjList;
	stack<int> toposort;
	vector<long long> dp;
public:
	Graph():num_vertex(0){};           // default constructor
	Graph(int N):num_vertex(N){        // constructor with input: number of vertex
		AdjList.resize(num_vertex);
		dp.resize(num_vertex);
	};
	void AddEdge(int from, int to, int dist){
		AdjList[from].push_back(node(to, dist));
	} 
	bool isCyclicUtil(int v, vector<bool>& visited, vector<bool>& recStack) 
	{ 
		if(visited[v] == false) 
		{ 
			// Mark the current node as visited and part of recursion stack 
			visited[v] = true; 
			recStack[v] = true; 
	
			// Recur for all the vertices adjacent to this vertex 
			vector<node>::iterator i; 
			for(i = AdjList[v].begin(); i != AdjList[v].end(); ++i) 
			{ 
				if ( !visited[i->to] && isCyclicUtil(i->to, visited, recStack) ) 
					return true; 
				else if (recStack[i->to]) 
					return true; 
			} 
	
		} 
		recStack[v] = false;  // remove the vertex from recursion stack 
		return false; 
	} 
	bool isCyclic() 
	{ 
		vector<bool> visited(num_vertex);
		vector<bool> recStack(num_vertex);
		for(int i = 1; i < num_vertex; i++) 
			if (isCyclicUtil(i, visited, recStack)) 
				return true; 
	
		return false; 
	}

	void topologicalSortUtil(int v, vector<bool>& visited) 
	{ 
		visited[v] = true;  
		vector<node>::iterator i; 
		for (i = AdjList[v].begin(); i != AdjList[v].end(); ++i) 
			if (!visited[i->to]) 
				topologicalSortUtil(i->to, visited); 
		toposort.push(v); 
	} 
	
	void topologicalSort() 
	{ 
		vector<bool> visited(num_vertex);
		for (int i = 1; i < num_vertex; i++) 
			if (visited[i] == false) 
				topologicalSortUtil(i, visited);
	} 
	long long finddiameter()
	{	
		while (toposort.empty() == false) {  
			int now = toposort.top();
			vector<node>::iterator it;
			for (it = AdjList[now].begin(); it != AdjList[now].end(); it++){
				dp[it->to] = max(dp[it->to], dp[now] + it->dist);
			}
			toposort.pop();
		}
		long long answer = 0;
		for (int i = 1; i < dp.size(); i++){
			answer = max(answer, dp[i]);
		}
		return answer;
	}

	void show(){
		for (int i = 1; i < AdjList.size(); i++){
			cout<<i<<": ";
			for (int j = 0; j < AdjList[i].size(); j++){
				node& n = AdjList[i][j];
				cout<<"( "<<n.to<<", "<<n.dist<<" )  ";
			}
			cout<<endl;
		}
	}
};

int bsearch(int left, int right, int value, vector<int>& v)
{
	while(left < right) {
	   int mid = left + (right - left) / 2;
	   if (value > v[mid]) left = mid + 1;
	   else if (value < v[mid]) right = mid - 1;
       else return mid;
	}
	return (value > v[left]) ? (left + 1) : left;
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
	int testcase;
	cin>>testcase;
	long long answer[11] = {0};
	for (int p = 0; p < testcase; p++){
		int N,M;
		cin>>N>>M;

		vector<int> nodemap[N+1][2];
		int nodecount = 0;

		//維護每首歌的頭尾點
		int longestsong = 0;
		for (int i = 1; i <= N; i++){
			int length;
			cin>>length;
			longestsong = max(longestsong, length);
			nodemap[i][0].push_back(1);
			nodemap[i][1].push_back(++nodecount);
			nodemap[i][0].push_back(length);
			nodemap[i][1].push_back(++nodecount);
		}
		
		if (M == 0){
			answer[p] = longestsong;
			continue;
		}
		
		int jumppoint[M][2];

		//維護每首歌的中繼點
		for (int i = 0; i < M; i++){
			int s1, t1, s2, t2;
			cin>>s1>>t1>>s2>>t2;
			
			if ((s1 == s2) && (t1 >= t2)){	//同一首歌自己有cycle
				answer[p] = -1;
			}
			

			int index = bsearch(0, nodemap[s1][0].size()-1, t1, nodemap[s1][0]);
			if (index < nodemap[s1][0].size()){
				if (nodemap[s1][0][index] != t1){
					nodemap[s1][0].insert(nodemap[s1][0].begin()+index, t1);
					nodemap[s1][1].insert(nodemap[s1][1].begin()+index, ++nodecount);	
				}
			}
			else {
				nodemap[s1][0].insert(nodemap[s1][0].begin()+index, t1);
				nodemap[s1][1].insert(nodemap[s1][1].begin()+index, ++nodecount);
			}
			jumppoint[i][0] = nodemap[s1][1][index];

			index = bsearch(0, nodemap[s2][0].size()-1, t2, nodemap[s2][0]);
			if (index < nodemap[s2][0].size()){
				if (nodemap[s2][0][index] != t2){
					nodemap[s2][0].insert(nodemap[s2][0].begin()+index, t2);
					nodemap[s2][1].insert(nodemap[s2][1].begin()+index, ++nodecount);	
				}
			}
			else {
				nodemap[s2][0].insert(nodemap[s2][0].begin()+index, t2);
				nodemap[s2][1].insert(nodemap[s2][1].begin()+index, ++nodecount);
			}

			jumppoint[i][1] = nodemap[s2][1][index];
		}
		if (answer[p] == -1) continue;
		
		Graph g(nodecount+1);
		
		//維護除了jump以外的邊
		for (int i = 1; i <= N; i++){
			for (int j = 0; j < nodemap[i][0].size()-1; j++){
				g.AddEdge(nodemap[i][1][j], nodemap[i][1][j+1], nodemap[i][0][j+1] - nodemap[i][0][j]);
			}
		}

		//維護jump的邊
		for (int i = 0; i < M; i++){
			g.AddEdge(jumppoint[i][0], jumppoint[i][1], 1);
		}
		
		//g.show();
		//計算
		if (g.isCyclic()){
			answer[p] = -1;
		}
		else {
			g.topologicalSort();
			answer[p] = g.finddiameter() + 1;
		}

	}
	
	for (int i = 0; i < testcase; i++)
	{
		if (answer[i] == -1) cout<<"LoveLive!"<<"\n";
		else cout<<answer[i]<<"\n";
	}
	
    return 0;
}
