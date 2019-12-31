#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <set>
#include <math.h>
#include <cryptominisat5/cryptominisat.h>

using namespace std;
using namespace CMSat;

int n, r, c;
int h[132][132] = {0};
int v[132][132] = {0};
int cell[132][132];
bool done = 0;
//set<int> edges;
vector<vector<int> > clause;

namespace sat {
    CMSat::SATSolver solver;
    std::vector<CMSat::Lit> lit_buf;

    void Init(int n) { solver.new_vars(n + 1); }

    void AddClause(std::vector<int> v) {
        lit_buf.clear();
        lit_buf.reserve(v.size());
        for (int x : v) lit_buf.emplace_back(abs(x), x < 0);
        solver.add_clause(lit_buf);
    }

    bool Solve() { return solver.solve() == CMSat::l_True; }

    int GetResult(int id) {
        auto r = solver.get_model()[id];
        return r == CMSat::l_True ? 1 : r == CMSat::l_False ? -1 : 0;
    }

}  // namespace sat

using namespace sat;

void edgeinit(int &edgecount){
    //horizontal edge
    for (int i = 1; i <= r + 1; i++)
        for (int j = 1; j <= c; j++){
            h[i][j] = ++edgecount;
        }
    
    //vertical edge
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c + 1; j++){
            v[i][j] = ++edgecount;
        }
}
void printedge(){
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            cout<<h[i][j]<<" ";
        }
        cout<<endl;
        for (int j = 1; j <= c + 1; j++){
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
    for (int j = 1; j <= c; j++){
        cout<<h[r + 1][j]<<" ";
    }
	cout<<endl;

}
void inputcells(){
    //input cells
    for (int i = 1; i <= r; i++){
        string row;
        cin>>row;
        for (int j = 1; j <= c; j++){
            if (row[j-1] != '.'){
                cell[i][j] = int(row[j-1]) - 48;
            }
            else cell[i][j] = -1;
        }
    }
}
void printcells(){
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            cout<<cell[i][j]<<" ";
        }
        cout<<endl;
    }
}
void printtable(){
	cout<<"-----------------table-----------------\n";
	for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            cout<<"+";
			if (GetResult(h[i][j]) == -1){
				cout<<" ";
			}
			else cout<<"-";
        }
		cout<<"+\n";
		
        for (int j = 1; j <= c; j++){
            if (GetResult(v[i][j]) == -1){
				cout<<" ";
			}
			else cout<<"|";
			
			if (cell[i][j] == -1){
				cout<<".";
			}
			else cout<<cell[i][j];
			
        }
		if (GetResult(v[i][c+1]) == -1){
			cout<<" \n";
		}
		else cout<<"|\n";
		
    }
	for (int j = 1; j <= c; j++){
		cout<<"+";
		if (GetResult(h[r+1][j]) == -1){
			cout<<" ";
		}
		else cout<<"-";
	}
	cout<<"+\n";
}
void exactlycell(int e1, int e2, int e3, int e4, int val){
	if (val == -1) return;
	if (val == 0){
		vector<int> c[4];
		c[0] = {e1 * -1};
		c[1] = {e2 * -1};
		c[2] = {e3 * -1};
		c[3] = {e4 * -1};
		for (int k = 0; k < 4; k++){
			AddClause(c[k]);
		}
	}
	if (val == 1 || val == 3){
		vector<int> c[7];
		if (val == 3){
			e1 *= -1;
			e2 *= -1;
			e3 *= -1;
			e4 *= -1;
		}
		c[0] = {e1, e2, e3, e4};
		c[1] = {e1 * -1, e2 * -1};
		c[2] = {e1 * -1, e3 * -1};
		c[3] = {e1 * -1, e4 * -1};
		c[4] = {e2 * -1, e3 * -1};
		c[5] = {e2 * -1, e4 * -1};
		c[6] = {e3 * -1, e4 * -1};
		for (int k = 0; k < 7; k++){
			AddClause(c[k]);
		}
	}
	if (val == 2){
		vector<int> c[8];
		c[0] = {e2, e3, e4};
		c[1] = {e1, e3, e4};
		c[2] = {e1, e2, e4};
		c[3] = {e1, e2, e3};
		c[4] = {e2 * -1, e3 * -1, e4 * -1};
		c[5] = {e1 * -1, e3 * -1, e4 * -1};
		c[6] = {e1 * -1, e2 * -1, e4 * -1};
		c[7] = {e1 * -1, e2 * -1, e3 * -1};
		for (int k = 0; k < 8; k++){
			AddClause(c[k]);
		}
	}
	
}
void exactlycorner_2(int e1, int e2){
	vector<int> c[2];
	c[0] = {e1 * -1, e2};
	c[1] = {e1, e2 * -1};
	for (int k = 0; k < 2; k++){
		AddClause(c[k]);
	}
}
void exactlycorner_3(int e1, int e2, int e3){
	vector<int> c[4];
	c[0] = {e1 * -1, e2, e3};
	c[1] = {e1, e2 * -1, e3};
	c[2] = {e1, e2, e3 * -1};
	c[3] = {e1 * -1, e2 * -1, e3 * -1};
	for (int k = 0; k < 4; k++){
		AddClause(c[k]);
	}
}
void exactlycorner_4(int e1, int e2, int e3, int e4){
	vector<int> c[8];
	c[0] = {e1 * -1, e2, e3, e4};
	c[1] = {e1, e2 * -1, e3, e4};
	c[2] = {e1, e2, e3 * -1, e4};
	c[3] = {e1, e2, e3, e4 * -1};
	c[4] = {e1 * -1, e2 * -1, e3 * -1};
	c[5] = {e1 * -1, e2 * -1, e4 * -1};
	c[6] = {e1 * -1, e3 * -1, e4 * -1};
	c[7] = {e2 * -1, e3 * -1, e4 * -1};
	for (int k = 0; k < 8; k++){
		AddClause(c[k]);
	}
}
int convert(int i, int j, bool v_or_h){
	if (v_or_h == 0) return h[i][j];
	else return v[i][j];
}
void banloop(){
	vector<int> edges;
	for (int i = 1; i <= n; i++){
		if (GetResult(i) == 1) edges.push_back(i);
	}
	bool visited[n + 1] = {false};
	for (int i = 0; i < edges.size(); i++){
		vector<int> loop;
		int e = edges[i];
		if (!visited[e]) loop.push_back(-1 * e);
		while (!visited[e]) {
			visited[e] = 1;
			vector<int> neighbor;
			int i1, j1, i2, j2;// ⅹ(쨁),쩵(짾)
			
			if (e <= c * (r + 1)){ //horizon
				i1 = (e - 1)/c + 1;
				j1 = (e - 1) % c + 1;
				i2 = i1;
				j2 = j1 + 1;
				//ⅹ헕
				if (i1 <= r) neighbor.push_back(v[i1][j1]); //짾
				if (j1 % (c + 1) >= 2) neighbor.push_back(h[i1][j1 - 1]); //ⅹ
				if (i1 > 1) neighbor.push_back(v[i1 - 1][j1]); //쨁
				//쩵헕
				if (i2 <= r) neighbor.push_back(v[i2][j2]); //짾
				if (j2 <= c) neighbor.push_back(h[i2][j2]); //쩵
				if (i2 > 1) neighbor.push_back(v[i2 - 1][j2]); //쨁
			}
			else {
				i1 = (e - (c * (r + 1)) - 1) / (c + 1) + 1;
				j1 = (e - (c * (r + 1)) - 1) % (c + 1) + 1;
				i2 = i1 + 1;
				j2 = j1;
				//쨁헕
				if (j1 <= c) neighbor.push_back(h[i1][j1]);//쩵
				if ((j1 - 1) % (c + 1) >= 1) neighbor.push_back(h[i1][j1 - 1]); //ⅹ
				if (i1 > 1) neighbor.push_back(v[i1 - 1][j1]); //쨁

				//짾헕
				if (i2 <= r) neighbor.push_back(v[i2][j2]); //짾
				if (j2 <= c) neighbor.push_back(h[i2][j2]);//쩵
				if ((j2 - 1) % (c + 1) >= 1) neighbor.push_back(h[i2][j2 - 1]); //ⅹ				
			}
			for (int j = 0; j < neighbor.size(); j++){
				if (GetResult(neighbor[j]) == 1 && !visited[neighbor[j]]){
					loop.push_back(-1 * neighbor[j]);
					e = neighbor[j];
					break;
				}
			}
		}
		if (loop.size() == edges.size()) done = 1;
		if (loop.size() > 0) AddClause(loop);
	}
}

