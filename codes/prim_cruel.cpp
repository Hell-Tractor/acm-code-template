const int INF = INT64_MAX;
int dis[N];
bool exist[N];
vector<pii> edge[N];
int n, m;

int prim() {
	exist[1] = true;
	int ans = 0;
	for (int count = 0; count < n - 1; count++) {
		int minn = INF, u = -1;
		for (int i = 1; i <= n; i++)
			if (!exist[i] && dis[i] < minn) {
				minn = dis[i];
				u = i;
			}
		ans += minn;
		for (auto& [v, w] : edge[u])
			if (dis[v] > w && !exist[v])
				dis[v] = w;
		exist[u] = true;
	}
	return ans;
}