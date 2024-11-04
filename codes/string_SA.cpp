int rk[MAXN << 1], sa[MAXN << 1], tmp[MAXN << 1], cnt[MAXN], rkt[MAXN];
int ht[MAXN];
void init_sa(string s, int n) {  //字符串下标从1开始
	if (n == 1)
		return void(rk[1] = sa[1] = 1);

	int m = 128;
	for (int i = 1; i <= n; ++i)
		++cnt[rk[i] = s[i]];
	for (int i = 1; i <= m; ++i)
		cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i)
		sa[cnt[rk[i]]--] = i;

	for (int w = 1;; w <<= 1) {
		for (int i = n; i > n - w; --i)
			tmp[n - i + 1] = i;
		for (int i = 1, p = w; i <= n; ++i)
			if (sa[i] > w)
				tmp[++p] = sa[i] - w;
		fill(cnt + 1, cnt + m + 1, 0);
		for (int i = 1; i <= n; ++i)
			cnt[rkt[i] = rk[tmp[i]]]++;
		for (int i = 1; i <= m; ++i)
			cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; --i)
			sa[cnt[rkt[i]]--] = tmp[i];
		m = 0;
		auto rp = [&](int x) {
			return make_pair(rk[x], rk[x + w]);
		};
		for (int i = 1; i <= n; ++i)
			tmp[sa[i]] = rp(sa[i - 1]) == rp(sa[i]) ? m : ++m;
		copy(tmp + 1, tmp + n + 1, rk + 1);
		if (n == m)
			break;
	}
}
void init_ht(string s, int n) {  //字符串下标从1开始
	for (int i = 1, k = 0; i <= n; ++i) {
		if (k > 0)
			--k;
		while (s[i + k] == s[sa[rk[i] - 1] + k])
			++k;
		ht[rk[i]] = k;
	}
}