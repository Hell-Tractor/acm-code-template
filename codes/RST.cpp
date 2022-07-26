vector<int> edge[N]
// ! 圆方树点数是原图二倍
vector<int> T[N << 1];
int low[N], dfn[N], dfc;
int stk[N], top;
// * 圆点数，方点数
int n, cnt;

void Tarjan(int u) {
    low[u] = dfn[u] = ++dfc;
    stk[++top] = u;
    range (v, edge[u]) {
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u]) {
                ++cnt;
                for (int x = 0; x != v; --top) {
                    x = stk[top];
                    T[cnt].push_back(x);
                    T[x].push_back(cnt);
                }
                T[cnt].push_back(u);
                T[u].push_back(cnt);
            }
        } else
            low[u] = min(low[u], dfn[v]);
    }
}

int main() {
    FOR (i, 1, g.n)
        if (!g.dfn[i])
            g.Tarjan(i, true), --g.top; // ! 退出时要将i点退栈
}