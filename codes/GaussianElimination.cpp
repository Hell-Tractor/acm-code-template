double a[105][105];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, cur = 1, ct1 = 0, ct2 = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n + 1; j++) {
			cin >> a[i][j];
		}
	}
	for (int j = 1; j <= n + 1; j++) {
		int i;
		for (i = cur; i <= n; i++) {
			if (a[i][j])
				break;
		}
		if (abs(a[i][j]) < eps)
			continue;
		for (int k = 1; k <= n + 1; k++) {
			swap(a[i][k], a[cur][k]);
		}
		for (int k = n + 1; k >= j; k--) {
			a[cur][k] /= a[cur][j];
		}
		for (int i = 1; i <= n; i++) {
			if (i != cur) {
				for (int k = n + 1; k >= j; k--) {
					a[i][k] -= a[cur][k] * a[i][j];
				}
			}
		}
		cur++;
	}
	for (int i = 1; i <= n; i++) {
		int flag = 1;
		for (int j = 1; j <= n; j++) {
			if (abs(a[i][j]) > eps) {
				flag = 0;
			}
		}
		ct1 += !flag;
		ct2 += !flag || a[i][n + 1];
	}
	if (ct1 != ct2) {
		cout << '-' << '1';  //无解
	} else if (ct1 == ct2 && ct1 < n) {
		cout << '0';  //无数解
	} else {
		for (int i = 1; i <= n; i++) {
			printf("x%d=%.2lf\n", i, a[i][n + 1]);
		}
	}
	return 0;
}
