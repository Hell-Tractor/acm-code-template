struct state {
	int len, link;
	int next[26];
} st[2 * MAXN];  // ! 两倍！！！！！
void init() {
	sz = 1;
	st[sz].len = 0;
	st[sz].link = 0;
	last = 1;
}
void extend(char c) {
	int cur = ++sz;
	val[cur] = 1;
	st[cur].len = st[last].len + 1;
	int p = last;
	while (p != 0 && !st[p].next[c - 'a']) {
		st[p].next[c - 'a'] = cur;
		p = st[p].link;
	}
	if (p == 0) {
		st[cur].link = 1;
	} else {
		int q = st[p].next[c - 'a'];
		if (st[p].len + 1 == st[q].len) {
			st[cur].link = q;
		} else {
			int clone = ++sz;
			st[clone].len = st[p].len + 1;
			for (int i = 0; i < 26; i++) {
				st[clone].next[i] = st[q].next[i];
			}
			st[clone].link = st[q].link;
			while (p != 0 && st[p].next[c - 'a'] == q) {
				st[p].next[c - 'a'] = clone;
				p = st[p].link;
			}
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}