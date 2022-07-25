int low[maxN], dfn[maxN], dfc;
bool isCut[maxN];
void Tarjan(int u, bool isRoot = false) {
	low[u] = dfn[u] = ++dfc;
	int child = 0;
	for (int i = G::head[u]; i; i = G::edge[i].next) {
		int v = G::edge[i].to;
		if (!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
			if (!isRoot && low[v] >= dfn[u])
				isCut[u] = true;
			if (isRoot)
				child++;
		} else
			low[u] = min(low[u], dfn[v]);
	}
	if (isRoot && child >= 2)
		isCut[u] = true;
}
