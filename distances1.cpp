// C++ program to implement the 
// above approach 
#include <bits/stdc++.h> 

using namespace std; 

// Fucntion to add an edge to the tree 
void addEdge(vector<pair<int, int> >& edges, 
			list<int>* tree, int x, int y) 
{ 
	edges.push_back({ x, y }); 
	tree[x].push_back(y); 
	tree[y].push_back(x); 
} 

// Function to run DFS and calculate the 
// height of the subtree below it 
void dfs(vector<pair<int, int> >& edges, list<int>* tree, 
		int node, int parent, int dp[]) 
{ 
	// Initially initialize with 1 
	dp[node] = 1; 

	// Traverse for all nodes connected to node 
	for (auto it : tree[node]) { 
		// If node is not parent 
		// then recall dfs 
		if (it != parent) { 
			dfs(edges, tree, it, node, dp); 

			// Add the size of the 
			// subtree beneath it 
			dp[node] += dp[it]; 
		} 
	} 
} 

// Function to assign weights to edges 
// to maximize the final sum 
int maximizeSum(int a[], vector<pair<int, int> >& edges, 
				list<int>* tree, int n) 
{ 

	// Initialize it which stores the 
	// height of the subtree beneath it 
	int dp[n + 1] = { 0 }; 

	// Call the DFS function to 
	dfs(edges, tree, 1, 0, dp); 

	// Sort the given array 
	//sort(a, a + (n - 1)); 

	// Stores the number of times an 
	// edge is part of a path 
	vector<int> ans; 

	// Iterate for all edges and find the 
	// number of nodes on the left and on the right 
	for (auto it : edges) { 

		// Node 1 
		int x = it.first; 

		// Node 2 
		int y = it.second; 

		// If the number of nodes below is less 
		// then the other will be n - dp[node] 
		if (dp[x] < dp[y]) { 
			int fi = dp[x]; 
			int sec = n - dp[x]; 
			ans.push_back(fi * sec); 
		} 

		// Second condition 
		else { 
			int fi = dp[y]; 
			int sec = n - dp[y]; 
			ans.push_back(fi * sec); 
		} 
	} 

	// Sort the number of times 
	// an edges occurs in the path 
	//sort(ans.begin(), ans.end()); 
	int res = 0; 

	// Find the summation of all those 
	// paths and return 
	for (int i = 0; i < n - 1; i++) { 
		res += ans[i] * a[i]; 
	} 

	return res; 
}  
// C++ program for Kruskal's algorithm to find Minimum 
// Spanning Tree of a given connected, undirected and 
// weighted graph 

// Creating shortcut for an integer pair 
typedef pair<int, int> iPair; 

// Structure to represent a graph 
struct Graph 
{ 
	int V, E; 
	vector< pair<int, iPair> > edges; 

	// Constructor 
	Graph(int V, int E) 
	{ 
		this->V = V; 
		this->E = E; 
	} 

	// Utility function to add an edge 
	void addEdge(int u, int v, int w) 
	{ 
		edges.push_back({w, {u, v}}); 
	} 

	// Function to find MST using Kruskal's 
	// MST algorithm 
	int kruskalMST(); 
}; 

// To represent Disjoint Sets 
struct DisjointSets 
{ 
	int *parent, *rnk; 
	int n; 

	// Constructor. 
	DisjointSets(int n) 
	{ 
		// Allocate memory 
		this->n = n; 
		parent = new int[n+1]; 
		rnk = new int[n+1]; 

		// Initially, all vertices are in 
		// different sets and have rank 0. 
		for (int i = 0; i <= n; i++) 
		{ 
			rnk[i] = 0; 

			//every element is parent of itself 
			parent[i] = i; 
		} 
	} 

	// Find the parent of a node 'u' 
	// Path Compression 
	int find(int u) 
	{ 
		/* Make the parent of the nodes in the path 
		from u--> parent[u] point to parent[u] */
		if (u != parent[u]) 
			parent[u] = find(parent[u]); 
		return parent[u]; 
	} 

	// Union by rank 
	void merge(int x, int y) 
	{ 
		x = find(x), y = find(y); 

		/* Make tree with smaller height 
		a subtree of the other tree */
		if (rnk[x] > rnk[y]) 
			parent[y] = x; 
		else // If rnk[x] <= rnk[y] 
			parent[x] = y; 

		if (rnk[x] == rnk[y]) 
			rnk[y]++; 
	} 
}; 

/* Functions returns weight of the MST*/

int Graph::kruskalMST() 
{ 
	int mst_wt = 0; // Initialize result 
	vector< pair<int, int> > result;
	// Sort edges in increasing order on basis of cost 
	sort(edges.begin(), edges.end()); 

	// Create disjoint sets 
	DisjointSets ds(V); 

	// Iterate through all sorted edges 
	vector< pair<int, iPair> >::iterator it; 
	for (it=edges.begin(); it!=edges.end(); it++) 
	{ 
		int u = it->second.first; 
		int v = it->second.second; 

		int set_u = ds.find(u); 
		int set_v = ds.find(v); 

		// Check if the selected edge is creating 
		// a cycle or not (Cycle is created if u 
		// and v belong to same set) 
		if (set_u != set_v) 
		{ 
			// Current edge will be in the MST 
			// so print it 
			cout << u << " - " << v << endl; 
			a
			// Update MST weight 
			mst_wt += it->first; 

			// Merge two sets 
			ds.merge(set_u, set_v); 
		} 
	} 
	
	return mst_wt; 
} 

// Driver program to test above functions 
int main() 
{ 
	/* Let us create above shown weighted 
	and unidrected graph */
	int V = 9, E = 14; 
	Graph g(V, E); 

	// making above shown graph 
	g.addEdge(0, 1, 4); 
	g.addEdge(0, 7, 8); 
	g.addEdge(1, 2, 8); 
	g.addEdge(1, 7, 11); 
	g.addEdge(2, 3, 7); 
	g.addEdge(2, 8, 2); 
	g.addEdge(2, 5, 4); 
	g.addEdge(3, 4, 9); 
	g.addEdge(3, 5, 14); 
	g.addEdge(4, 5, 10); 
	g.addEdge(5, 6, 2); 
	g.addEdge(6, 7, 1); 
	g.addEdge(6, 8, 6); 
	g.addEdge(7, 8, 7); 

	cout << "Edges of MST are \n"; 
	int mst_wt = g.kruskalMST(); 

	cout << "\nWeight of MST is " << mst_wt; 

	return 0; 
} 

