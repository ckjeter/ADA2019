/*
5 5
0 4
0 1 1 3
0 2 2 2
1 3 1 4
2 3 2 2
3 4 2 5

5 5
0 4
0 1 1 3
1 2 2 1
2 3 1 2
3 4 1 3
0 4 1 4
*/
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <tuple>
#include <utility>
#include <stdio.h>
#include <climits>

using namespace std;

struct HeapNode
{
    int element;
	long long key;
    HeapNode():element(0),key(0){};
    HeapNode(int node, int key):element(node), key(key){};
};

class BinaryHeap
{
public:
    vector<HeapNode> heap;        // 存放HeapNode資料的矩陣
    void swap(struct HeapNode &p1, struct HeapNode &p2)
    {
    	struct HeapNode temp = p1;
	    p1 = p2;
	    p2 = temp;
    }
    int FindPosition(int node)
    {
	    int idx = 0;
	    for (int i = 1; i < heap.size(); i++) 
	    {
	        if (heap[i].element == node) 
	        {
	            idx = i;
	        }
	    }
	    return idx;
    }
    BinaryHeap()				// default constructor會把heap[0]給預留 
    {               
        heap.resize(1);         // 之後若新增HeapNode, 會從heap[1]開始新增
    }
    BinaryHeap(int n)
    {
        heap.resize(n + 1);
    }
    bool IsHeapEmpty(){return (heap.size()<1);};

    // Min-Priority Queue
    void Adjust(int node, int length)
    {
	    int left = 2*node,          // 取得left child
	        right = 2*node + 1,     // 取得right child
	        smallest;               // smallest用來記錄包含root與child, 三者之中Key最小的node

	    if (left <= length && heap[left].key < heap[node].key)
	        smallest = left;
	    else
	        smallest = node;

	    if (right <= length && heap[right].key < heap[smallest].key)
	        smallest = right;

	    if (smallest != node) {                 // 如果目前node的Key不是三者中的最小
	        swap(heap[smallest], heap[node]);   // 就調換node與三者中Key最小的node之位置
	        Adjust(smallest, length);       // 調整新的subtree成Min Heap
    	}
    }

    void BuildMinHeap(vector<long long>& array)
    {
	    // 將array[]的資料放進 heap之矩陣中, 並預留 heap[0] 不做使用
	    for (int i = 0; i < array.size(); i++) 
	    {     
	        heap[i + 1].element = i;                 // 把array[]的idx視為element
	        heap[i + 1].key = array[i];              // 把array[]的數值視為key
	    }
	    for (int i = (int)heap.size()/2; i >= 1 ; i--) 
	    {
	        Adjust(i, (int)heap.size()-1);     // length要減一, 因為heap從從1開始存放資料
	    }
    }
    void insert(int node, long long newKey)
    {
    	heap.push_back(HeapNode(node,newKey));    	// 在heap[]尾巴新增一個node
    	int index = heap.size() - 1;
	    while (index > 1 && heap[index / 2].key > heap[index].key) 
	    {
	        swap(heap[index], heap[index / 2]);
	        index = index / 2;
	    }
    }
    int Minimum()                // 回傳vertex的位置index
    {
    	return heap[1].element;
    }
    int ExtractMin()          // 回傳並刪除root(最小值)
    {

	    if (IsHeapEmpty()) 
	    {
	    	cout<<"extract error"<<endl;
	        exit(-1);
	    }
	    int min = heap[1].element;    // 此時heap的第一個node具有最小key值
	                                  // 便以min記錄其element, 最後回傳min
	    // delete the first element/vertex
	    heap[1] = heap[heap.size()-1];            // 把最後一個element放到第一個位置,
	    heap.erase(heap.begin() + heap.size()-1);   // 再刪除最後一個element
	    Adjust(1, (int)heap.size());          // 目前, heap[1]具有最大Key, 需要進行調整
	    return min;       // 回傳heap中具有最小key的element
    }
};


