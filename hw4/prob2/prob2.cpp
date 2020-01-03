#include <iostream>
#include <stack>
#include <vector>
#include <time.h>
#include <limits.h>
#include <random>

using namespace std;
struct node{
    int to;
    node(int t):to(t){}
};
class Graph
{
private:
	int num_vertex;
	vector<vector<node> > AdjList;
	vector<int> toposort;
    int K;
    vector<vector<int> > table;
public:
	Graph():num_vertex(0){};           // default constructor
	Graph(int N):num_vertex(N){        // constructor with input: number of vertex
		AdjList.resize(num_vertex);
        table.resize(num_vertex);
        srand(12345);
        K = 500;
        for (int i = 0; i < num_vertex; i++){
            table[i].resize(K);
        }
        
	};
	void AddEdge(int from, int to){
		AdjList[from].push_back(node(to));
	} 

	void topologicalSortUtil(int v, vector<bool>& visited) 
	{ 
		visited[v] = true;  
		vector<node>::iterator i; 
		for (i = AdjList[v].begin(); i != AdjList[v].end(); ++i) 
			if (!visited[i->to]) 
				topologicalSortUtil(i->to, visited); 
		toposort.push_back(v); 
	} 
	
	void topologicalSort() 
	{ 
		vector<bool> visited(num_vertex);
		for (int i = 1; i < num_vertex; i++) 
			if (visited[i] == false) 
				topologicalSortUtil(i, visited);
	}
    void randgen(){
        for (int i = 0; i < num_vertex; i++){
            for (int k = 0; k < K; k++){
                table[i][k] = rand();
            }
        }
        
    }
    void MiniHash(){
        randgen();
        for (int i = 0; i < toposort.size(); i++){
            for (int j = 0; j < AdjList[toposort[i]].size(); j++){
                for (int k = 0; k < K; k++){
                    table[toposort[i]][k] = min(table[toposort[i]][k], table[AdjList[toposort[i]][j].to][k]);
                }
            }
        }
    }
    double Jaccard(int a, int b){
        double count = 0;
        for (int i = 0; i < K; i++){
            if (table[a][i] == table[b][i]){
                count++;
            }
        }
        return count/(double)K;
    }
	void show(){
		for (int i = 1; i < AdjList.size(); i++){
			cout<<i<<": ";
			for (int j = 0; j < AdjList[i].size(); j++){
				node& n = AdjList[i][j];
				cout<<n.to<<" ";
			}
			cout<<endl;
		}
	}
    void printtable(){
        for (int i = 0; i < num_vertex; i++){
            for (int j = 0; j < K; j++){
                cout<<table[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    void printtopo(){
        for (int i = 0; i < toposort.size(); i++){
            cout<<toposort[i]<<" ";
        }
        cout<<endl;
    }
};
int main()
{
    ios_base::sync_with_stdio(false); 
	cin.tie(nullptr);
    int N, Q, M;
    cin>>N>>M>>Q;
    double answer[Q];
    Graph G(N + 1);
    for (int i = 0; i < M; i++){
        int from, to;
        cin>>from>>to;
        G.AddEdge(from, to);
    }
    G.topologicalSort();
    //G.printtopo();
    G.MiniHash();
    for (int i = 0; i < Q; i++){
        int a, b;
        cin>>a>>b;
        answer[i] = G.Jaccard(a, b);
    }

    for (int i = 0; i < Q; i++){
        cout<<answer[i]<<"\n";
    }
    
    

    return 0;
}