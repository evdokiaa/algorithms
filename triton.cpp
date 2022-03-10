#include <iostream>

using namespace std;

int compare(const void* a, const void* b){
        return (*(int*)a-*(int*)b);
}
int readint() {
                int n = 0;
                char c = getchar_unlocked();
                        while ( !( '0' <= c && c <= '9' ) ) {
                        c = getchar_unlocked();
                }
        while ( '0' <= c && c <= '9' ) {
                n = n * 10 + c - '0';
                c = getchar_unlocked();
        }
        return n;
}

struct diavash_info {
	long long int x,y;
	bool arxh,telos;

};// struct me tis syntetagmenes kathe diavashs 

int main(){
	long long int N, M, K, X;
	N=readint();
	M=readint();
	K=readint();
	X=readint();
	int number = 1000000103;
	
	diavash_info diavaseis[180][180]; //grid me tis plhrofories twn diavasewn  
	

	for (int i=0; i<K; i++) {
		long long int s=readint();
		long long int e=readint();

		diavaseis[s/M][s%M].arxh=true;
		diavaseis[e/M][e%M].telos=true;
		diavaseis[e/M][e%M].x=s/M;
		diavaseis[e/M][e%M].y=s%M;
	}

	long long int grid[N][M][X+1]={0};
	cout << grid[1][2][0] << " "; 
	long long int result = 0;
	
	grid[N-1][M-1][0]=1;
	
	for (int k=0; k<X+1; k++){
		for (int i=N-1; i>=0; i--){
			for (int j=M-1; j>=0; j--){
				if (diavaseis[i+1][j].arxh==false){
					grid[i][j][k]+=(grid[i+1][j][k])%number;
				}
				if (diavaseis[i][j+1].arxh==false){
					grid[i][j][k]+=grid[i][j+1][k]%number;
				}

				if(diavaseis[i][j].telos==true && k>0){
				        grid[i][j][k]+=grid[diavaseis[i][j].x][diavaseis[i][j].y][k-1]%number;
				
				}
			}
		}
		result += grid[0][0][k] % number;
	}

	cout << result%number << endl;
}
				
	

		
