template <typename T>
vector<int> find_scc(const digraph<T> &g, int &cnt) {
  digraph<T> g_rev = g.reverse();
  vector<int> order;
  vector<bool> was(g.n, false);
  function<void(int)> tar = [&](int v) {
    was[v] = true;
    for (int id : g.g[v]) {
      if (g.ignore != nullptr && g.ignore(id)) {
        continue;
      }
      auto &e = g.edges[id];
      int to = e.to;
      if (!was[to]) {
        tar(to);
      }
    }
    order.push_back(v);
  };
  for (int i = 0; i < g.n; i++) {
    if (!was[i]) {
      tar(i);
    }
  }
  vector<int> c(g.n, -1);
  function<void(int)> jan = [&](int v) {
    for (int id : g_rev.g[v]) {
      if (g_rev.ignore != nullptr && g_rev.ignore(id)) {
        continue;
      }
      auto &e = g_rev.edges[id];
      int to = e.to;
      if (c[to] == -1) {
        c[to] = c[v];
        jan(to);
      }
    }
  };
  cnt = 0;
  for (int id = g.n - 1; id >= 0; id--) {
    int i = order[id];
    if (c[i] != -1) {
      continue;
    }
    c[i] = cnt++;
    jan(i);
  }
  return c;
  // c[i] <= c[j] for every edge i -> j
}