int main()
{
    ios_base::sync_with_stdio(false); 
	cin.tie(nullptr);
	bool cansolve; 
    cin>>r>>c;
    n = 2*r*c + r + c;
    int edgecount = 0;
    edgeinit(edgecount);
    inputcells();
	Init(n);

	//cell rule
	for (int i = 1; i <= r; i++){
		for (int j = 1; j <= c; j++){
			exactlycell(h[i][j], h[i + 1][j], v[i][j], v[i][j + 1], cell[i][j]);
		}
	}

	//corner rule
	exactlycorner_2(h[1][1], v[1][1]);
	exactlycorner_2(h[1][c], v[1][c+1]);
	exactlycorner_2(h[r+1][1], v[r][1]);
	exactlycorner_2(h[r+1][c], v[r][c+1]);
	for (int i = 2; i <= c; i++){
		exactlycorner_3(h[1][i - 1], h[1][i], v[1][i]);
		exactlycorner_3(h[r + 1][i - 1], h[r + 1][i], v[r][i]);
	}
	for (int i = 2; i <= r; i++){
		exactlycorner_3(v[i - 1][1], v[i][1], h[i][1]);
		exactlycorner_3(v[i - 1][c + 1], v[i][c + 1], h[i][c]);
	}
	for (int i = 2; i <= r; i++){
		for (int j = 2; j <= c; j++){
			exactlycorner_4(h[i][j], v[i][j], h[i][j - 1], v[i - 1][j]);
		}
	}
	
	//checkloop
	while (!done){
		Solve();
		banloop();
	}
	
	
	//printtable();
	
	for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
			if (GetResult(h[i][j]) == -1) cout<<0;
			else cout<<1;
        }
        for (int j = 1; j <= c + 1; j++){
            if (GetResult(v[i][j]) == -1) cout<<0;
			else cout<<1;
        }
    }
    for (int j = 1; j <= c; j++){
        if (GetResult(h[r + 1][j]) == -1) cout<<0;
		else cout<<1;
    }
	cout<<"\n";
	
    

    return 0;
}
