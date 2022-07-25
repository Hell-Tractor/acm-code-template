void init() {
  str[0] = '#';
  char ch = getchar();
  while (isalpha(ch)) {
    str[++cnt] = ch;
    str[++cnt] = '#';
    ch = getchar();
  }
  str[++cnt] = '\0';
}
int l = 0, r = -1;
for (int i = 0; i < cnt; i++) {
  int k = i > r ? 1 : min(r - i, d[l + r - i]);
  while (i - k >= 0 && i + k < cnt && str[i - k] == str[i + k])
    k++;
  k--;
  d[i] = k;
  if (i + k > r) {
    r = i + k;
    l = i - k;
  }
  ans = max(ans, d[i]);
}
