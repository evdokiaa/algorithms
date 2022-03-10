#include <bits/stdc++.h> 
#include <vector>
using namespace std; 

class Edge  
{  
    public: 
    int src, dest, weight;  
};

// Fucntion to add an edge to the tree 
void addEdge(vector<Edge>& edges, 
             list<int>* tree, int x, int y) 
{ 
    edges.push_back({ x, y }); 
    tree[x].push_back(y); 
    tree[y].push_back(x); 
} 
  
// Function to run DFS and calculate the 
// height of the subtree below it 
void dfs(vector<Edge>& edges, list<int>* tree, 
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
int maximizeSum(vector<Edge>& edges, 
                list<int>* tree, int n) 
{ 
  
    // Initialize it which stores the 
    // height of the subtree beneath it 
    int dp[n + 1] = { 0 }; 
  
    // Call the DFS function to 
    dfs(edges, tree, 1, 0, dp); 
    for (int i=0; i<n+1; i++){
	    cout <<  dp[i] << " ";
    }
    
    // Sort the given array 
    //sort(a, a + (n - 1)); 
  
    // Stores the number of times an 
    // edge is part of a path 
    vector<int> ans; 
  
    // Iterate for all edges and find the 
    // number of nodes on the left and on the right 
    for (auto it : edges) { 
  
        // Node 1 
        int x = it.src; 
  
        // Node 2 
        int y = it.dest; 
         
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
  
    int res = 0; 
  
    // Find the summation of all those 
    // paths and return 
    for (int i = 0; i < n - 1; i++) {     
        res += ans[i] * edges[i].weight;
       cout << ans[i];	
    } 
  
    return res; 
} 

class Graph{
    public:
    // V-> Number of vertices, E-> Number of edges
    int V, E;

    // graph is represented as an array of edges.   // Since the graph is undirected, the edge
    // from src to dest is also edge from dest    // to src. Both are counted as 1 edge here.
    Edge* edge;
};

// Creates a graph with V vertices and E edges
Graph* createGraph(int V, int E){
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;

    graph->edge = new Edge[E];

    return graph;
}

// A structure to represent a subset for union-find
class subset{
    public:
    int parent;
    int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int find(subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}
void Union(subset subsets[], int x, int y){
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    // If ranks are same, then make one as root and
    // increment its rank by one
    else    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}

// The main function to construct MST using Kruskal's algorithm
void KruskalMST(Graph* graph)
{ 
    int V = graph->V;
    list<int>* tree = new list<int>[V+1];
    vector<Edge> result(V);
    //ore the resultant MST
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges

    // Step 1: Sort all the edges in non-decreasing   // order of their weight. If we are not allowed to
    // change the given graph, we can create a copy of    // array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    // Allocate memory for creating V ssubsets
    subset *subsets = new subset[( V * sizeof(subset) )];

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v){
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < graph->E)
    {
        // Step 2: Pick the smallest edge. And increment
        // the index for next iteration
        Edge next_edge = graph->edge[i++];
	int x = find(subsets, next_edge.src);
	int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
    cout << maximizeSum(result,tree,e) << endl;
    for (i = 0; i < e; ++i)
        cout<<result[i].src<<" -- "<<result[i].dest<<" == "<<result[i].weight<<endl;
    return;
}

// Driver code
int main()
{
    /* Let us create following weighted graph
            10
        0--------1
        | \ |
    6| 5\ |15
        | \ |
        2--------3
            4 */
    int V = 4; // Number of vertices in graph
    int E = 5; // Number of edges in graph
    Graph* graph = createGraph(V, E);


    // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    // add edge 0-2
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    // add edge 0-3
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    // add edge 1-3
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    // add edge 2-3
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    KruskalMST(graph);

    return 0;
}

// This code is contributed by rathbhupendra

