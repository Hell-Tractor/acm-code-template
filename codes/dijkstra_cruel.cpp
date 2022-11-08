const int INF = INT64_MAX / 3;
vector<pii> e[N];
int dis[N], vis[N];

void dijkstra(int s) {
	fill(dis, dis + n + 1, INF);
	dis[s] = 0;
	for (int i = 1; i <= n; i++) {
		int u = 0, mind = INF;
		for (int j = 1; j <= n; j++)
			if (!vis[j] && dis[j] < mind) {
				u = j;
				mind = dis[j];
			}
		vis[u] = true;
		for (auto& [v, w] : e[u])
    		if (dis[v] > dis[u] + w)
    			dis[v] = dis[u] + w;
	}
}