namespace tree {

template<class T, int N, T (*cmp)(const T&, const T&)>
class segment_tree {
	public:
		typedef const int cint;

		class node {
			private:
				int left, right;
			public:
				T data;

				friend class segment_tree;
		};

		void make_tree(cint& left, cint& right, const T* num, cint& now);
		T query(cint& left, cint& right, cint& now) const;
	private:
		node nodes[N];
};

template<class T, int N, T (*cmp)(const T&, const T&)>
T segment_tree<T, N, cmp>::query(cint& left, cint& right, cint& now) const {
	if (nodes[now].left >= left && nodes[now].right <= right)
		return nodes[now].data;
	int mid = (nodes[now].left + nodes[now].right) >> 1;
	T a, b;
	int state = 0;
	if (left <= mid)
		state |= 0b10, a = this->query(left, right, now << 1);
	if (right > mid)
		state |= 0b01, b = this->query(left, right, (now << 1) | 1);
	return state == 0b11 ? cmp(a, b) : (state & 0b01) ? b : a;
}

template<class T, int N, T (*cmp)(const T&, const T&)>
void segment_tree<T, N, cmp>::make_tree(cint& left, cint& right, const T* num, cint& now) {
	nodes[now].left = left, nodes[now].right = right;
	if (left == right) {
		nodes[now].data = num[left];
		return;
	}
	int mid = (left + right) >> 1;
	this->make_tree(left, mid, num, now << 1);
	this->make_tree(mid + 1, right, num, (now << 1) | 1);
	nodes[now].data = cmp(nodes[now << 1].data, nodes[(now << 1) | 1].data);
	return;
}

} //tree