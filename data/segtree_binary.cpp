template <class T, auto binary, auto e>
struct SegmentTree {
  int n;
  vector<T> s;
  SegmentTree(int n) : n(n), s(n * 2, e()) {}
  void set(int i, T v) {
    for (s[i += n] = v; i /= 2;) {
      s[i] = binary(s[i * 2], s[i * 2 + 1]);
    }
  }
  T product(int l, int r) {
    T rl = e(), rr = e();
    for (l += n, r += n + 1; l != r; l /= 2, r /= 2) {
      if (l % 2) {
        rl = binary(rl, s[l++]);
      }
      if (r % 2) {
        rr = binary(s[--r], rr);
      }
    }
    return binary(rl, rr);
  }
};

int f(int x, int y) {

}

int e() {

}
