int cnt[N];		// * 初始值为0
vector<Edge> edge[N];
vector<int> ans;
void Hierholzer(int x) {
	for (int& i = cnt[x]; i < (int)edge[x].size();) {
		if (edge[x][i].exists) {  // 标记边是否走过
			edge e = edge[x][i];
			edge[x][i].exists = 0;
			edge[e.to][e.revref].exists = 0;  // 同时标记反向边
			++i;
			Hierholzer(e.to);
		} else {
			++i;
		}
	}
	ans.push(x);
}