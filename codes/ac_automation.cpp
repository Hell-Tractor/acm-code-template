void insert(string &s, int i) {
	int u = 0;
	for (auto c : s) {
		if (!tr[u][c - 'a']) {
			tr[u][c - 'a'] = ++cnt;
		}
		u = tr[u][c - 'a'];
	}
	match[i] = u;
}
queue<int> q;
void build() {
	for (int i = 0; i < 26; i++) {
		if (tr[0][i]) {
			q.push(tr[0][i]);
		}
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < 26; i++) {
			if (tr[u][i]) {
				fail[tr[u][i]] = tr[fail[u]][i];
				in[fail[tr[u][i]]]++;
				q.push(tr[u][i]);
			} else {
				tr[u][i] = tr[fail[u]][i];
			}
		}
	}
}
void topo() {
	for (int i = 0; i <= cnt; i++) {
		if (in[i] == 0) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		in[fail[u]]--;
		val[fail[u]] += val[u];
		if (in[fail[u]] == 0) {
			q.push(fail[u]);
		}
	}
}
void query(string &s) {
	int u = 0;
	for (auto c : s) {
		u = tr[u][c - 'a'];
		val[u]++;
	}
}
