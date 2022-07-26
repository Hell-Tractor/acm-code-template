struct state {
  int len, link;
  int next[26];
} st[2 * MAXN];  // ! 两倍！！！！！
int sz = 0;
void init() {
  sz = 1;
  st[1].link = 0;
  st[1].len = 0;
}
void insert(string s) {
  int cur = 1;
  for (auto c : s) {
	if (!st[cur].next[c - 'a'])
	  st[cur].next[c - 'a'] = ++sz;
	cur = st[cur].next[c - 'a'];
  }
}
int extend(int c, int last) {
  int cur = st[last].next[c];
  if (st[cur].len)
	return cur;
  st[cur].len = st[last].len + 1;
  int p = st[last].link;
  while (p != 0 && !st[p].next[c]) {
	st[p].next[c] = cur;
	p = st[p].link;
  }
  if (p == 0) {
	st[cur].link = 1;
	return cur;
  }
  int q = st[p].next[c];
  if (st[p].len + 1 == st[q].len) {
	st[cur].link = q;
	return cur;
  } else {
	int clone = ++sz;
	st[clone].len = st[p].len + 1;
	for (int i = 0; i < 26; i++) {
	  if (st[st[q].next[i]].len == 0) {
		st[clone].next[i] = 0;
	  } else {
		st[clone].next[i] = st[q].next[i];
	  }
	}
	while (p != 0 && st[p].next[c] == q) {
	  st[p].next[c] = clone;
	  p = st[p].link;
	}
	st[clone].link = st[q].link;
	st[cur].link = st[q].link = clone;
	return cur;
  }
}
void build() {
  queue<paii> q;
  for (int i = 0; i < 26; i++) {
	if (st[1].next[i]) {
	  q.push({i, 1});
	}
  }
  while (!q.empty()) {
	int c = q.front().first, last = q.front().second;
	q.pop();
	last = extend(c, last);
	for (int i = 0; i < 26; i++) {
	  if (st[last].next[i]) {
		q.push({i, last});
	  }
	}
  }
}
signed main() {
  int n;
  cin >> n;
  init();
  for (int i = 1; i <= n; i++) {
	string s;
	cin >> s;
	insert(s);
  }
  build();
  return 0;
}