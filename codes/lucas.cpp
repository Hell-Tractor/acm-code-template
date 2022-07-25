void init(int p) {
  inv[1] = fac[1] = fac[0] = 1;
  for (int i = 2; i < p; i++) {
    inv[i] = ((p - p / i) * inv[p % i]) % p;
    fac[i] = (fac[i - 1] * i % p) % p;
  }
}
int c(int m, int n, int p) {
  return m < n ? 0 : ((fac[m] * inv[fac[n]]) % p * inv[fac[m - n]]) % p;
}
int lucas(int m, int n, int p) {
  return n == 0 ? 1 % p : lucas(m / p, n / p, p) * c(m % p, n % p, p) % p;
}
//大模数下求组合数逆元不用
ll inv(ll a, ll p) {
  ll x, y;
  if (exgcd(a, p, x, y) != 1)
    return -1;
  return (x % p + p) % p;
}
