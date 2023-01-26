template <typename T>
class fenwick {
 public:
  vector<vector<T>> fenw;
  int n, m;

  fenwick(int _n, int _m) : n(_n), m(_m) {
    fenw.resize(n + 1);
    for (int i = 0; i < n; ++i) {
      fenw[i].resize(m);
    }
  }

  inline void modify(int x, int y, T v) {
    assert(x >= 0 && x < n);
    assert(y >= 0 && y < m);
    for (int i = x; i < n; i |= (i + 1)) {
      for (int j = y; j < m; j |= (j + 1)) {
        fenw[i][j] += v;
      }
    }
  }

  inline T get(int x, int y) {
    assert(x >= 0 && x < n);
    assert(y >= 0 && y < m);
    T res{};
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
        res += fenw[i][j];
      }
    }
    return res;
  }

  inline T get(int x1, int y1, int x2, int y2) {
    assert(x1 <= x2 && y1 <= y2);
    assert(x1 >= 0 && x1 < n && x2 >= 0 && x2 < n);
    assert(y1 >= 0 && y1 < m && y2 >= 0 && y2 < m);
    T res = get(x2, y2);
    if (x1 - 1 >= 0) {
      res -= get(x1 - 1, y2);
    }
    if (y1 - 1 >= 0) {
      res -= get(x2, y1 - 1);
    }
    if (x1 - 1 >= 0 && y1 - 1 >= 0) {
      res += get(x1 - 1, y1 - 1);
    }
    return res;
  }
};
