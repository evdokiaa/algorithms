#include <iostream>
#include <queue>


using namespace std;

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

int main(){
	int N,M;
	N=readint();
	M=readint();
	queue<int> graph[N][N];
	for(int i=0; i<N; i++){
                for (int j=0; j<N; j++){
                    if (i==j) graph[i][j].push(0);  
		    else graph[i][j].push(100);
                }
        }

	for (int k=0; k<M; k++){
		int i,j,d;
		i=readint();
		j=readint();
		d=readint();
		graph[i-1][j-1].pop();
		graph[i-1][j-1].push(d);
		graph[j-1][i-1].pop();
		graph[j-1][i-1].push(d);

	}

	/*for (int k = 0; k < N; k++) {
	    for (int i = 0; i < N; i++)	{
		for (int j = 0; j < N; j++)	{
	            if (graph[i][k] + get<0>(graph[k][j]) < get<0>(graph[i][j]))
		        get<0>(graph[i][j]) = get<0>(graph[i][k]) + get<0>(graph[k][j]);
		        graph[i][j]=make_tuple(get<0>(graph[i][k]) + get<0>(graph[k][j]),
			}
	    }
	}*/
	for(int i=0; i<N; i++){
	    for (int j=0; j<N; j++){
	        cout << graph[i][j].front();
		cout << " ";
	    }
	    cout << endl;
	}
return 0;

}
