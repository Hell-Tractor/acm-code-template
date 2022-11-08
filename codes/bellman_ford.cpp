const int INF = INT64_MAX / 3;
vector<vector<pii>> edge;
int n, m;
vector<int> dis;

bool bellmanford(int s) {
	dis.resize(n + 1);
	fill(all(dis), INF);
	dis[s] = 0;
	bool flag;
	FOR (i, 1, n) {
		flag = false;
		FOR (u, 1, n) {
			if (dis[u] == INF)
				continue;
			for (auto& [v, w] : edge[u])
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					flag = true;
				}
		}
		if (!flag)
			break;
	}
	return flag;
}