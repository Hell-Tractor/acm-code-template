vector<int> primes;
int phi[400005];
bool isnp[400005];
void init(int n) {
  phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isnp[i]) {
      primes.push_back(i);
      phi[i] = i - 1;
    }
    for (auto p : primes) {
      if (p * i > n)
        break;
      isnp[p * i] = 1;
      if (i % p == 0) {
        phi[p * i] = phi[i] * p;
        break;
      } else
        phi[p * i] = phi[p] * phi[i];
    }
  }
}
