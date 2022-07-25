for (int i = 1; i <= n; i++) {
  scanf("%d", &f[i][0]);
}
for (int i = 1; i <= 21; i++)
  for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
    f[j][i] = max(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);
  }
for (int i = 2; i <= n; i++) {
  log2[i] = log2[i / 2] + 1;
}
for (int i = 1; i <= m; i++) {
  int l, r;
  scanf("%d %d", &l, &r);
  int s = log2[r - l + 1];
  printf("%d\n", max(f[l][s], f[r - (1 << s) + 1][s]));
}
