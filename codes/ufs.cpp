template <int N>
class UFS {
  protected:
    int father[N];
    virtual int find(int a);
  public:
    UFS();
    virtual void merge(int a, int b);
    virtual bool check(int a, int b);
};

template <int N>
class sizeUFS final : public UFS<N> {
  private:
    int size[N];
  public:
    sizeUFS();
    virtual void merge(int a, int b);
};

template <int N>
void sizeUFS<N>::merge(int a, int b) {
  a = this->find(a), b = this->find(b);
  if (size[a] < size[b]) {
    swap(a, b);
  }
  this->father[b] = a;
  size[a] += size[b];
}

template <int N>
sizeUFS<N>::sizeUFS() : UFS<N>() {
  for (int i = 0; i < N; ++i)
    size[i] = 1;
}

template <int N>
UFS<N>::UFS() {
  for (int i = 0; i < N; ++i)
    father[i] = i;
}

template <int N>
int UFS<N>::find(int a) {
  return father[a] == a ? a : father[a] = find(father[a]);
}

template <int N>
void UFS<N>::merge(int a, int b) {
  father[find(b)] = find(a);
}

template <int N>
bool UFS<N>::check(int a, int b) {
  return find(a) == find(b);
}