int low[maxN], dfn[maxN], dfc;
int stk[maxN], top;
int scc[maxN], cnt;
void Tarjan(int u) {
	low[u] = dfn[u] = ++dfc;
	stk[++top] = u;
	for (int i = G::head[u]; i; i = G::edge[i].next) {
		int v = G::edge[i].to;
		if (!dfn[v])  // 延伸路径
			Tarjan(v), low[u] = min(low[u], low[v]);
		else if (!scc[v])  // 通过反向边回到路径 v必须在路径上
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		scc[u] = ++cnt;
		while (stk[top] != u)
			scc[stk[top--]] = cnt;
		top--;
	}
}
