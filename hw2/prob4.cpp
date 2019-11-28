#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int N;

void printvec(vector<int>& v)
{
	for (int i = 0; i < v.size(); i++) {
		cout<<v[i]<<" ";
	}
	cout<<endl;
}
int bsearch(int left, int right, int value, const vector<int>& v)
{
	/*
	if (left > right) {
		return left;
	}
	int mid = left + (right - left) / 2;
	if (value >= v[mid]) {
		return bsearch(mid + 1, right, value, v);
	}
	else return bsearch(left, mid - 1, value, v);
	*/
	while(left <= right) {
	   int mid = left + (right - left) / 2;
	   if (v[mid] <= value)
	   {
			left = mid + 1;
	   }
	   else right = mid - 1;
	}
	//return (value > v[left]) ? (left + 1) : left;
	return left;
}

void pos_update(vector<int>& pos, const vector<int>& s, const vector<int>& enemy)
{
	for (int i = 1; i < pos.size(); i++) {
		pos[i] = bsearch(0, enemy.size()-1, s[i], enemy);
	}
}

int main()
{
	int answer = 0;
	scanf("%d", &N);
	vector<int> s(8);
	vector<int> pos(8);
	pos[0] = 0;
	s[0] = 0;
	for (int i = 1; i <= 3; ++i)
	{
		scanf("%d", &s[i]);
	}
	sort(s.begin(), s.begin()+4);
	s[4] = s[1] + s[2];
	s[5] = s[1] + s[3];
	s[6] = s[2] + s[3];
	s[7] = s[1] + s[2] + s[3];

	vector<int> enemy(N);
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &enemy[i]);
	}
	sort(enemy.begin(), enemy.end());
	pos_update(pos, s, enemy);

	//檢查s6 ~ s7區間
	if (pos[7] < N) {
		answer = -1;
		enemy.erase(enemy.begin(), enemy.end());
	}
	else
	{
		answer += max(0, N - pos[6]);
		enemy.erase(enemy.begin()+pos[6], enemy.end());
	}
	pos_update(pos, s, enemy);

	//檢查s5 ~ s6區間，優先和s0 ~ s1區間一起消-------------------------------------------
	int count = pos[6] - pos[5];
	enemy.erase(enemy.begin()+pos[5], enemy.end());
	answer += count;
	if (count > 0 && pos[1] > 0){
		enemy.erase(enemy.begin() + max(0, pos[1] - count), enemy.begin() + pos[1]);
	}
	//printvec(enemy);
	//int tempindex = pos[1];
	//pos.erase(pos.end()-1);

	//假設s1 + s2 > s3
	if (s[1] + s[2] > s[3]) {
		//檢查s4 ~ s5區間，優先和s1 ~ s2區間一起消----------------------------------------
		pos_update(pos, s, enemy);
		count = pos[5] - pos[4];
		enemy.erase(enemy.begin()+pos[4], enemy.end());
		answer += count;
		if (count > 0 && pos[2] > 0){
			enemy.erase(enemy.begin() + max(0, pos[2] - count), enemy.begin() + pos[2]);
		}
		//pos.erase(pos.end()-1);

		//檢查s3 ~ s4區間，優先和s2 ~ s3區間一起消----------------------------------------
		pos_update(pos, s, enemy);
		count = pos[4] - pos[3];
		enemy.erase(enemy.begin()+pos[3], enemy.end());
		answer += count;
		if (count > 0 && pos[3] > 0){
			enemy.erase(enemy.begin() + max(0, pos[3] - count), enemy.begin() + pos[3]);
		}
		//pos.erase(pos.end()-1);

	}

	//s1 + s2 <= s3
	else {
		//檢查s3 ~ s5區間，優先和s1 ~ s2區間一起消----------------------------------------
		pos_update(pos, s, enemy);
		count = pos[5] - pos[3];
		enemy.erase(enemy.begin()+pos[3], enemy.end());
		answer += count;
		if (count > 0 && pos[2] > 0){
			enemy.erase(enemy.begin() + max(0, pos[2] - count), enemy.begin() + pos[2]);
		}
	}
	//printvec(enemy);

	//檢查所有<s3的--------------------------------------------------------------------------------
	pos_update(pos, s, enemy);
	/*
	while (enemy.size() > 0 && pos[2] > 0) {
		if (pos[1] > 0) {
			enemy.erase(enemy.begin()+pos[1]-1);
			pos[3]--;
			pos[2]--;
			pos[1]--;
		}
		if (pos[2] > 0) {
			enemy.erase(enemy.begin()+pos[2]-1);
			pos[3]--;
			if (pos[2] == pos[1]) {
				pos[2]--;
				pos[1]--;
			}
			else {
				pos[2]--;
			}
		}
		if (pos[3] > 0) {
			enemy.erase(enemy.begin()+pos[3]-1);
			if (pos[3] == pos[2] && pos[2] == pos[1]) {
				pos[3]--;
				pos[2]--;
				pos[1]--;
			}
			else if(pos[3] == pos[2] && pos[2] > pos[1]){
				pos[3]--;
				pos[2]--;
			}
			else{
				pos[3]--;
			}
		}
		answer++;
	}
	pos_update(pos, s, enemy);
	if (s[1]+s[2] > s[3]) {
		while (pos[3] > 0) {
			if (pos[3] > 0) {
				pos[3]--;
			}
			if (pos[3] > 0) {
				pos[3]--;
			}
			answer++;
		}
	}
	else {
		//pos[4] <= pos[3]
		while (enemy.size() > 0 && pos[4] > 0) {
			if (pos[4] > 0) {
				enemy.erase(enemy.begin()+pos[4]-1);
				pos[4]--;
				pos[3]--;
			}
			if (pos[3] > 0) {
				enemy.erase(enemy.begin()+pos[3]-1);
				if (pos[3] == pos[4]) {
					pos[3]--;
					pos[4]--;
				}
				else {
					pos[3]--;
				}
			}
			answer++;
		}
		pos_update(pos, s, enemy);
		while (pos[3] > 0) {
			pos[3]--;
			answer++;
		}

	}
	*/
	//此部分和連少甫同學討論做法
	int *pointer1 = &pos[1];
	int *pointer2 = &pos[2];
	int *pointer3 = &pos[3];
	int *pointer4 = &pos[4];

	if (pos[2] == pos[1]){
		pointer2 = pointer1;
	}

	if (pos[3] == pos[2]){
		pointer3 = pointer2;
	}

	int pos1 = pos[1];
	int pos2 = pos[2];
	int pos3 = pos[3];
	int pos4 = pos[4];

	int power3 = 1;
	bool combine1 = 0, combine2 = 0, never = 0, special_case = 0;

	int i = 0;
	while (i < enemy.size()){
		//s1
		if(*pointer1 > 0){
			i++;
			(*pointer1)--;
		}
		else{//s1沒用到
			combine1 = 1;
		}

		//s2
		if(*pointer2 > 0){
			i++;
			(*pointer2)--;
			if(*pointer2 == pos1){
				if (pointer3 == pointer2){
					pointer3 = pointer1;
				}
				pointer2 = pointer1;
			}
		}
		else{//s2沒用到
			combine2 = 1;
		}

		//s1+s2
		if(combine2 == 1 && combine1 == 1 && never == 0){
			if (*pointer4 >= (*pointer3)){
				//s1+s2 >= s3
				power3 = 2;
				never = 1;
			}
			else {
				//s1+s2 < s3
				special_case = 1;
				if (*pointer4 == pos2){
					*pointer4 = 0;
				}
				if(*pointer4 > 0){
						i++;
						(*pointer4)--;
					}
			}
		}

		//s3
		if(*pointer3 > 0){
			i += power3;
			(*pointer3) = (*pointer3) - power3;

			if (*pointer3 == pos2){
				pointer3 = pointer2;
			}
			if (special_case == 1 && *pointer3 == pos4){
				pointer3 = pointer4;
			}
		}
		answer += 1;

	}

	printf("%d\n", answer);
	return 0;
}
