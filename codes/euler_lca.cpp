int n, q, s, depth[N << 1];
int lg[N << 1], dfn[N << 1], pos[N], tot, st[30][(N << 1) + 2], rev[30][(N << 1) + 2];

// 求欧拉序，注意数组要开二倍
void dfs(int cur, int dep) {
    dfn[++tot] = cur;
    depth[tot] = dep;
    pos[cur] = tot;
    for (auto v : e[cur])
        if (!pos[v]) {
            dfs(v, dep + 1);
            dfn[++tot] = cur, depth[tot] = dep;
        }
}

void init() {
    for (int i = 2; i <= tot + 1; ++i) lg[i] = lg[i >> 1] + 1;
    // ST表维护区间最值
    for (int i = 1; i <= tot; i++) st[0][i] = depth[i], rev[0][i] = dfn[i];
    for (int i = 1; i <= lg[tot]; i++)
        for (int j = 1; j + (1 << i) - 1 <= tot; j++)
            if (st[i - 1][j] < st[i - 1][j + (1 << i - 1)]) st[i][j] = st[i - 1][j], rev[i][j] = rev[i - 1][j];
            else {
                st[i][j] = st[i - 1][j + (1 << i - 1)];
                rev[i][j] = rev[i - 1][j + (1 << i - 1)];
            }
}

int query(int l, int r) {
    int k = lg[r - l + 1];
    return st[k][l] < st[k][r + 1 - (1 << k)] ? rev[k][l] : rev[k][r + 1 - (1 << k)];
}

int LCA(int u, int v) {
    return query(min(pos[u], pos[v]), max(pos[u], pos[v]));
}