// LiChao Tree
// min(ax + b) 
template <typename T>
struct LiChaoTree{
  struct Line{
    T a, b;

    Line(T a, T b) : a(a), b(b) {}

    inline T get(T x) const { return a * x + b; }

    inline bool over(const Line &b, const T &x) const{
      return get(x) < b.get(x);
    }
  };
 
  vector<T> xs;
  vector<Line> seg;
  int sz;
 
  LiChaoTree(const vector<T> &x, T INF) : xs(x) {
    sz = 1;
    while (sz < xs.size()) {
      sz <<= 1;
    }
    while (xs.size() < sz) {
      xs.push_back(xs.back() + 1);      
    }
    seg.assign(2 * sz - 1, Line(0, INF));
  }
 
  void update(Line &x, int k, int l, int r) {
    int m = midpoint(l, r);
    auto latte = x.over(seg[k], xs[l]), malta = x.over(seg[k], xs[m]);
    if (malta) {
      swap(seg[k], x);
    }
    if (l + 1 >= r) {
      return;
    }
    if (latte != malta) {
      update(x, 2 * k + 1, l, m);
    } else {
      update(x, 2 * k + 2, m, r);
    }
  }

  void update(T a, T b) { // ax+b
    Line l(a, b);
    update(l, 0, 0, sz);
  }

  T query(int k) { // xs[k]
    const T x = xs[k];
    k += sz - 1;
    T ret = seg[k].get(x);
    while (k > 0){
      k = (k - 1) >> 1;
      ret = min(ret, seg[k].get(x));
    }
    return ret;
  }
};
