class DSU {
public:
  vector<int> p;
  vector<int> siz;
  int n;
 
  DSU(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
    siz.assign(n, 1);
  }
 
  int find(int x) {
    return (x == p[x] ? x : (p[x] = find(p[x])));
  }
 
  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
      siz[y] += siz[x];
      p[x] = y;
      return true;
    }
    return false;
  }

  bool same(int x, int y) {
    return find(x) == find(y);
  }

  int size(int x) {
    return siz[find(x)];
  }

  vector<vector<int>> groups() {
    vector<int> leader(n), g_size(n);
    for (int i = 0; i < n; i++) {
      leader[i] = find(i);
      g_size[leader[i]]++;
    }
    vector<vector<int>> group(n);
    for (int i = 0; i < n; i++) {
      group[i].reserve(g_size[i]);
    }
    for (int i = 0; i < n; i++) {
      group[leader[i]].push_back(i);
    }
    group.erase(remove_if(group.begin(), group.end(), [&](const vector<int>& v) {
      return v.empty();
    }), group.end());
    return group;
  }
};
