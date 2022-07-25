class node{
private:
	int data,count,priority,size;
	node *left_child,*right_child;
public:
	friend class Treap;
	node(int x);
};
class Treap{
private:
	void delete_tree(node* &pos);
	void update(node* &pos);
	void Zig(node* &pos);
	void Zag(node* &pos);
public:
	node* root;
	Treap();
	~Treap();
	// 插入data
	void insert(const int &data, node* &pos);
	// 删除data
	void remove(const int &data, node* &pos);
	// 获取data前驱
	int pre(const int &data);
	// 获取data后继
	int sub(const int &data);
	// 获取排名为rank的数据
	int data(const int &rank);
	// 查询data的排名
	int rank(const int &data);
};

#include <cstdlib>
node::node(int x){
	data=x;
	count=1;
	priority=rand();
	size=1;
	left_child=right_child=NULL;
}
#include <ctime>
Treap::Treap(){
	root=NULL;
	srand((unsigned)time(NULL));
}
Treap::~Treap(){
	delete_tree(root);
}
void Treap::delete_tree(node* &pos){
	if(pos){
		delete_tree(pos->left_child);
		delete_tree(pos->right_child);
		delete pos;
	}
}
void Treap::update(node* &pos){
	pos->size=pos->count;
	if(pos->left_child)
		pos->size+=pos->left_child->size;
	if(pos->right_child)
		pos->size+=pos->right_child->size;
}
void Treap::Zig(node* &pos){
	if(!pos)
		return;
	node* tmp=pos->left_child;
	pos->left_child=tmp->right_child;
	tmp->right_child=pos;
	tmp->size=pos->size;
	update(pos);
	pos=tmp;
}
void Treap::Zag(node* &pos){
	if(!pos)
		return;
	node* tmp=pos->right_child;
	pos->right_child=tmp->left_child;
	tmp->left_child=pos;
	tmp->size=pos->size;
	update(pos);
	pos=tmp;
}
void Treap::insert(const int &data, node* &pos){
	if(!pos){
		pos=new node(data);
		return;
	}
	else
		pos->size++;
	if(data==pos->data)
		pos->count++;
	else if(data<pos->data){
		insert(data, pos->left_child);
		if(pos->left_child->priority<pos->priority)
			Zig(pos);
	}
	else{
		insert(data, pos->right_child);
		if(pos->right_child->priority<pos->priority)
			Zag(pos);
	}
}
void Treap::remove(const int &data, node* &pos){
	if(!pos)
		return;
	if(data==pos->data){
		if(pos->count>1)
			pos->count--,pos->size--;
		else if(!pos->left_child&&!pos->right_child){
			delete pos;
			pos=NULL;
		}
		else if(pos->left_child&&!pos->right_child){
			node* tmp=pos;
			pos=pos->left_child;
			delete tmp;
		}
		else if(!pos->left_child&&pos->right_child){
			node* tmp=pos;
			pos=pos->right_child;
			delete tmp;
		}
		else if(pos->left_child->priority<pos->right_child->priority){
			Zig(pos);
			remove(data, pos);
		}
		else{
			Zag(pos);
			remove(data, pos);
		}
		return;
	}
	pos->size--;
	if(data<pos->data)
		remove(data,pos->left_child);
	else
		remove(data,pos->right_child);
}
int Treap::pre(const int &data){
	node* tmp=root;
	int ans=0x80000000;
	while(tmp){
		if(data>tmp->data)
			ans=tmp->data,tmp=tmp->right_child;
		else
			tmp=tmp->left_child;
	}
	return ans;
}
int Treap::sub(const int &data){
	node* tmp=root;
	int ans=0x7fffffff;
	while(tmp){
		if(data<tmp->data)
			ans=tmp->data,tmp=tmp->left_child;
		else
			tmp=tmp->right_child;
	}
	return ans;
}
int Treap::data(const int &rank){
	node* tmp=root;
	int k=rank;
	while(tmp){
		int x=tmp->left_child?tmp->left_child->size:0;
		if(x<k&&x+tmp->count>=k)
			return tmp->data;
		if(x>=k)
			tmp=tmp->left_child;
		else{
			k-=x+tmp->count;
			tmp=tmp->right_child;
		}
	}
	return 0;
}
int Treap::rank(const int &data){
	node* tmp=root;
	int r=0;
	while(tmp){
		int x=tmp->left_child?tmp->left_child->size:0;
		if(data==tmp->data)
			return x+r+1;
		if(data<tmp->data)
			tmp=tmp->left_child;
		else{
			r+=x+tmp->count;
			tmp=tmp->right_child;
		}
	}
	return r;
}