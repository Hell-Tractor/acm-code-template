namespace graph {
	template<int N, int M>
	class Dijkstra {
		protected:
			struct Edge {
				int to, len;
				int next;
			};
		
			int head[N];
			Edge edge[M];
			int dis[N];
			int edgeCnt;

		public:
			Dijkstra() {
				clear();
			}
			void clear() {
				memset(dis, 0x3f, sizeof(dis));
				memset(edge, 0, sizeof(edge));
				memset(head, 0, sizeof(head));
				edgeCnt = 1;
			}
			void add_edge(int from, int to, int len, bool bidirected = false) {
				edge[++edgeCnt] = Edge{to, len, head[from]};
				head[from] = edgeCnt;
				if (bidirected) {
					edge[++edgeCnt] = Edge{from, len, head[to]};
					head[to] = edgeCnt;
				}
			}
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
			int distance(const int& target) const {
				if (target > N || target < 0)
					throw std::out_of_range("target not valid");
				return dis[target];
			}
	};
}