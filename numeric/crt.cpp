template <typename T>
void crt(const vector<int>& p, const vector<int>& a, T& res) {
  assert(p.size() == a.size());
  auto inverse = [&](int q, int m) {
    q %= m;
    if (q < 0) q += m;
    int b = m, u = 0, v = 1;
    while (q) {
      int t = b / q;
      b -= t * q; swap(q, b);
      u -= t * v; swap(u, v);
    }
    assert(b == 1);
    if (u < 0) u += m;
    return u;
  };
  vector<int> x(p.size());
  for (int i = 0; i < (int) p.size(); i++) {
    assert(0 <= a[i] && a[i] < p[i]);
    x[i] = a[i];
    for (int j = 0; j < i; j++) {
      x[i] = (int) ((long long) (x[i] - x[j]) * inverse(p[j], p[i]) % p[i]);
      if (x[i] < 0) x[i] += p[i];
    }
  }
  res = 0;
  for (int i = (int) p.size() - 1; i >= 0; i--) {
    res = res * p[i] + x[i];
  }
}