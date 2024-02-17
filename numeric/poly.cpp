template <typename T>
vector<T>& operator+=(vector<T>& a, const vector<T>& b) {
  if (a.size() < b.size()) {
    a.resize(b.size());
  }
  for (int i = 0; i < (int) b.size(); i++) {
    a[i] += b[i];
  }
  return a;
}
 
template <typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
  vector<T> c = a;
  return c += b;
}
 
template <typename T>
vector<T>& operator-=(vector<T>& a, const vector<T>& b) {
  if (a.size() < b.size()) {
    a.resize(b.size());
  }
  for (int i = 0; i < (int) b.size(); i++) {
    a[i] -= b[i];
  }
  return a;
}
 
template <typename T>
vector<T> operator-(const vector<T>& a, const vector<T>& b) {
  vector<T> c = a;
  return c -= b;
}
 
template <typename T>
vector<T> operator-(const vector<T>& a) {
  vector<T> c = a;
  for (int i = 0; i < (int) c.size(); i++) {
    c[i] = -c[i];
  }
  return c;
}
 
template <typename T>
vector<T> operator*(const vector<T>& a, const vector<T>& b) {
  if (a.empty() || b.empty()) {
    return {};
  }
  vector<T> c(a.size() + b.size() - 1, 0);
  for (int i = 0; i < (int) a.size(); i++) {
    for (int j = 0; j < (int) b.size(); j++) {
      c[i + j] += a[i] * b[j];
    }
  }
  return c;
}
 
template <typename T>
vector<T>& operator*=(vector<T>& a, const vector<T>& b) {
  return a = a * b;
}
 
template <typename T>
vector<T> inverse(const vector<T>& a) {
  assert(!a.empty());
  int n = (int) a.size();
  vector<T> b = {1 / a[0]};
  while ((int) b.size() < n) {
    vector<T> a_cut(a.begin(), a.begin() + min(a.size(), b.size() << 1));
    vector<T> x = b * b * a_cut;
    b.resize(b.size() << 1);
    for (int i = (int) b.size() >> 1; i < (int) min(x.size(), b.size()); i++) {
      b[i] = -x[i];
    }
  }
  b.resize(n);
  return b;
}
 
template <typename T>
vector<T>& operator/=(vector<T>& a, const vector<T>& b) {
  int n = (int) a.size();
  int m = (int) b.size();
  if (n < m) {
    a.clear();
  } else {
    vector<T> d = b;
    reverse(a.begin(), a.end());
    reverse(d.begin(), d.end());
    d.resize(n - m + 1);
    a *= inverse(d);
    a.erase(a.begin() + n - m + 1, a.end());
    reverse(a.begin(), a.end());
  }
  return a;
}
 
template <typename T>
vector<T> operator/(const vector<T>& a, const vector<T>& b) {
  vector<T> c = a;
  return c /= b;
}
 
template <typename T>
vector<T>& operator%=(vector<T>& a, const vector<T>& b) {
  int n = (int) a.size();
  int m = (int) b.size();
  if (n >= m) {
    vector<T> c = (a / b) * b;
    a.resize(m - 1);
    for (int i = 0; i < m - 1; i++) {
      a[i] -= c[i];
    }
  }
  return a;
}
 
template <typename T>
vector<T> operator%(const vector<T>& a, const vector<T>& b) {
  vector<T> c = a;
  return c %= b;
}
 
template <typename T, typename U>
vector<T> power(const vector<T>& a, const U& b, const vector<T>& c) {
  assert(b >= 0);
  vector<U> binary;
  U bb = b;
  while (bb > 0) {
    binary.push_back(bb & 1);
    bb >>= 1;
  }
  vector<T> res = vector<T>{1} % c;
  for (int j = (int) binary.size() - 1; j >= 0; j--) {
    res = res * res % c;
    if (binary[j] == 1) {
      res = res * a % c;
    }
  }
  return res;
}
 
