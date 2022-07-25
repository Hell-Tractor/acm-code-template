// return: $a ^ b \% mod$
ll qpower(ll a, ll b, ll mod) {
	ll base = a, res = 1;
	while (b) {
		if (b & 1)
			res = res * base % mod;
		base = base * base % mod;
		b >>= 1;
	}
	return res % mod;
}