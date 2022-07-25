#include <queue>

using std::queue;

namespace tree {

template<int N>
class splay {
 public:
	typedef const int cint;
	typedef int node;
	typedef const node cnode;
	splay();
	~splay();
	int key(cnode &num) const;
	// 插入
	virtual void insert(cint &x);
	// 查询第k个元素
	virtual node Kth(int k) const;
	// 查询排名
	int Rank(cint &x);
	// 查询前驱
	node Pre(cint &x);
	// 查询后继
	node Succ(cint &x);
	// 删除
	void Remove(cint &x);

 private:
	int CheckDir(cint &x) const;
	void PushUp(cint &x);
	void Rotate(cint &x);
	void Find(cint &x);
	void Recycle(cnode &x);

	queue<node> trash_;

 protected:
	node NewNode();
	void Splay(cint &x, cint &goal = 0);
	
	int count_[N];
	//节点N下节点个数（重复只计1
	int size_[N];
	int father_[N];
	int key_[N];
	int child_[N][2];
	int root_;
	int nodecnt_;
};

} // namespace tree

namespace tree {

template<int N>
class SeqSplay : public splay<N> {
 public:
	typedef const int cint;
	typedef int node;
	typedef const node cnode;
	SeqSplay();
	~SeqSplay();
	// 反转区间$[left, right]$
	void Reverse(cint &left, cint &right);
	// 在x位置插入data
	virtual void insert(cint &x, cint &data);
	// 查询第k大的数
	virtual node Kth(int k);
	// 获取当前序列
	int* Sequence(int *size);
 
 private:
	void PushDown(cnode &x);
	void MidOrder(cnode &x, int* buffer, int *cnt);

	bool reverse_[N];
	int data_[N];
};

} // namespace tree

#include <cstring>

namespace tree {

template<int N>
splay<N>::splay() {
	nodecnt_ = 0;
	root_ = 0;
	memset(child_, 0, sizeof(child_));
	memset(key_, 0, sizeof(key_));
	memset(count_, 0, sizeof(count_));
	memset(father_, 0, sizeof(father_));
	memset(size_, 0, sizeof(size_));
	insert(0x7fffffff);
	insert(0x80000000);
}

template<int N>
splay<N>::~splay() {
}

template<int N>
int splay<N>::CheckDir(cint &x) const {
	return child_[father_[x]][1] == x;
}

template<int N>
void splay<N>::PushUp(cint &x) {
	size_[x] = size_[child_[x][0]] + size_[child_[x][1]] + count_[x];
}

template<int N>
void splay<N>::Rotate(cint &x) {
	int father = father_[x], gfather = father_[father];
	int dir = CheckDir(x);
	int son = child_[x][dir ^ 1];
	child_[father][dir] = son;
	father_[son] = father;
	child_[gfather][CheckDir(father)] = x;
	father_[x] = gfather;
	child_[x][dir ^ 1] = father;
	father_[father] = x;
	PushUp(father);
	PushUp(x);
}

template<int N>
void splay<N>::Splay(cint &x, cint &goal) {
	while (father_[x] != goal) {
		int father = father_[x], gfather = father_[father];
		if (gfather != goal) {
			if (CheckDir(x) == CheckDir(father))
				Rotate(father);
			else
				Rotate(x);
		}
		Rotate(x);
	}
	if (!goal)
		root_ = x;
}

template<int N>
void splay<N>::Find(cint &x) {
	int cur = root_;
	while (child_[cur][x > key_[cur]] && x != key_[cur])
		cur = child_[cur][x > key_[cur]];
	Splay(cur);
}

template<int N>
typename splay<N>::node splay<N>::NewNode() {
	int cur;
	if (trash_.empty())
		cur = ++nodecnt_;
	else {
		cur = trash_.front();
		trash_.pop();
	}
	return cur;
}

template<int N>
void splay<N>::Recycle(cnode &x) {
	trash_.push(x);
}

template<int N>
int splay<N>::key(cnode &num) const{
	return key_[num];
}

template<int N>
void splay<N>::insert(cint &x) {
	int cur = root_, father = 0;
	while (cur && key_[cur] != x) {
		father = cur;
		cur = child_[cur][x > key_[cur]];
	}
	if (cur)
		count_[cur]++;
	else {
		cur = NewNode();
		if (father)
			child_[father][x > key_[father]] = cur;
		child_[cur][0] = child_[cur][1] = 0;
		key_[cur] = x;
		father_[cur] = father;
		count_[cur] = size_[cur] = 1;
	}
	Splay(cur);
}

template<int N>
typename splay<N>::node splay<N>::Kth(int k) const{
	k++;
	int cur = root_;
	while (1) {
		if (child_[cur][0] && k <= size_[child_[cur][0]]) {
			cur = child_[cur][0];
		} else if (k > size_[child_[cur][0]] + count_[cur]) {
			k -= size_[child_[cur][0]] + count_[cur];
			cur = child_[cur][1];
		} else
			return cur;
	}
}

template<int N>
int splay<N>::Rank(cint &x) {
	Find(x);
	if (key_[root_] >= x)
		return size_[child_[root_][0]];
	else
		return size_[child_[root_][0]] + count_[root_];
}

template<int N>
typename splay<N>::node splay<N>::Pre(cint &x) {
	Find(x);
	if (key_[root_] < x)
		return root_;
	int cur = child_[root_][0];
	while (child_[cur][1])
		cur = child_[cur][1];
	return cur;
}

template<int N>
typename splay<N>::node splay<N>::Succ(cint &x) {
	Find(x);
	if (key_[root_] > x)
		return root_;
	int cur = child_[root_][1];
	while (child_[cur][0])
		cur = child_[cur][0];
	return cur;
}

template<int N>
void splay<N>::Remove(cint &x) {
	node last = Pre(x), next = Succ(x);
	Splay(last);
	Splay(next, last);
	node del = child_[next][0];
	if (count_[del] > 1) {
		count_[del]--;
		Splay(del);
	} else {
		Recycle(child_[next][0]);
		child_[next][0] = 0;
		PushUp(next);
		PushUp(root_);
	}
}

} // namespace tree

