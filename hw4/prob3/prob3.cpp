//maximum clique 參考來源：http://insilab.org/maxclique/
#include <fstream>
#include <iostream>
#include <set>
#include <string.h>
#include <string>
#include <map>
#include <assert.h>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

class Maxclique {
	const bool* const* e;
	int pk, level;
	const float Tlimit;
	class Vertices {
		class Vertex {
			int i, d;
		public:
			void set_i(const int ii)  { i = ii; }
			int get_i() const { return i; }
			void set_degree(int dd) { d = dd; }
			int get_degree() const { return d; }
		};
		Vertex *v;
		int sz;
		static bool desc_degree(const Vertex vi, const Vertex vj) { return (vi.get_degree() > vj.get_degree()); }
	public:
		Vertices(int size) : sz(0) { v = new Vertex[size]; }
		~Vertices () {}
		void dispose() { if (v) delete [] v; }
		void sort() { std::sort(v, v+sz, desc_degree); }
		void init_colors();
		void set_degrees(Maxclique&);
		int size() const { return sz; }
		void push(const int ii) { v[sz++].set_i(ii); };
		void pop() { sz--; };
		Vertex& at(const int ii) const { return v[ii]; };
		Vertex& end() const { return v[sz - 1]; };
	};
	class ColorClass {
		int *i;
		int sz;
	public:
		ColorClass() : sz(0), i(0) {}
		ColorClass(const int sz) : sz(sz), i(0) { init(sz); }
		~ColorClass() { if (i) delete [] i;}
		void init(const int sz) { i = new int[sz]; rewind(); }
		void push(const int ii) { i[sz++] = ii; };
		void pop() { sz--; };
		void rewind() { sz = 0; };
		int size() const { return sz; }
		int& at(const int ii) const { return i[ii]; }
		ColorClass& operator=(const ColorClass& dh) {
		for (int j = 0; j < dh.sz; j++) i[j] = dh.i[j];
		sz = dh.sz;
		return *this;
		}
  	};
	Vertices V;
	ColorClass *C, QMAX, Q;
	class StepCount {
		int i1, i2;
	public:
		StepCount() : i1(0), i2(0) {}
		void set_i1(const int ii)  { i1 = ii; }
		int get_i1() const { return i1; }
		void set_i2(const int ii)  { i2 = ii; }
		int get_i2() const { return i2; }
		void inc_i1()  { i1++; }
	};
	StepCount *S;
	bool connection(const int i, const int j) const { return e[i][j]; }
	bool cut1(const int, const ColorClass&);
	void cut2(const Vertices&, Vertices&);
	void color_sort(Vertices&);
	void expand_dyn(Vertices);
	void _mcq(int*&, int&);
	void degree_sort(Vertices &R) { R.set_degrees(*this); R.sort(); }
public:
	Maxclique(const bool* const*, const int, const float=0.025);
	int steps() const { return pk; }
	void mcqdyn(int* &maxclique, int &sz) { _mcq(maxclique, sz); }
	~Maxclique() {
		if (C) delete [] C;
		if (S) delete [] S;
		V.dispose();
	};
};

Maxclique::Maxclique (const bool* const* conn, const int sz, const float tt) : pk(0), level(1), Tlimit(tt), V(sz), Q(sz), QMAX(sz) {
	for (int i=0; i < sz; i++) V.push(i);
	e = conn;
	C = new ColorClass[sz + 1];
	for (int i=0; i < sz + 1; i++) C[i].init(sz + 1);
	S = new StepCount[sz + 1];
}

void Maxclique::_mcq(int* &maxclique, int &sz) { 
	V.set_degrees(*this);
	V.sort();
	V.init_colors();
	for (int i=0; i < V.size() + 1; i++) {
		S[i].set_i1(0);
		S[i].set_i2(0);
	}
	expand_dyn(V);
	maxclique = new int[QMAX.size()]; 
	for (int i=0; i<QMAX.size(); i++) { 
		maxclique[i] = QMAX.at(i);
	}
	sz = QMAX.size();
}

void Maxclique::Vertices::init_colors() { 
	const int max_degree = v[0].get_degree();
	for (int i = 0; i < max_degree; i++)
		v[i].set_degree(i + 1);
	for (int i = max_degree; i < sz; i++)
		v[i].set_degree(max_degree + 1);
}

void Maxclique::Vertices::set_degrees(Maxclique &m) { 
	for (int i=0; i < sz; i++) {
		int d = 0;
		for (int j=0; j < sz; j++){
			if (m.connection(v[i].get_i(), v[j].get_i())) d++;
		}
		v[i].set_degree(d);
	}
}

