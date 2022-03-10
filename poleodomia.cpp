#include <iostream>
#include <stack>
#include <utility>

using namespace std;

int main(){
	unsigned long int N;
	cin >> N;
	unsigned long long int *H=new unsigned long long int[N];
        unsigned long long int *CL=new unsigned long long int[N];
	unsigned long long int *CR=new unsigned long long int[N];
	
	for (int i=0; i<N; i++){
		cin >> H[i];
	}
	CL[0]=H[0];
	stack<pair<unsigned long long int,unsigned long long int>> stiva;
	stiva.push(make_pair(H[0],0));
	for (int i=1; i<N; i++){
        	while(get<0>(stiva.top())<H[i]){
			stiva.pop();
			if (stiva.empty()) break;
		}
		if (!stiva.empty()) {
			CL[i]=CL[get<1>(stiva.top())]+(i-get<1>(stiva.top()))*H[i];
		}
		else {
			CL[i]=(i+1)*H[i];
		}
		stiva.push(make_pair(H[i],i));
		
        }
	while(!stiva.empty()) {
		stiva.pop();
	}
	CR[N-1]=H[N-1];
	stiva.push(make_pair(H[N-1],N-1));

	for (int i=1; i<N; i++){
                while(get<0>(stiva.top())<H[N-1-i]){
                        stiva.pop();
                        if (stiva.empty()) break;
                }
                if (!stiva.empty()) {
                        CR[N-1-i]=CR[get<1>(stiva.top())]+(get<1>(stiva.top())-(N-i-1))*H[N-1-i];
                }
                else {
                        CR[N-1-i]=(i+1)*H[N-1-i];
                }
                stiva.push(make_pair(H[N-1-i],N-1-i));

        }
	unsigned long long int min=CR[0]+CL[0]-H[0];
	for (int i=1; i<N; i++){
		if (CR[i]+CL[i]-H[i]<min) {
			min=CR[i]+CL[i]-H[i]; 
		}		
	}
	cout << min << endl;



}

