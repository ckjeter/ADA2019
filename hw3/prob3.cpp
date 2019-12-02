#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class Graph{
private:
	int num_vertex;
	vector<list<int> > AdjList;
	vector<int> color;			// 0:白色, 1:灰色, 2:黑色
	vector<int> predecessor;	// -1:沒有predecessor, 表示為起點vertex
	vector<int> distance;		// 0:起點, 無限大:從起點走不到的vertex

public:
	Graph():num_vertex(0){};           // default constructor
	Graph(int N):num_vertex(N){        // constructor with input: number of vertex
		// initialize Adjacency List
		AdjList.resize(num_vertex);
		color.resize(num_vertex);
		predecessor.resize(num_vertex);
		distance.resize(num_vertex);
	};
	void AddEdgeList(int from, int to){
		AdjList[from].push_back(to);
	}
	void BFS(int Start){
		for (int i = 0; i < num_vertex; i++) {  // 初始化
			color[i] = 0;                       // 0:白色;
			predecessor[i] = -1;                // -1表示沒有predecessor
			distance[i] = num_vertex+1;         // num_vertex個vertex,
		}                                       // 最長距離 distance = num_vertex -1條edge

		queue<int> q;
		int i = Start;

		for (int j = 0; j < num_vertex; j++) {  // j從0數到num_vertex-1, 因此j會走過graph中所有vertex
			if (color[i] == 0) {                // 第一次i會是起點vertex, 如圖二(c)
				color[i] = 1;                   // 1:灰色
				distance[i] = 0;                // 每一個connected component的起點之距離設成0
				predecessor[i] = -1;            // 每一個connected component的起點沒有predecessor
				q.push(i);
				while (!q.empty()) {
					int u = q.front();                  // u 為新的搜尋起點
					for (list<int>::iterator itr = AdjList[u].begin();        // for loop 太長
						itr != AdjList[u].end(); itr++) {                         // 分成兩段
						if (color[*itr] == 0) {                // 若被「找到」的vertex是白色
							color[*itr] = 1;                   // 塗成灰色, 表示已經被「找到」
							distance[*itr] = distance[u] + 1;  // 距離是predecessor之距離加一
							predecessor[*itr] = u;             // 更新被「找到」的vertex的predecessor
							q.push(*itr);                      // 把vertex推進queue
						}
					}
					q.pop();        // 把u移出queue
					color[u] = 2;   // 並且把u塗成黑色
				}
			}
			// 若一次回圈沒有把所有vertex走過, 表示graph有多個connected component
			// 就把i另成j, 繼續檢查graph中的其他vertex是否仍是白色, 若是, 重複while loop
			//i = j;
		}
	}
};

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
	cout<<"ansdkanskjnajknd"<<endl;
	/*
    int testcase;
    cin>>testcase;
    int answer[testcase];
    for (int z = 0; z < testcase; z++){
		int N,M;


    }
    for (int i = 0; i < testcase; i++){
        if (answer[i] < 0)  cout<<"LoveLive!"<<"\n";
        else cout<<answer[i]<<"\n";
    }
	*/
    return 0;
}
