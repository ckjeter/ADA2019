/*
2
3 3
10 10 10
1 5 2 3
2 7 1 6
2 3 3 5
1 1
10
1 6 1 3
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
	vector<int> dp;
public:
	Graph():num_vertex(0){};           // default constructor
	Graph(int N):num_vertex(N){        // constructor with input: number of vertex
		AdjList.resize(num_vertex);
		dp.resize(num_vertex);
	};
	void AddEdge(int from, int to, int dist){
		AdjList[from].push_back(node(to, dist));
	} 
	bool isCyclicUtil(int v, bool visited[], bool *recStack) 
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
		// Mark all the vertices as not visited and not part of recursion 
		// stack 
		bool *visited = new bool[num_vertex]; 
		bool *recStack = new bool[num_vertex]; 
		for(int i = 0; i < num_vertex; i++) 
		{ 
			visited[i] = false; 
			recStack[i] = false; 
		} 
	
		// Call the recursive helper function to detect cycle in different 
		// DFS trees 
		for(int i = 0; i < num_vertex; i++) 
			if (isCyclicUtil(i, visited, recStack)) 
				return true; 
	
		return false; 
	}

	void topologicalSortUtil(int v, bool visited[]) 
	{ 
		// Mark the current node as visited. 
		visited[v] = true; 
	
		// Recur for all the vertices adjacent to this vertex 
		vector<node>::iterator i; 
		for (i = AdjList[v].begin(); i != AdjList[v].end(); ++i) 
			if (!visited[i->to]) 
				topologicalSortUtil(i->to, visited); 
		// Push current vertex to stack which stores result 
		toposort.push(v); 
	} 
	
	// The function to do Topological Sort. It uses recursive 
	// topologicalSortUtil() 
	void topologicalSort() 
	{ 
		// Mark all the vertices as not visited 
		bool* visited = new bool[num_vertex]; 
		for (int i = 1; i < num_vertex; i++) 
			visited[i] = false; 
	
		for (int i = 1; i < num_vertex; i++) 
			if (visited[i] == false) 
				topologicalSortUtil(i, visited);
	} 
	int finddiameter()
	{	
		while (toposort.empty() == false) {  
			int now = toposort.top();
			vector<node>::iterator it;
			for (it = AdjList[now].begin(); it != AdjList[now].end(); it++){
				dp[it->to] = max(dp[it->to], dp[now] + it->dist);
			}
			toposort.pop();
		}
		int answer = 0;
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

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
	int problemcount;
	cin>>problemcount;
	vector<int> answer(problemcount);
	for (int p = 0; p < problemcount; p++){
		int N,M;
		cin>>N>>M;
		
		vector<unordered_map<int, int> > nodemap(N+1); //<local index, global index>
		unordered_map<int, int>::iterator it;
		int jumppoint[M][4];
		int nodecount = 0;
	
		//維護每首歌的頭尾點
		int longestsong = 0;
		for (int i = 1; i <= N; i++){
			int length;
			cin>>length;
			longestsong = max(longestsong, length);
			nodemap[i].insert(make_pair(1, ++nodecount));
			nodemap[i].insert(make_pair(length, ++nodecount));
		}
		if (M == 0){
			answer[p] = longestsong;
			continue;
		}
		
		//維護每首歌的中繼點
		for (int i = 0; i < M; i++){
			int from_song, from_time, to_song, to_time;
			cin>>from_song>>from_time>>to_song>>to_time;
			
			if ((from_song == to_song) && (from_time >= to_time)){	//同一首歌自己有cycle
				answer[p] = -1;
				break;
			}
			
			if ((from_song == to_song) && (from_time < to_time)){	//同一首歌自己jump->忽略
				continue;
			}
			if (nodemap[from_song].find(from_time) == nodemap[from_song].end()) {
				nodemap[from_song].insert(make_pair(from_time, ++nodecount));
			}
			if (nodemap[to_song].find(to_time) == nodemap[to_song].end()) {
				nodemap[to_song].insert(make_pair(to_time, ++nodecount));
			}
			jumppoint[i][0] = from_song;
			jumppoint[i][1] = from_time;
			jumppoint[i][2] = to_song;
			jumppoint[i][3] = to_time;
		}
		if (answer[p] == -1) continue;
		Graph g(nodecount+1);
		
		//維護除了jump以外的邊
		for (int i = 1; i <= N; i++){
			vector<int> keys(nodemap[i].size());
			it = nodemap[i].begin();
			for (int j = 0; j < keys.size(); j++){
				keys[j] = it->first;
				it++;
			}
			sort(keys.begin(), keys.end());
			for (int j = 0; j < keys.size()-1; j++){
				g.AddEdge(nodemap[i][keys[j]], nodemap[i][keys[j+1]], keys[j+1] - keys[j]);
			}
		}

		//維護jump的邊
		for (int i = 0; i < M; i++){
			int from_index, to_index;
			from_index = nodemap[jumppoint[i][0]][jumppoint[i][1]];
			to_index = nodemap[jumppoint[i][2]][jumppoint[i][3]];
			g.AddEdge(from_index, to_index, 1);
		}

		//計算
		if (g.isCyclic()){
			answer[p] = -1;
			continue;
		}
		g.topologicalSort();
		answer[p] = g.finddiameter() + 1;
	}
	
	for (int i = 0; i < problemcount; i++)
	{
		if (answer[i] == -1) cout<<"LoveLive!"<<"\n";
		else cout<<answer[i]<<"\n";
	}
	
    return 0;
}
