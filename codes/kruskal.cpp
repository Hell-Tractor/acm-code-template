int n, m;
vector<tuple<int, int, int>> edge;
int Kruskal() {
	int ans = 0, count = 0;
	sort(all(edge), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
		return get<2>(a) < get<2>(b);
	});
	DSU dsu(edge.size() + 1);
	for (auto& [u, v, w] : edge) {
		if (!dsu.check(u, v)) {
			ans += w;
			count++;
			if (count == n - 1)
				return ans;
			dsu.union(u, v);
		}
	}
}
