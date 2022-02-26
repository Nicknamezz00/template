template <typename T, class F = function<T(const T &, const T &)>>
class fenwick {
 public:
  int n;
  vector<T> fenw, val;
  F func;

  fenwick(const vector<T> &v, const F &f) : func(f) {
    n = static_cast<int>(v.size());
    val.resize(n);
    fenw.resize(n);
    for (int i = 1; i <= n; ++i) {
      val[i - 1] = fenw[i - 1] = v[i - 1];
      int len = i & -i;
      for (int j = 1; j < len; j <<= 1) {
        fenw[i - 1] = func(fenw[i - 1], fenw[i - j - 1]);
      }
    }
  }

  void modify(int x, T v) {
    assert(x >= 0 && x < n);
    val[x] = v;
    for (int i = x + 1; i <= n; i += i & -i) {
      fenw[i - 1] = val[i - 1];
      int len = i & -i;
      for (int j = 1; j < len; j <<= 1) {
        fenw[i - 1] = func(fenw[i - 1], fenw[i - j - 1]);
      }
    }
  }

  T get(int l, int r) {
    assert(l >= 0 && l < n);
    assert(r >= 0 && r < n);
    ++l, ++r;
    T res = val[r - 1];
    while (true) {
      res = func(res, val[r - 1]);
      if (l == r) {
        break;
      }
      for (--r; r - (r & -r) >= l; r -= (r & -r)) {
        res = func(res, fenw[r - 1]);
      }
    }
    return res;
  }
};
