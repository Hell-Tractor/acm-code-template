const int N = 3e3 + 5;
const int INF = 1000000000;
vector<pii> edge[N];
int h[N], dis[N][N];
int n, m;

bool bellmanford(int s) {
	fill(h, h + n + 1, INF);
	h[s] = 0;
	bool flag;
	For (i, 0, n) {
		flag = false;
		FOR (u, 1, n) {
			if (h[u] == INF)
				continue;
			for (auto& [v, w] : edge[u])
				if (h[v] > h[u] + w) {
					h[v] = h[u] + w;
					flag = true;
				}
		}
		if (!flag)
			break;
	}
	return flag;
}

void dijkstra(int s) {
	fill(dis[s], dis[s] + n + 1, INF);
	priority_queue<pii, vector<pii>, greater<pii>> q;
	dis[s][s] = 0;
	q.emplace(0, s);
	while (!q.empty()) {
		auto [d, u] = q.top();
		q.pop();
		if (d != dis[s][u])
			continue;
		for (auto& [v, w] : edge[u])
			if (dis[s][v] > dis[s][u] + w) {
				dis[s][v] = dis[s][u] + w;
				q.emplace(dis[s][v], v);
			}
	}
}

void Johnson() {
	// 建立超级源点
	FOR (i, 1, n)
		edge[n + 1].emplace_back(i, 0);
	n++;
	// 判断是否有负环并计算势能
	if (bellmanford(n)) {
		cout << "-1\n";
		return;
	}
	// 应用势能
	FOR (u, 1, n)
		for (auto& [v, w] : edge[u])
			w += h[u] - h[v];
	// 跑最短路
	FOR (u, 1, n)
		dijkstra(u);
	// 移除势能影响
	FOR (u, 1, n)
		FOR (v, 1, n)
			if (dis[u][v] != INF)   // ! 无法到达点的距离不修改
				dis[u][v] += h[v] - h[u];
}