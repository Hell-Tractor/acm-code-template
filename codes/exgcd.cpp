void Exgcd(const long long &a, const long long &b, long long &x, long long &y) {
  if (!b)
    x = 1, y = 0;
  else
    Exgcd(b, a % b, y, x), y -= a / b * x;
}