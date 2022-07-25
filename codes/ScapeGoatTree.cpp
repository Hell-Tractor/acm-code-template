namespace scapegoattree {

typedef const int cint;

class SGTnode {
 public:
	typedef const SGTnode cnode;
	SGTnode();
	SGTnode(cint &value, cint &count = 1);
	~SGTnode();
	inline bool NeedRebuild();
	inline void Update();
	friend class SGT;
 private:
	//0.5<=alpha<1 the larger, the faster when inserting, the slower when finding
	const static double alpha;
	SGTnode *left_child_, *right_child_;
	int value_, size_, valid_;
	bool deleted_;
};

class SGT {
 public:
	typedef const SGTnode cnode;
	const static int kINF;
	static SGTnode* null;
	SGT();
	~SGT();
	void Insert(cint &data);
	void Delete(cint &data);
	int Rank(cint &data) const;
	int Kth(cint &k) const;
	int Pre(cint &data) const;
	int Succ(cint &data) const;
 private:
	SGTnode* Build(SGTnode** num, cint &left, cint &right);
	void Dfs(SGTnode* o, SGTnode** num);
	void Rebuild(SGTnode* &o);
	void Insert(cint &data, SGTnode* &o);
	void Delete(cint &rank, SGTnode* o);

	SGTnode *root_;
	int num_cnt_;
};

} // namespace scapegoattree

#define null SGT::null

namespace scapegoattree {

const int SGT::kINF = 0x7fffffff;
const double SGTnode::alpha = 0.7;
SGTnode* SGT::null = new SGTnode(0, 0);

SGTnode::SGTnode() {
}


SGTnode::SGTnode(cint &value, cint &count) {
	left_child_ = null;
	right_child_ = null;
	value_ = value;
	size_ = valid_ = count;
	deleted_ = false;
}

SGTnode::~SGTnode() {

}

bool SGTnode::NeedRebuild() {
	if (this == null)
		return false;
	return (double)left_child_->size_ > alpha * (double)size_ ||
				 (double)right_child_->size_ > alpha * (double)size_;
}

void SGTnode::Update() {
	size_ = !deleted_ + left_child_->size_ + right_child_->size_;
	valid_ = !deleted_ + left_child_->valid_ + right_child_->valid_;
}

SGT::SGT() {
	root_ = null;
	num_cnt_= 0;
}

SGT::~SGT() {
}

SGTnode* SGT::Build(SGTnode** num, cint &left, cint &right) {
	if (left >= right)
		return null;
	int mid = (left + right) >> 1;
	SGTnode *o = num[mid];
	o->left_child_ = Build(num, left, mid);
	o->right_child_ = Build(num, mid + 1, right);
	o->Update();
	return o;
}

void SGT::Dfs(SGTnode* o, SGTnode** num) {
	if (o == null)
		return;
	Dfs(o->left_child_, num);
	if (!o->deleted_)
		num[num_cnt_++] = o;
	Dfs(o->right_child_, num);
	if (o->deleted_)
		delete o;
}

void SGT::Rebuild(SGTnode* &o) {
	SGTnode **tmp = new SGTnode*[root_->size_];
	num_cnt_ = 0;
	Dfs(o, tmp);
	o = Build(tmp, 0, num_cnt_);
	delete[] tmp;
}

void SGT::Insert(cint &data, SGTnode* &o) {
	if (o == null) {
			o = new SGTnode(data);
		return;
	}
	++o->size_;
	++o->valid_;
	if (data >= o->value_)
		Insert(data, o->right_child_);
	else
		Insert(data, o->left_child_);
	if (o->NeedRebuild())
		Rebuild(o);
}

void SGT::Delete(cint &rank, SGTnode* o) {
	if (!o->deleted_ && rank == o->left_child_->valid_ + 1) {
		o->deleted_ = true;
		--o->valid_;
		return;
	}
	--o->valid_;
	if (rank <= o->left_child_->valid_ + !o->deleted_)
		Delete(rank, o->left_child_);
	else
		Delete(rank - o->left_child_->valid_ - !o->deleted_, o->right_child_);
}

void SGT::Insert(cint &data) {
	Insert(data, root_);
}

void SGT::Delete(cint &data) {
	Delete(Rank(data), root_);
}

int SGT::Rank(cint &data) const {
	int ans = 1;
	SGTnode* o = root_;
	while (o != null) {
		if (o->value_ >= data)
			o = o->left_child_;
		else {
			ans += o->left_child_->valid_ + !o->deleted_;
			o = o->right_child_;
		}
	}
	return ans;
}

int SGT::Kth(cint &k) const {
	int k_ = k;
	SGTnode* o = root_;
	while (o != null) {
		if (!o->deleted_ && o->left_child_->valid_ + 1 == k_)
			return o->value_;
		if (o->left_child_->valid_ >= k_)
			o = o->left_child_;
		else {
			k_ -= o->left_child_->valid_ + !o->deleted_;
			o = o->right_child_;
		}
	}
	return kINF;
}

int SGT::Pre(cint &data) const {
	return Kth(Rank(data) - 1);
}

int SGT::Succ(cint &data) const {
	return Kth(Rank(data + 1));
}

} // namespace scapegoattree