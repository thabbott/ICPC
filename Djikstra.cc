/**
 * This code provides structures and functions for shortest path finding
 * with Djikstra's algorithm. The code uses the built-in C++ priority
 * queue, which does not include a decreaseKey operation.  Instead, the
 * priority queue may hold duplicates of a vertex, and will continue
 * removing elements at each step until it finds the minimum weight unvisited
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

struct Node {
  // Vertex number
  ll v;
  // Current cost of visiting
  T c;
  // Constructors
  Node(ll vx, T cost) { v = vx; c = cost; }
  Node() {}
};

struct Edge {
  // End vertex
  ll v;
  // Weight
  T w;
  // Constructor
  Edge(ll vx, T wt) { v = vx; w = wt; }
};

typedef vector<Edge> VE;
typedef vector<VE> VVE;

// This class should be used to control the priority queue ordering
class priority {
  public:
    bool operator()(Node &n1, Node &n2) {
      return n1.c > n2.c;
    }
};

/**
 * Perform Djikstra's algorithm from source node s to target node t.
 * g is an adjacency list representation of a graph.
 *
 * The function return -1 if no path exists.
 */
T djikstra(ll s, ll t, VVE &g) {
 
  VT dist(g.size(), INF);
  VB vis(g.size(), false);
  dist[s] = 0;
  priority_queue<Node, vector<Node>, priority> pq;
  pq.push(Node(s, 0));

  while (true) {
    Node cur;
    do {
      if (pq.empty()) return -1;
      cur = pq.top();
      pq.pop();
    } while (vis[cur.v]);
    vis[cur.v] = true;

    if (cur.v == t) return cur.c;
    dist[cur.v] = cur.c;

    for (ll i = 0; i < g[cur.v].size(); i++) {
      Edge e = g[cur.v][i];
      if (!vis[e.v]) {
	pq.push(Node(e.v, dist[cur.v] + e.w));
      }
    }
  }
}

// Testing / example construction of an adjacency list
// A few simple tests suggest that it works correctly...
int main(void) {
  VVE adj(5);
  adj[0].push_back(Edge(1, 1));
  adj[0].push_back(Edge(2, 5));
  adj[1].push_back(Edge(2, 2));
  adj[2].push_back(Edge(3, 3));
  adj[3].push_back(Edge(1, 1));

  cout << djikstra(0, 3, adj) << endl;
  cout << djikstra(3, 4, adj) << endl;
}