bool Maxclique::cut1(const int pi, const ColorClass &A) {
	for (int i = 0; i < A.size(); i++)
	if (connection(pi, A.at(i)))
		return true;
	return false;
}

void Maxclique::cut2(const Vertices &A, Vertices &B) {
	for (int i = 0; i < A.size() - 1; i++) {
	if (connection(A.end().get_i(), A.at(i).get_i()))
		B.push(A.at(i).get_i());
	}
}

void Maxclique::color_sort(Vertices &R) {
	int j = 0;
	int maxno = 1;
	int min_k = QMAX.size() - Q.size() + 1;
	C[1].rewind();
	C[2].rewind();
	int k = 1;
	for (int i=0; i < R.size(); i++) {
		int pi = R.at(i).get_i();
		k = 1;
		while (cut1(pi, C[k])) k++;
		if (k > maxno) {
			maxno = k;
			C[maxno + 1].rewind();
		}
		C[k].push(pi);
		if (k < min_k) {
			R.at(j++).set_i(pi);
		}
	}
	if (j > 0) R.at(j-1).set_degree(0);
	if (min_k <= 0) min_k = 1;
	for (k = min_k; k <= maxno; k++)
		for (int i = 0; i < C[k].size(); i++) {
			R.at(j).set_i(C[k].at(i));
			R.at(j++).set_degree(k);
		}
}
void Maxclique::expand_dyn(Vertices R) {
	S[level].set_i1(S[level].get_i1() + S[level - 1].get_i1() - S[level].get_i2());
	S[level].set_i2(S[level - 1].get_i1());
	while (R.size()) {
    	if (Q.size() + R.end().get_degree() > QMAX.size()) {
    	Q.push(R.end().get_i());
    	Vertices Rp(R.size());
    	cut2(R, Rp);
    	if (Rp.size()) {
        	if ((float)S[level].get_i1()/++pk < Tlimit) {
          		degree_sort(Rp);
        	}
        	color_sort(Rp);
			S[level].inc_i1();
			level++;
			expand_dyn(Rp);
			level--;
      	}
    	else if (Q.size() > QMAX.size()) {  
			QMAX = Q;
      	}    
      	Rp.dispose();
      	Q.pop();
    }
    else {
    	return;
    }
    R.pop();
  	}
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    bool **conn;
    int N;
    cin>>N;
	conn = new bool*[N];
	for (int i = 0; i < N; i++){
		conn[i] = new bool[N];
		string row;
		cin>>row;
		for (int j = 0; j < N; j++){
			conn[i][j] = bool(row[j]-48);
		}
	}

	bool **_conn;
	int _N = 0;
	vector<int> connmap;
	for (int i = 0; i < N; i++){
		if (conn[i][i] == 1){
			_N++;
			connmap.push_back(i);
		}
	}
	_conn = new bool*[_N];
	for (int i = 0; i < _N; i++){
		_conn[i] = new bool[_N];
		for (int j = 0; j < _N; j++){
			_conn[i][j] = conn[connmap[i]][connmap[j]];
		}
	}
	//處理沒有對稱的_conn
	for (int i = 0; i < _N; i++){
		for (int j = i + 1; j < _N; j++){
			if (_conn[i][j] == 1 && _conn[j][i] == 0){
				_conn[i][j] = 0;
			}
			if (_conn[i][j] == 0 && _conn[j][i] == 1){
				_conn[j][i] = 0;
			}
		}
	}
	
	
	/*
	for (int i = 0; i < connmap.size(); i++)
	{
		cout<<connmap[i]<<" ";
	}
	cout<<endl;
	
	
	for (int i = 0; i < _N; i++)
	{
		for (int j = 0; j < _N; j++)
		{
			cout<<_conn[i][j]<<" ";
		}
		cout<<endl;
		
	}
	*/
	
    int *qmax;
    int qsize;
    Maxclique md(_conn, _N, 0.025);
    md.mcqdyn(qmax, qsize);
	/*
	for (int i = 0; i < qsize; i++)
	{
		cout<<qmax[i]<<" ";
	}
	cout<<endl;
	*/
	bool hasprint[122] = {0};
	for (int i = 0; i < qsize; i++){
		hasprint[connmap[qmax[i]] + 1] = 1;
		cout<<connmap[qmax[i]] + 1<<" ";
	}
	for (int i = 1; i <= N; i++){
		if (hasprint[i] == 0){
			cout<<i<<" ";
		}
	}
	cout<<"\n";
	

    return 0;
}