class Graph
{
public:
	vector<vector<tuple<int, int, int> > > adlist;
    multimap<int, pair<int, int> > edgelist;
	multimap<int, pair<int, int> >::iterator it;
    vector<int> disjoint_set;
	vector<int> predecessor;
	vector<long long> distance;
	int V;
	int E;
    int L;
	Graph(int _V, int _E)
	{
		V = _V;
		E = _E;
        L = 0;
		adlist.resize(V);
		predecessor.resize(V);
		distance.resize(V);
		for (int i = 0; i < E; ++i)
		{
			int temp_v1, temp_v2, temp_e, temp_d; //v1走到v2
			scanf("%d %d %d %d", &temp_v1, &temp_v2, &temp_e, &temp_d);
			adlist[temp_v1].push_back(make_tuple(temp_v2, temp_e, temp_d));
            adlist[temp_v2].push_back(make_tuple(temp_v1, temp_e, temp_d));
            edgelist.insert(make_pair(temp_d, make_pair(temp_v1, temp_v2)));
		}
        for (int i = 0; i <= V; ++i)
        {
            disjoint_set.push_back(i); //0不使用
        }
        kruskal();
	}
	void kruskal()
	{
		int count = 0;
		for (it = edgelist.begin(); it != edgelist.end(); ++it)
		{
			if (find((it->second).first) != find((it->second).second))
			{
				count++;
				L = max(it->first, L);
				set_union((it->second).first, (it->second).second);
			}
			if (count == V - 1)
			{
				break;
			}
		}
	}
    void set_union(int x, int y)
	{
		disjoint_set[find(y)] = find(x);
	}
	int find(int x)
	{
		if (disjoint_set[x] == x)
		{
			return x;
		}
		else
		{
			return find(disjoint_set[x]);
		}
	}
	void Dijkstra(int s)
	{
		initialize(s);
		BinaryHeap priorityqueue(V);
   		priorityqueue.BuildMinHeap(distance);

		while(!priorityqueue.IsHeapEmpty())
		{
			//cout<<"----------"<<endl;
		    //priorityqueue.printheap();
		    int u = priorityqueue.ExtractMin();
		    //list<tuple<int, int, int> >::iterator itr;
			for (int i = 0; i < adlist[u].size(); i++)
			{
				relax(u, get<0>(adlist[u][i]), get<1>(adlist[u][i]), get<2>(adlist[u][i]));
				if (distance[get<0>(adlist[u][i])] >= distance[u] + get<1>(adlist[u][i]) && get<2>(adlist[u][i]) <= L)
				{
					distance[get<0>(adlist[u][i])] = distance[u] + get<1>(adlist[u][i]);
					predecessor[get<0>(adlist[u][i])] = u;
					priorityqueue.insert(get<0>(adlist[u][i]), distance[get<0>(adlist[u][i])]);
				}
			}
		}
		//printarray();
	}

	void initialize(int s)
	{
		for (int i = 0; i < V; ++i)
		{
			distance[i] = LLONG_MAX;
			predecessor[i] = -1;
		}
		distance[s] = 0;
	}

	void relax(int u, int v, int w, int d)
	{
		if (distance[v] > distance[u] + w && d <= L)
		{
			distance[v] = distance[u] + w;
			predecessor[v] = u;
		}
	}

	void printarray()
	{
		for (int i = 0; i < distance.size(); ++i)
		{
			cout<<distance[i]<<" ";
		}
		cout<<endl;
	}
};

int main()
{
    int V, E;
    int s,t;
	scanf("%d %d", &V, &E);
	scanf("%d %d", &s, &t);
    Graph G(V, E);
    G.Dijkstra(s);
    /*
    G.distance : s到所有點的最短距離
    */
    long long minpath = G.distance[t];
	printf("%lld %d\n", minpath, G.L);
	return 0;
}

/*

*/
