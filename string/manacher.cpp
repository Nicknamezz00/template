template <typename T>
vector<int> manacher(int n, const T &s) {
  if (n == 0) {
    return vector<int>();
  }
  vector<int> res(2 * n - 1, 0);
  {
    // odd
    int l = -1, r = -1;
    for (int i = 0; i < n; i++) {
      int p = (i >= r ? 0 : min(r - i, res[2 * (l + r - i)]));
      while (i + p + 1 < n && i - p - 1 >= 0) {
        if (s[i + p + 1] != s[i - p - 1]) {
          break;
        }
        p++;
      }
      if (i + p > r) {
        l = i - p;
        r = i + p;
      }
      res[2 * i] = p;
    }
  }
  {
    // even
    int l = -1, r = -1;
    for (int i = 0; i < n - 1; i++) {
      debug(l, r);
      int p = (i >= r ? 0 : min(r - i, res[2 * (l + r - i) - 1]));
      while (i + p + 1 < n && i - p >= 0) {
        if (s[i + p + 1] != s[i - p]) {
          break;
        }
        p++;
      }
      if (i + p > r) {
        l = i - p + 1;
        r = i + p;
      }
      res[2 * i + 1] = p;
    }
  }
  return res;
  // res[2 * i] = odd radius in position i
  // res[2 * i + 1] = even radius between positions i and i + 1
  // s = "abaa" -> res = {0, 0, 1, 0, 0, 1, 0}
}

template <typename T>
vector<int> manacher(const T &s) {
  return manacher(s.size(), s);
}