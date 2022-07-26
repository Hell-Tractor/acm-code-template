ll crt(ll n) {
	ll p = 1, x = 0;
	for (int i = 1; i <= n; i++) {
		p *= a[i];
	}
	for (int i = 1; i <= n; i++) {
		ll r = p / a[i];
		x += (b[i] * r * inv(r, a[i])) % p;
	}
	return x % p;
}
