struct Edge {
	int to, len;
	int next;
};

int head[N];
Edge edge[M];
int dis[N];

void exec(const int &s) {
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
	dis[s] = 0;
	for (q.push({0, s}); !q.empty();) {
		auto u = q.top();
		q.pop();
		if (u.first != dis[u.second])
			continue;
		for (int i = head[u.second]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (dis[v] > dis[u.second] + edge[i].len) {
				dis[v] = dis[u.second] + edge[i].len;
				q.push({dis[v], v});
			}
		}
	}
}