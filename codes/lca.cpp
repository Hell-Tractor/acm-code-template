const int N = 5e5 + 5;
const int M = 5e5 + 5;
constexpr const int LGN = std::log2(N) + 1;

struct Edge {
	int to, next;
};

int head[N], lg2[N];
Edge edge[M << 1];
int father[N][LGN], depth[N];
int n, m, s;

void add_edge(int from, int to);
void DFS(int now, int fa);
int LCA(int x, int y);

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cin >> n >> m >> s;
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		std::cin >> u >> v;
		add_edge(u, v);
	}
	for (int i = 2; i <= n; ++i) lg2[i] = lg2[i - 1] + !(i & (i - 1));
	DFS(s, 0);
	while (m--) {
		int x, y;
		std::cin >> x >> y;
		std::cout << LCA(x, y) << std::endl;
	}
	return 0;
}

int LCA(int x, int y) {
	if (depth[x] < depth[y]) std::swap(x, y);
	while (depth[x] > depth[y]) x = father[x][lg2[depth[x] - depth[y]]];
	if (x == y) return x;
	for (int k = lg2[depth[x]]; ~k; --k)
		if (father[x][k] != father[y][k]) x = father[x][k], y = father[y][k];
	return father[x][0];
}

void DFS(int now, int fa) {
	depth[now] = depth[fa] + 1;
	father[now][0] = fa;
	for (int i = 1; i <= lg2[depth[now]]; ++i)
		father[now][i] = father[father[now][i - 1]][i - 1];
	for (int i = head[now]; i; i = edge[i].next)
		if (edge[i].to != fa) DFS(edge[i].to, now);
}

inline void add_edge(int from, int to) {
	static int cnt = 1;
	edge[++cnt] = {to, head[from]};
	head[from] = cnt;
	edge[++cnt] = {from, head[to]};
	head[to] = cnt;
}