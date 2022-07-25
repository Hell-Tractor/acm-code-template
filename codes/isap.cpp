namespace graph {
	template <int N, int M>
	class ISAP {
		public:
			typedef const int cint;
			const static int INF;

			void add_edge(cint& from, cint& to, cint& size, bool bidirect = false);
			// * parameter: 源点，汇点，总点数（可多）
			int exec(cint& start, cint& target, cint& node_cnt);
		protected:
			struct node {
				int to, size;
				int next;
			};

			int s, t, n;
			int max_flow;
			int head[N], gap[N], depth[N], cur[N];
			node edge[M];
			
			void BFS();
			int DFS(cint& now, cint& flow);
	};
	template <int N, int M>
	const int ISAP<N, M>::INF = 1 << 30;

	template <int N, int M>
	inline int ISAP<N, M>::exec(cint& start, cint& target, cint& node_cnt) {
		max_flow = 0;
		s = start, t = target, n = node_cnt;
		BFS();
		while (depth[s] < n) {
			memcpy(cur, head, sizeof(head));
			DFS(s, 1 << 30);
		}
		return max_flow;
	}
	
	template <int N, int M>
	int ISAP<N, M>::DFS(cint& now, cint& flow) {
		if (now == t) {
			max_flow += flow;
			return flow;
		}
		int used = 0, rflow = 0;
		for (int i = cur[now]; i; i = edge[i].next) {
			cur[now] = i;
			node &e = edge[i];
			node &_e = edge[i ^ 1];
			if (e.size && depth[e.to] + 1 == depth[now] && (rflow = DFS(e.to, std::min(flow - used, e.size)))) {
				e.size -= rflow;
				_e.size += rflow;
				used += rflow;
				if (used == flow)
					return used;
			}
		}
		if (!--gap[depth[now]])
			depth[s] = n + 1;
		gap[++depth[now]]++;
		return used;
	}

	template <int N, int M>
	void ISAP<N, M>::BFS() {
		memset(depth, -1, sizeof(depth));
		memset(gap, 0, sizeof(gap));
		std::queue<int> q;
		q.push(t);
		depth[t] = 0;
		gap[0] = 1;
		while (!q.empty()) {
			int tmp = q.front();
			q.pop();
			for (int i = head[tmp]; i; i = edge[i].next) {
				node &e = edge[i];
				if (depth[e.to] != -1)
					continue;
				q.push(e.to);
				depth[e.to] = depth[tmp] + 1;
				gap[depth[e.to]]++;
			}
		}
	}

	template <int N, int M>
	inline void ISAP<N, M>::add_edge(cint& from, cint& to, cint& size, bool bidirect) {
		static int cnt = 1;
		edge[++cnt] = node{to, size, head[from]};
		head[from] = cnt;
		edge[++cnt] = node{from, bidirect ? size : 0, head[to]};
		head[to] = cnt;
	}
} // namespace graph