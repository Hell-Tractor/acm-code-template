#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-x))
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<int, int> paii;
const int inf = 1e9;
struct node1 {
	int l, r, time, id;
} q[2500005];
struct node2 {
	int pos, col;
} c[2500005];
int a[2500005], ans[2500005], cnt[2500005], sq, cntq = 0, cntc = 0, cur = 0;
bool cmp(node1 a, node1 b) {
	if (a.l / sq != b.l / sq)
		return a.l < b.l;
	else if (a.r / sq != b.r / sq) {
		if ((a.l / sq) % 2)
			return a.r < b.r;
		else
			return a.r > b.r;
	} else
		return a.time < b.time;
}
void add(int p) {
	cnt[a[p]]++;
	if (cnt[a[p]] == 1)
		cur++;
}
void del(int p) {
	cnt[a[p]]--;
	if (cnt[a[p]] == 0)
		cur--;
}
void update(int time, int i) {
	if (c[time].pos >= q[i].l && c[time].pos <= q[i].r) {
		if (--cnt[a[c[time].pos]] == 0)
			cur--;
		if (++cnt[c[time].col] == 1)
			cur++;
	}
	swap(c[time].col, a[c[time].pos]);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	sq = (int)pow(n, 2.0 / 3.0);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= m; i++) {
		char op;
		cin >> op;
		if (op == 'Q') {
			cntq++;
			cin >> q[cntq].l >> q[cntq].r;
			q[cntq].time = cntc;
			q[cntq].id = cntq;
		} else {
			cntc++;
			cin >> c[cntc].pos >> c[cntc].col;
		}
	}
	sort(q + 1, q + 1 + cntq, cmp);
	int l = 1, r = 0, time = 0;
	for (int i = 1; i <= cntq; i++) {
		while (l > q[i].l)
			add(--l);
		while (r < q[i].r)
			add(++r);
		while (l < q[i].l)
			del(l++);
		while (r > q[i].r)
			del(r--);
		while (time < q[i].time)
			update(++time, i);
		while (time > q[i].time)
			update(time--, i);
		ans[q[i].id] = cur;
	}
	for (int i = 1; i <= cntq; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}
