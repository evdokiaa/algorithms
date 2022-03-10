#include <iostream>
#include <vector>
#include <tuple>


//https://cs.stackexchange.com/questions/119114/min-vertex-cover-to-access-k-edges-in-a-tree

using namespace std;

const int apeiro = 2147483647;

vector<int> sakidiaki(const vector<int> x, const vector<int> y, int z) {
    
    int a = x.size();
    int b = y.size();
    
    vector<int> k(a+b-1, -apeiro);

    for (int i = 0; i < a; ++i)  for (int j = 0; j < b; ++j) k[i+j] = max(k[i+j], x[i] + y[j]);
    
    if (k.size() > z) k.resize(z);
    
return k;
}

pair<vector<int>, vector<int>> depth(int a, int b, int c, const vector<vector<int>>& f) {

    vector<int> DP_1 = {0, 0};
    vector<int> DP_2 = {-apeiro, (int)f[a].size() - (b != -1)};

    for (auto t : f[a]) {
        if (t == b) continue;
        vector<int> DP_1_t, DP_2_t;
        tie(DP_1_t, DP_2_t) = depth(t, a, c, f);
        int m = DP_1_t.size();

        vector<int> v1(m), v2(m);
        for (int j = 0; j < m; ++j) v1[j] = max(DP_1_t[j], DP_2_t[j] + 1);
        for (int j = 0; j < m; ++j) v2[j] = max(DP_1_t[j], DP_2_t[j]);
        DP_1 = sakidiaki(DP_1, v1, c+1);
        DP_2 = sakidiaki(DP_2, v2, c+1);
    }
    return {DP_1, DP_2};
}

int vertexCover(int a, const vector<vector<int>>& b) {
    vector<int> DP_1, DP_2;
    tie(DP_1, DP_2) = depth(0, -1, a, b);
    for (int i = 0;; ++i) {
        if (max(DP_1[i], DP_2[i]) >= a) return i;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
                                                                                                                                                                                         
    int N, K;
    cin >> N >> K;

    vector<vector<int>> v(N);
    for (int i = 0; i < N-1; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        v[x].push_back(y);
        v[y].push_back(x);
    }

    int l = vertexCover(K, v);
    cout << l << '\n';
}
