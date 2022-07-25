char s1[N], s2[N];
int kmp[N];
void main() {
	std::cin >> s1 >> s2;
	kmp[0] = kmp[1] = 0;
	int l1 = strlen(s1), l2 = strlen(s2);
	for (int i = 1, k = 0; i < l2; ++i) {
		while (k && s2[i] != s2[k])
			k = kmp[k];
		kmp[i + 1] = s2[i] == s2[k] ? ++k : 0;
	}
	for (int i = 0, k = 0; i < l1; ++i) {
		while (k && s2[k] != s1[i])
			k = kmp[k];
		k += s2[k] == s1[i];
		if (k == l2)  // matched at i-k+2
			std::cout << i - k + 2 << std::endl;
	}
	FOR (i, 1, l2)
		std::cout << kmp[i] << ' ';
	std::cout << std::endl;
}