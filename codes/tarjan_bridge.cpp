int low[MAXN], dfn[MAXN], dfc;
bool isbridge[MAXN];
vector<int> G[MAXN];
int cnt_bridge;
int father[MAXN];

void tarjan(int u, int fa) {
	father[u] = fa;
	low[u] = dfn[u] = ++dfc;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
				isbridge[v] = true;
				++cnt_bridge;
			}
		} else if (dfn[v] < dfn[u] && v != fa) {
			low[u] = min(low[u], dfn[v]);
		}
	}
}