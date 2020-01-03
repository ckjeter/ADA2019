#include <iostream>
#include <vector>
#include <functional>
#include <cstdlib>
#include "hex.h"

using namespace std;
typedef pair<int, int> pii;

const int maxn = 11;

int board[maxn][maxn];
int round;
int n;
pii high;
pii low;

void init(int _n) {
    n = _n;
    for (int i = 0; i < maxn; i++){
        for (int j = 0; j < maxn; j++){
            board[i][j] = 0;
        }
    }
    high = make_pair(n/2, n/2);
    low = make_pair(n/2, n/2);
    round = 1;
    srand(12345);
}
pii rand_pos(){
    vector<pii> unused;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (board[i][j] == 0)
                unused.push_back({i, j});
    //cout<<"random!"<<endl;
    return unused[rand() % unused.size()];
}

pii decide(pii p) {
    pii res;
    if (p == make_pair(-1, -1)) {
        if (n % 2 == 1){
            res = make_pair(n/2, n/2);
        }
        else {
            res = make_pair(n/2, n/2 - 1);
            high = make_pair(n/2, n/2 - 1);
            low = make_pair(n/2, n/2 - 1);
        }
        board[res.first][res.second] = round;
        return res;
    }
    else {
        round++;
        board[p.first][p.second] = round;
    }
    
    if (n == 4 && board[0][2] == 2 && round == 2){
        res = make_pair(1, 0);
        round++;
        board[1][0] = round;
        //cout << "hi1" << endl;
        return res;
    }
    if (n == 4 && board[1][1] == 4 && board[0][2] == 2 && round == 4){
        res = make_pair(2, 0);
        high = make_pair(1, 0);
        round++;
        board[2][0] = round;
        //cout << "hi2" << endl;
        return res;
    }

    if (n == 4 && board[0][2] == 4 && round == 4 && !board[1][0] && !board[0][1] && high.first == 2)
    {
        res = make_pair(1, 0);
        round++;
        board[1][0] = round;
        //cout << "hi3" << endl;
        return res;
    }
    if (n == 4 && board[1][1] == 6 && board[0][2] == 4 && round == 6 && !board[2][0] && !board[0][1] && high.first == 2)
    {
        res = make_pair(2, 0);
        high = make_pair(1, 0);
        round++;
        board[2][0] = round;
        //cout << "hi4" << endl;
        return res;
    }

    //���W�b��
    if ((p.first < n/2 && high.first != 0 && high.second != n - 1 && high.second != 0) || low.first == n - 1){
        bool isrand = 0;
        if (!board[high.first - 1][high.second] && !board[high.first - 1][high.second + 1]){
            //�S�ר��
            if (p.second > high.second) res = make_pair(high.first - 1, high.second);//�����b��
            else res = make_pair(high.first - 1, high.second + 1);//���k�b��
            
        }
        else{//�ר��
            if (!board[high.first - 1][high.second + 1]) res = make_pair(high.first - 1, high.second + 1);
            else if (!board[high.first - 1][high.second]) res = make_pair(high.first - 1, high.second);
            else if (!board[high.first][high.second - 1]) res = make_pair(high.first, high.second - 1);
            else {
                res = rand_pos();
                isrand = 1;
            }
        }
        if (!isrand) high = res;
        if (board[high.first][high.second - 1] % 2 == 1 && n == 4) high = make_pair(high.first, high.second - 1);
    }
    //���U�b��
    else if (p.first >= n/2 && low.first != n - 1 && low.second != 0 && low.second != n - 1) {
        bool isrand = 0;
        if (!board[low.first + 1][low.second] && !board[low.first + 1][low.second - 1]){
            //�S�ר��
            if (p.second >= low.second) res = make_pair(low.first + 1, low.second - 1);//�����b��
            else res = make_pair(low.first + 1, low.second);//���k�b��
        }
        else{//�ר��
            if (!board[low.first + 1][low.second - 1]) res = make_pair(low.first + 1, low.second - 1);
            else if (!board[low.first + 1][low.second]) res = make_pair(low.first + 1, low.second);
            else if (!board[low.first][low.second + 1]) res = make_pair(low.first, low.second + 1);
            else {
                res = rand_pos();
                isrand = 1;
            }
        }
        if (!isrand) low = res;
    }
    else res = rand_pos();
    round++;
    board[res.first][res.second] = round;
    return res;
    
}