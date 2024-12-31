#include <bits/stdc++.h>
#define l '\n'
using namespace std;

using ll = long long;
//goal of the problem is to calculate a binary representation of the total cost of all possible paths in a graph
//just recall for me :
// Nodes represent cities
// Edges represent roads, each with a cost
// The graph forms a connected component after considering the minimum spanning tree (MST)
// Output the total cost of all paths in binary format


class DSU {  //Disjoint Set Union (DSU): for building the MST
	private: int n;
	vector < int > parent;
	public: DSU(int n) {
		this-> n = n;
		parent.assign(n, 0);
		for(int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}
	int find(int node) {
		if(node == parent[node]) {
			return node;
		}
		return parent[node] = find(parent[node]);
	}
	bool unite(int node1, int node2) {
		int root1 = find(node1);
		int root2 = find(node2);
		if(root1 != root2) {
			parent[root2] = root1;
			return true;
		}
		return false;
	}
};
vector < vector < pair < ll, ll >>> adj;  //Adjacency List (adj): Stores the MST structure ,,,, Each node points to its neighbors along with the edge cost
vector < ll > childCount; //Stores the number of nodes in the subtree rooted at each node -->Calculated via a depth-first search (DFS).


ll dfs(ll node, ll parent) {
	ll count = 1;
	for(auto[nbr, cost]: adj[node]) {
		if(nbr == parent)
			continue;
		count += dfs(nbr, node);
	}
	childCount[node] = count;
	return count;
}
const int MAXN = 1e6;
vector < ll > powers(MAXN, 0);  //powers[i] stores the number of paths with a cost of 2**i
void solve() {
	ll n, m;
	cin >> n >> m;
	adj.resize(n);
	childCount.assign(n, 0);
	vector < array < ll, 3 >> edges(m);
	vector < array < ll, 3 >> goodEdges;
	for(int i = 1; i <= m; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		a -= 1;
		b -= 1;
		edges[i - 1] = {
			c,
			a,
			b
		};
	}
	sort(edges.begin(), edges.end());
	DSU dsu(n);
	for(auto edge: edges) {
		auto[c, a, b] = edge;
		if(dsu.unite(a, b)) {
			adj[a].push_back({
				b,
				c
			});
			adj[b].push_back({
				a,
				c
			});
			goodEdges.push_back({
				a,
				b,
				c
			});
		}
	}
	dfs(0, 0);
	ll ans = 0;
	for(auto edge: goodEdges) {
		auto[a, b, c] = edge;
		ll mul = min(childCount[a], childCount[b]) * (n - min(childCount[a], childCount[b]));
		powers[c] += mul;
	}
	for(int i = 0; i < MAXN; i++) {
		if(powers[i] <= 1)
			continue;
		if(powers[i] & 1) {
			ll extra = powers[i] - 1;
			powers[i + 1] += (extra / 2);
			powers[i] = 1;
			continue;
		}
		ll extra = powers[i];
		powers[i + 1] += (extra / 2);
		powers[i] = 0;
		continue;
	}
	bool ok = false;
	for(int i = MAXN; i >= 0; i--) {
		if(powers[i]) {
			ok = true;
		}
		if(ok) {
			cout << powers[i];
		}
	}
	cout << l;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
	return 0;
}