namespace tree {

template<int N>
SeqSplay<N>::SeqSplay() : splay<N>() {
	memset(reverse_, false, sizeof(reverse_));
	memset(data_, 0, sizeof(data_));
}

template<int N>
SeqSplay<N>::~SeqSplay() {
}

template<int N>
void SeqSplay<N>::PushDown(cnode &x) {
	if (reverse_[x]) {
		std::swap(this->child_[x][0], this->child_[x][1]);
		reverse_[this->child_[x][0]] ^= 1;
		reverse_[this->child_[x][1]] ^= 1;
		reverse_[x] = false;
	}
}

template<int N>
void SeqSplay<N>::Reverse(cint &left, cint &right) {
	int x = this->Kth(left - 1), y = this->Kth(right + 1);
	this->Splay(x);
	this->Splay(y, x);
	reverse_[this->child_[y][0]] ^= 1;
}

template<int N>
void SeqSplay<N>::insert(cint &x, cint &data) {
	int cur = this->root_, father = 0;
	while (cur && this->key_[cur] != x) {
		father = cur;
		cur = this->child_[cur][x > this->key_[cur]];
	}
	if (cur)
		this->count_[cur]++;
	else {
		cur = this->NewNode();
		if (father)
			this->child_[father][x > this->key_[father]] = cur;
		this->child_[cur][0] = this->child_[cur][1] = 0;
		this->key_[cur] = x;
		data_[cur] = data;
		this->father_[cur] = father;
		this->count_[cur] = this->size_[cur] = 1;
	}
	this->Splay(cur);
}

template<int N>
typename SeqSplay<N>::node SeqSplay<N>::Kth(int k) {
	k++;
	int cur = this->root_;
	while (1) {
		this->PushDown(cur);
		if (this->child_[cur][0] && k <= this->size_[this->child_[cur][0]]) {
			cur = this->child_[cur][0];
		} else if (k > this->size_[this->child_[cur][0]] + this->count_[cur]) {
			k -= this->size_[this->child_[cur][0]] + this->count_[cur];
			cur = this->child_[cur][1];
		} else
			return cur;
	}
}

template<int N>
void SeqSplay<N>::MidOrder(cnode &x, int *buffer, int *cnt) {
	this->PushDown(x);
	if (this->child_[x][0])
		MidOrder(this->child_[x][0], buffer, cnt);
	if (this->key_[x] > (int)0x80000000 && this->key_[x] < (int)0x7fffffff)
		buffer[(*cnt)++] = data_[x];
	if (this->child_[x][1])
		MidOrder(this->child_[x][1], buffer, cnt);
}

template<int N>
int* SeqSplay<N>::Sequence(int *size) {
	int *tmp = new int[this->nodecnt_];
	*size = 0;
	MidOrder(this->root_, tmp, size);
	return tmp;
}

} // namespace tree