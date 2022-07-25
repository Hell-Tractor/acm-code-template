class zkw {
	public:
		zkw() = default;
		~zkw() = default;
		//arr[1...n]
		void make_tree(const int* arr, int n);
		void modify(int target, int val);
		int query(int left, int right);
	private:
		int* sum;
		int n, m;
};

int zkw::query(int left, int right) {
	int res = 0;
	for (left += m - 1, right += m + 1; left ^ right ^ 1; left >>= 1, right >>= 1) {
		if (~left & 1)
			res += sum[left ^ 1];
		if (right & 1)  
			res += sum[right ^ 1];
	}
	return res;
}

void zkw::make_tree(const int* arr, int n) {
	for (this->n = n, this->m = 1; this->m <= n; this->m <<= 1);
	this->sum = new int[n + m];
	for (int i = m + 1; i <= n + m; ++i)
		sum[i] = arr[i - m];
	for (int i = m - 1; i; --i)
		sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

void zkw::modify(int target, int val) {
	for (int i = (target += m); i; i >>= 1)
		sum[i] += val;
}