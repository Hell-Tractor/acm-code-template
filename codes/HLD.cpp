const int N = 1e5 + 5;

struct Edge {
	int to;
	int next;
};


int depth[N], father[N], size[N], pson[N];
int w0[N], w[N];
int id[N], top[N];
int seg[N << 2], tag[N << 2], li[N << 2], ri[N << 2];
Edge edge[N << 1];
int head[N];
int n, m, r, mod;

void DFS1(int u, int fa);
void DFS2(int u, int topf);
int query(int x, int y);
int query(int l, int r, int now);
int query(int u);
void modify(int x, int y, int delt);
void modify(int l, int r, int delt, int now);
void modify(int u, int delt);
void add_edge(int from, int to);
void build(int l, int r, int now);
void push_down(int u);

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cin >> n >> m >> r >> mod;
	for (int i = 1; i <= n; ++i) {
		std::cin >> w0[i];
		w0[i] %= mod;
	}
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		add_edge(u, v);
	}
	DFS1(r, 0);
	DFS2(r, r);
	build(1, n, 1);
	while (m--) {
		int opt;
		std::cin >> opt;
		switch (opt) {
			int x, y, z;
			case 1:
				// add z to [x, y]
				std::cin >> x >> y >> z;
				modify(x, y, z);
				break;
			case 2:
				// query sum value of [x, y]
				std::cin >> x >> y;
				std::cout << query(x, y) << '\n';
				break;
			case 3:
				// add z to subtree of x
				std::cin >> x >> z;
				modify(x, z);
				break;
			case 4:
				// query sum value of subtree x
				std::cin >> x;
				std::cout << query(x) << '\n';
				break;
		}
	}

	return 0;
}

void push_down(int u) {
	if (!tag[u])
		return;
	seg[u << 1] = (seg[u << 1] + (ri[u << 1] - li[u << 1] + 1) * tag[u]) % mod;
	tag[u << 1] = (tag[u << 1] + tag[u]) % mod;
	seg[u << 1 | 1] = (seg[u << 1 | 1] + (ri[u << 1 | 1] - li[u << 1 | 1] + 1) * tag[u]) % mod;
	tag[u << 1 | 1] = (tag[u << 1 | 1] + tag[u]) % mod;
	tag[u] = 0;
}

void modify(int l, int r, int delt, int now) {
	if (l <= li[now] && ri[now] <= r) {
		seg[now] = (seg[now] + (ri[now] - li[now] + 1) * delt) % mod;
		tag[now] = (tag[now] + delt) % mod;
		return;
	}
	push_down(now);
	int mid = (li[now] + ri[now]) >> 1;
	if (l <= mid)
		modify(l, r, delt, now << 1);
	if (mid + 1 <= r)
		modify(l, r, delt, now << 1 | 1);
	seg[now] = (seg[now << 1] + seg[now << 1 | 1]) % mod;
}

int query(int l, int r, int now) {
	if (l <= li[now] && ri[now] <= r)
		return seg[now] % mod;
	push_down(now);
	int mid = (li[now] + ri[now]) >> 1;
	int a = 0, b = 0;
	if (l <= mid)
		a = query(l, r, now << 1);
	if (mid + 1 <= r)
		b = query(l, r, now << 1 | 1);
	return (a + b) % mod;
}

void build(int l, int r, int now) {
	li[now] = l;
	ri[now] = r;
	if (l == r) {
		seg[now] = w[l];
		return;
	}
	int mid = (l + r) >> 1;
	if (l <= mid)
		build(l, mid, now << 1);
	if (mid + 1 <= r)
		build(mid + 1, r, now << 1 | 1);
	seg[now] = (seg[now << 1] + seg[now << 1 | 1]) % mod;
	return;
}

void add_edge(int from, int to) {
	static int cnt = 1;
	edge[++cnt] = {to, head[from]};
	head[from] = cnt;
	edge[++cnt] = {from, head[to]};
	head[to] = cnt;
}

void modify(int u, int delt) {
	modify(id[u], id[u] + size[u] - 1, delt, 1);
}

void modify(int x, int y, int delt) {
	delt %= mod;
	while (top[x] != top[y]) {
		if (depth[top[x]] < depth[top[y]])
			std::swap(x, y);
		modify(id[top[x]], id[x], delt, 1);
		x = father[top[x]];
	}
	if (depth[x] < depth[y])
		std::swap(x, y);
	modify(id[y], id[x], delt, 1);
}

int query(int u) {
	return query(id[u], id[u] + size[u] - 1, 1);
}

int query(int x, int y) {
	int res = 0;
	while (top[x] != top[y]) {
		if (depth[top[x]] < depth[top[y]])
			std::swap(x, y);
		res += query(id[top[x]], id[x], 1);
		res %= mod;
		x = father[top[x]];
	}
	if (depth[x] < depth[y])
		std::swap(x, y);
	return (res + query(id[y], id[x], 1)) % mod;
}

void DFS2(int u, int topf) {
	static int cnt = 0;
	id[u] = ++cnt;
	w[cnt] = w0[u];
	top[u] = topf;
	if (!pson[u])
		return;
	DFS2(pson[u], topf);
	for (int i = head[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (v != father[u] && v != pson[u])
			DFS2(v, v);
	}
}

void DFS1(int u, int fa) {
	depth[u] = depth[father[u] = fa] + 1;
	size[u] = 1;
	int maxSon = -1;
	for (int i = head[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (fa != v) {
			DFS1(v, u);
			size[u] += size[v];
			if (size[v] > maxSon) {
				pson[u] = v;
				maxSon = size[v];
			}
		}
	}
}