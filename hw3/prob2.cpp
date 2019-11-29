/*
5 5
4 0
0 1 1 3
0 2 2 2
1 3 1 4
2 3 2 2
3 4 2 5

5 5
4 0
0 1 1 3
1 2 2 1
2 3 1 2
3 4 1 3
0 4 1 4
*/
#include <vector>
#include <queue>
#include <iostream>
#include <cstring>
#include <climits>
using namespace std;
#define inf 1e18
#define maxn 300050

struct Edge
{
    int from,to;
    long long dist, dang;
    Edge(int f,int t,long long d, long long l):from(f),to(t),dist(d),dang(l){}
};

struct HeapNode
{
    long long d;
    int u;
    HeapNode(long long dd,int uu):d(dd),u(uu){}
    bool operator<(const HeapNode& rhs)const
    {
        return d > rhs.d;
    }
};

struct Dijkstra
{
    int n,m;
    vector<Edge> edges;
    vector<int> g[maxn];
    bool done[maxn];
    long long d[maxn];
    int p[maxn];
	int L;

    void init(int n)
    {
        this->n = n;
        for (int i = 0 ; i < n ; ++i) g[i].clear();
        edges.clear();
    }

    void add(int from,int to,long long dist, int dang)
    {
        edges.push_back(Edge(from,to,dist, dang));
        m = edges.size();
        g[from].push_back(m-1);
        edges.push_back(Edge(to,from,dist, dang));
        m = edges.size();
        g[to].push_back(m-1);		
    }
	
	void dij_L(int s, int t)
	{
		priority_queue<HeapNode> que;
		for (int i = 0 ; i < n ; ++i) d[i] = inf;
		d[s] = 0;
        memset(done,0,sizeof(done));
        que.push(HeapNode(0,s));

		while(!que.empty())
        {
            HeapNode x = que.top();
            que.pop();
            int u = x.u;
            if (done[u]) continue;
            done[u] = true;
            for (int i = 0 ; i < g[u].size();++i)
            {
                Edge& e = edges[g[u][i]];
				//d[e.to] = min(max(d[u], e.dang), d[e.to]);
                if(d[e.to] > max(d[u], e.dang))
                {
                    d[e.to] = max(d[u], e.dang);
                    que.push(HeapNode(d[e.to] , e.to));
                }
            }
        }
		L = d[t];
	}
	
    void dijkstra(int s)
    {
        priority_queue<HeapNode> que;
        //initialize
        for (int i = 0 ; i < n ; ++i) d[i] = inf;
        d[s] = 0;
        memset(done,0,sizeof(done));
        que.push(HeapNode(0,s));

        while(!que.empty())
        {
            HeapNode x = que.top();
            que.pop();
            int u = x.u;
            if (done[u]) continue;
            done[u] = true;
            for (int i = 0 ; i < g[u].size();++i)
            {
                Edge& e = edges[g[u][i]];
                if(d[e.to] > d[u] + e.dist && e.dang <= L)
                {
                    d[e.to] = d[u] + e.dist;
                    p[e.to] = g[u][i];
                    que.push(HeapNode(d[e.to] , e.to));
                }
				
                else if(d[e.to] == d[u] + e.dist && e.dist < edges[p[e.to]].dist)
                {
                    p[e.to] = g[u][i];
                }
				
            }
        }
    }
};

Dijkstra dij;
int N, M;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
	cin>>N>>M;
	int s,t;
	cin>>s>>t;
	dij.init(N);
	for (int i = 1 ; i <= M ; i++)
	{
		int u,v;
		long long d;
		long long l;
		cin>>u>>v>>d>>l;
		dij.add(u , v , d, l);
	}
	dij.dij_L(s, t);
	dij.dijkstra(s);
	cout<<dij.d[t]<<" "<<dij.L<<"\n";

    
    return 0;
}