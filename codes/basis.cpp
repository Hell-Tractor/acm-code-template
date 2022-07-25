vector<ull> b;
void Insert(ull x) {
  for (auto c : b) {
    x = min(x, c ^ x);
  }
  for (auto &c : b) {
    c = min(c, c ^ x);
  }
  if (x)
    b.push_back(x);
}
int main() {
  int n;
  ull ans = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    ull x;
    cin >> x;
    Insert(x);
  }
  for (auto c : b) {
    ans ^= c;
  }
  cout << ans;
  return 0;
}
