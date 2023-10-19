template <int N>
class DSU {
  protected:
    int father[N];
    virtual int find(int a);
  public:
    DSU();
    virtual void merge(int a, int b);
    virtual bool check(int a, int b);
};

template <int N>
class sizeDSU final : public DSU<N> {
  private:
    int size[N];
  public:
    sizeDSU();
    virtual void merge(int a, int b);
};

template <int N>
void sizeDSU<N>::merge(int a, int b) {
  a = this->find(a), b = this->find(b);
  if (a == b)
    return;
  if (size[a] < size[b]) {
    swap(a, b);
  }
  this->father[b] = a;
  size[a] += size[b];
}

template <int N>
sizeDSU<N>::sizeDSU() : DSU<N>() {
  for (int i = 0; i < N; ++i)
    size[i] = 1;
}

template <int N>
DSU<N>::DSU() {
  for (int i = 0; i < N; ++i)
    father[i] = i;
}

template <int N>
int DSU<N>::find(int a) {
  return father[a] == a ? a : father[a] = find(father[a]);
}

template <int N>
void DSU<N>::merge(int a, int b) {
  father[find(b)] = find(a);
}

template <int N>
bool DSU<N>::check(int a, int b) {
  return find(a) == find(b);
}