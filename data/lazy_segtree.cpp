// [l, r)
template<class Info, class Tag>
struct LazySegmentTree {
  int n;
  vector<Info> info;
  vector<Tag> tag;

  LazySegmentTree() : n(0) {}

  LazySegmentTree(int _n, Info _v = Info()) {
    init(_n, _v);
  }

  template<class T>
  LazySegmentTree(vector<T> _init) {
    init(_init);
  }

  void init(int _n, Info _v = Info()) {
    init(vector(_n, _v));
  }

  template<class T>
  void init(vector<T> _init) {
    n = _init.size();
    info.assign(4 << __lg(n), Info());
    tag.assign(4 << __lg(n), Tag());
    function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        info[p] = _init[l];
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m, r);
      pull(p);
    };
    build(1, 0, n);
  }

  void pull(int p) {
    info[p] = info[2 * p] + info[2 * p + 1];
  }

  void apply(int p, const Tag &v) {
    info[p].apply(v);
    tag[p].apply(v);
  }

  void push(int p) {
    apply(2 * p, tag[p]);
    apply(2 * p + 1, tag[p]);
    tag[p] = Tag();
  }

  void modify(int p, int l, int r, int x, const Info &v) {
    if (r - l == 1) {
      info[p] = v;
      return;
    }
    int m = (l + r) / 2;
    push(p);
    if (x < m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m, r, x, v);
    }
    pull(p);
  }

  void modify(int p, const Info &v) {
      modify(1, 0, n, p, v);
  }

  Info query(int p, int l, int r, int x, int y) {
    if (l >= y || r <= x) {
      return Info();
    }
    if (l >= x && r <= y) {
      return info[p];
    }
    int m = (l + r) / 2;
    push(p);
    return query(2 * p, l, m, x, y) + query(2 * p + 1, m, r, x, y);
  }

  Info query(int l, int r) {
    return query(1, 0, n, l, r);
  }

  void modify(int p, int l, int r, int x, int y, const Tag &v) {
    if (l >= y || r <= x) {
      return;
    }
    if (l >= x && r <= y) {
      apply(p, v);
      return;
    }
    int m = (l + r) / 2;
    push(p);
    modify(2 * p, l, m, x, y, v);
    modify(2 * p + 1, m, r, x, y, v);
    pull(p);
  }

  void modify(int l, int r, const Tag &v) {
    return modify(1, 0, n, l, r, v);
  }

  template<class F>
  int find_first(int p, int l, int r, int x, int y, F pred) {
    if (l >= y || r <= x || !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    push(p);
    int res = find_first(2 * p, l, m, x, y, pred);
    if (res == -1) {
      res = find_first(2 * p + 1, m, r, x, y, pred);
    }
    return res;
  }

  template<class F>
  int find_first(int l, int r, F pred) {
    return find_first(1, 0, n, l, r, pred);
  }

  template<class F>
  int find_last(int p, int l, int r, int x, int y, F pred) {
    if (l >= y || r <= x || !pred(info[p])) {
      return -1;
    }
    if (r - l == 1) {
      return l;
    }
    int m = (l + r) / 2;
    push(p);
    int res = find_last(2 * p + 1, m, r, x, y, pred);
    if (res == -1) {
      res = find_last(2 * p, l, m, x, y, pred);
    }
    return res;
  }

  template<class F>
  int find_last(int l, int r, F pred) {
    return find_last(1, 0, n, l, r, pred);
  }
};
 
struct Tag {
  void apply(const Tag &t) {
  }
};

struct Info {
  void apply(const Tag &t) {
  }
};
 
Info operator+(const Info &a, const Info &b) {
}
