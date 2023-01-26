template <typename T>
class fenwick {
 public:
  vector<T> fenw;
  int n;

  fenwick(int _n) : n(_n) {
    fenw.resize(n);
  }

  inline void modify(int x, T v) {
    assert(x >= 0 && x < n);
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }

  inline T get(int x) {
    assert(x >= 0 && x < n);
    T res{};
    while (x >= 0) {
      res += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return res;
  }

  inline T get(int l, int r) {
    assert(l >= 0 && l < n);
    assert(r >= 0 && r < n);
    T res = get(r);
    if (l - 1 >= 0) {
      res -= get(l - 1);
    }
    return res;
  }
};
