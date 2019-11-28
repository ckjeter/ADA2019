#include <array>
#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>
#include <climits>
#include <numeric>
using namespace std;
int get_last_smaller(const std::vector<int>& v, int x)
{
  int first = 0, last = int(v.size()) - 1;
  while (first <= last)
  {
    long long mid = (first + last) / 2;
    if (v[mid] > x)
      last = mid - 1;
    else
      first = mid + 1;
  }
  return first - 1 < 0 ? -1 : first - 1;
}

void print(const std::vector<int>& v){
	for (int i=0;i<v.size();i++){
		std::cout<<v[i]<<" ";
	}
	std::cout<<"\n";
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N,input;
    std::cin>>N;
    std::vector<int> A,B;
    for (int i = 0; i<3;i++){
      std::cin>>input;
      A.push_back(input);
    }
    std::sort(A.begin(), A.end());


    for (int i = 0; i<N;i++){
      std::cin>>input;
      B.push_back(input);
    }
	std::sort(B.begin(), B.end());

	//impossible case
	if (B[N-1]>(A[0]+A[1]+A[2])){
	    std::cout<<-1;
	    return 0;
	}

	int turns = 0;

	//1+2+3 case
	int second_power_index = get_last_smaller(B,A[1]+A[2]);
	turns += (B.size()-(second_power_index+1));
	if (turns>0){
	B.erase(B.begin()+second_power_index+1,B.end());
	}

	//2+3 case
	int count=0;
	int next_power_index  = get_last_smaller(B,A[0]+A[2]);
	int free_power_index = get_last_smaller(B,A[0]);

	count = (B.size()-(next_power_index+1));
	if (count > 0){
		B.erase(B.begin()+next_power_index+1,B.end());

	}
	turns +=count;
	if (count>0 and free_power_index >=0){
		B.erase(B.begin()+std::max(0,free_power_index-count+1),
			B.begin()+free_power_index+1);
	}

	//1+3 case
	count=0;
	int f_th_max = std::max(A[2],A[1]+A[0]);
	if (f_th_max == A[2]){
		next_power_index  = get_last_smaller(B,A[2]);
		free_power_index = get_last_smaller(B,A[1]);
	}
	else{
		next_power_index  = get_last_smaller(B,A[1]+A[0]);
		free_power_index = get_last_smaller(B,A[1]);
	}
	count = (B.size()-(next_power_index+1));
	if (count > 0){
		B.erase(B.begin()+next_power_index+1,B.end());
	}
	turns +=count;
	if (count>0 and free_power_index >=0){
		B.erase(B.begin()+std::max(0,free_power_index-count+1),
			B.begin()+free_power_index+1);
	}
	if (f_th_max == A[1]+A[0]){

		next_power_index  = get_last_smaller(B,A[2]);
		free_power_index = get_last_smaller(B,A[2]);
		count=0;
		count = (B.size()-(next_power_index+1));
		if (count > 0){
			B.erase(B.begin()+next_power_index+1,B.end());
		}

		turns +=count;
		if (count>0 and free_power_index >=0){
			B.erase(B.begin()+std::max(0,free_power_index-count+1),
				B.begin()+free_power_index+1);
		}
	}


	//3 case
	int index0 = get_last_smaller(B,A[0]);
	int index1 = get_last_smaller(B,A[1]);
	int index2 = get_last_smaller(B,A[2]);
	int index3 = get_last_smaller(B,A[0]+A[1]);


	int *pointer0 = &index0;
	int *pointer1 = &index1;
	int *pointer2 = &index2;
	int *pointer3 = &index3;

	if (index1==index0){
		pointer1 = pointer0;
	}

	if (index2==index1){
		pointer2 = pointer1;
	}

	int O_index0 = get_last_smaller(B,A[0]);
	int O_index1 = get_last_smaller(B,A[1]);
	int O_index2 = get_last_smaller(B,A[2]);
	int O_index3 = get_last_smaller(B,A[0]+A[1]);
	//std::cout<<"index2:"<<index2<<endl;
	int Q=1,special_case=0;

	int help1 = 0,help2 = 0,never=0;
	for (int i=0;i<B.size();){
		//cout<<*pointer3<<"/"<<*pointer1<<endl;
		//1
		if(*pointer0>=0){
			i++;
			(*pointer0)--;
		}
		else{
			help1=1;
		}

		//2
		if(*pointer1>=0 ){
			//cout<<"index:"<<index1<<endl;
			i++;
			(*pointer1)--;

			if( *pointer1 == O_index0){
				if (pointer2==pointer1){
					pointer2=pointer0;
				}
				pointer1 = pointer0;
			}
		}
		else{
			help2=1;
		}

		if(help2==1 and help1==1 and never==0){

			//initialize
			//cout<<*pointer3<<"/"<<*pointer2;
			if (*pointer3 >=(*pointer2)){
				Q=2;
				never=1;
			}

			else{
				special_case = 1;

				if ( *pointer3 == O_index1){
					*pointer3 = -1;
				}

				if(*pointer3>=0){
						i++;
						(*pointer3)--;
					}


			}


		}

		//3
		if(*pointer2>=0){
			//cout<<Q;
			i=i+Q;
			(*pointer2) = (*pointer2)-Q;

			if ( *pointer2 == O_index1){
				pointer2 = pointer1;
			}
			if (special_case ==1 and *pointer2 == O_index3){
				pointer2 = pointer3;
			}
		}



		turns+=1;
		//cout<<"turns:"<<turns<<endl;

	}




    std::cout<<turns<<"\n";
    return 0;
}
