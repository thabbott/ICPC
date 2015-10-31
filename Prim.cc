/**
 * This code provides structures and functions for MST finding using
 * Prim's algorithm. The code uses the built-in C++ priority
 * queue, which does not include a decreaseKey operation.  Instead, the
 * priority queue may hold duplicates of a vertex, and will continue
 * removing elements at each step until it finds the minimum cost unvisited
 * vertex.
 *
 * This implementation uses directed edges. To calculate a MST using undirected
 * edges, include (u,v), w and (v,u), w if an edge between u and v has weight w.
 *
 * If the algorithm is run without doing this, it will return a spanning tree
 * (NOT necessarily an MST) for the directed connected component of the start 
 * vertex.
 */
#include <iostream>
#include <vector>
#include <queue>

#define INF 100000001

using namespace std;

typedef long long ll;
typedef double T;
typedef vector<T> VT;
typedef vector<bool> VB;

struct Edge {
  // End vertex
  ll v;
  // Weight
  T w;
  // Constructors
  Edge(ll vx, T wt) { v = vx; w = wt; }
  Edge() {}
};

typedef vector<Edge> VE;
typedef vector<VE> VVE;

// This class should be used to control the priority queue ordering
class priority {
  public:
    bool operator()(Edge &e1, Edge &e2) {
      return e1.w > e2.w;
    }
};

/**
 * Add an undirected edge from vertex indexed at u to vertex indexed at v, of
 * weight w. VVE is an adjacency list representation of the graph and must be
 * initialized.
 */
void addEdge(ll u, ll v, ll w, VVE &g) {
  g[u].push_back(Edge(v, w));
  g[v].push_back(Edge(u, w));
}

/**
 * Perform Prim's algorithm starting from node s.
 * g is an adjacency list representation of a graph.
 *
 * The function will return the MST for the connected component of g that
 * node s is in.  Modifying the function to detect if the entire graph is
 * connected can be done by counting the number of edges included in the
 * MST.
 * NOTE: this function handles duplicate edges and edges to and from the
 * same node.
 */
T prim(ll s, VVE &g) {
 
  T cost;
  VB vis(g.size(), false);
  priority_queue<Edge, vector<Edge>, priority> pq;

  // Enqueue all edges leaving from s
  vis[s] = true;
  for (ll i = 0; i < g[s].size(); i++) {
    if (!vis[g[s][i].v]) {
      pq.push(g[s][i]);
    }
  }
  
  // Build tree
  for (ll i = 0; i < g.size() - 1; i++) {
    Edge cur;
    do {
      if (pq.empty()) return cost;
      cur = pq.top();
      pq.pop();
    } while (vis[cur.v]);
    vis[cur.v] = true;

    cost += cur.w;

    for (ll i = 0; i < g[cur.v].size(); i++) {
      if (!vis[g[cur.v][i].v]) {
	pq.push(g[cur.v][i]);
      }
    }
  }
  return cost;
}

// Testing / example construction of an adjacency list
// A few simple tests suggest that it works correctly...
int main(void) {
  VVE adj(5);
  addEdge(0, 1, 1, adj);
  addEdge(0, 2, 5, adj);
  addEdge(1, 2, 2, adj);
  addEdge(2, 3, 3, adj);
  addEdge(3, 1, 1, adj);

  cout << prim(0, adj) << endl;
  cout << prim(4, adj) << endl;
}
