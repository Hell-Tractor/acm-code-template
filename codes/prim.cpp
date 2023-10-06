int dis[N];
vector<pair<int, int>> edge[N];
bool exist[N];
int n, m;

int prim() {
  memset(dis, 0x7f / 3, sizeof(dis));
  int cnt = 0, ans = 0;
  dis[1] = 0;
  priority_queue<pii, vector<pii>, greater<pii>> q;
  q.emplace(0, 1);
  while (!q.empty() && cnt < n) {
    auto [len, u] = q.top();
    q.pop();
    if (!exist[u]) {
      cnt++;
      ans += len;
      exist[u] = true;
      for (auto& [v, w] : edge[u])
        if (w < dis[v]) {
          dis[v] = w;
          q.emplace(dis[v], v);
        }
    }
  }
  return ans;
}