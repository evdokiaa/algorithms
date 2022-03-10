#include <iostream> 
#include <vector> 

using namespace std;

//meros tou kwdika exei parthei apo to parakatw link 
//https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/?fbclid=IwAR1sXLGSNiyhlzU22CMgWcqHevOXkg9PA3tySOynIJvRgHkg6ViaoCublO8
// Binary search (note boundaries in the caller) 
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

long long int CeilIndex(vector<long long int>& v, long long int l,long long int r,long long int key) 
{ 
	while (r - l > 1) { 
		long long int m = l + (r - l) / 2; 
		if (v[m] >= key) 
			r = m; 
		else
			l = m; 
	} 

	return r; 
}

long long int CeilIndex2(vector<long long int>& v, long long int l,long long int r,long long int key)
{
        while (r - l > 1) {
                long long int m = l + (r - l) / 2;
                if (v[m] <= key)
                        r = m;
                else
                        l = m;
        }

        return r;
}


long long int LongestIncreasingSubsequenceLength(vector<long long int>& v) 
{ 
	if (v.size() == 0) 
		return 0; 

	vector<long long int> tail(v.size(), 0);
	vector<long long int> tail2(v.size(), 0);
        vector<long long int> lis(v.size(), 0);	
	vector<long long int> lds(v.size(), 0);
	
	long long int length = 1; // always points empty slot in tail 
	long long int length2 = 1;
	
	tail[0] = v[0]; 
	for (size_t i = 1; i < v.size(); i++) { 

		if (v[i] < tail[0]){ 
			tail[0] = v[i];	
		}

		else if (v[i] > tail[length - 1]){ 
			tail[length++] = v[i]; 
		}

		else{	
			long long int l=CeilIndex(tail, -1, length - 1, v[i]);
			tail[l] = v[i];
		 }
		lis[i]=length;
	}
	
	for (int i = v.size()-1; i >-1 ; i--){
		if (v[i] > tail2[0]){
                        tail2[0] = v[i];
                }

                else if (v[i] < tail2[length2 - 1]){
                        tail2[length2++] = v[i];
                }
                else{
                        long long int l=CeilIndex2(tail2, -1, length2 - 1, v[i]);
                        tail2[l] = v[i];
		}
                lds[i]=length2;
	}
		
	int max=0;
	for (int i=0; i<v.size(); i++){
		if (lis[i]+lds[i]>max) max=lis[i]+lds[i];
	}

	return max; 
	
}


int main() 
{ 
		
	long long int N, K;
	N=readint();
	K=readint();
	vector<long long int> v(N, 0);
        for (long long int i=0; i<N; i++){
		v[i]=readint();
	}	
	cout << LongestIncreasingSubsequenceLength(v) << '\n';
	return 0; 
} 

