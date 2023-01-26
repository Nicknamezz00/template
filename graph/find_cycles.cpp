template <typename T>
vector<vector<int>> find_cycles(const graph<T> &g, int bound = 1 << 30) {
  vector<int> was(g.n, -1);
  vector<int> st;
  vector<vector<int>> cycles;
  function<void(int, int)> dfs = [&g, &was, &st, &cycles, &dfs, &bound](int v, int pe) {
    if ((int) cycles.size() >= bound) {
      return;
    }
    was[v] = st.size();
    for (int id : g.g[v]) {
      if (id == pe) {
        continue;
      }
      auto &e = g.edges[id];
      int to = e.from ^ e.to ^ v;
      if (was[to] >= 0) {
        vector<int> cycle(1, id);
        for (int j = was[to]; j < (int) st.size(); j++) {
          cycle.push_back(st[j]);
        }
        cycles.push_back(cycle);
        if ((int) cycles.size() >= bound) {
          return;
        }
        continue;
      }
      if (was[to] == -1) {
        st.push_back(id);
        dfs(to, id);
        st.pop_back();
      }
    }
    was[v] = -2;
  };
  for (int i = 0; i < g.n; i++) {
    if (was[i] == -1) {
      dfs(i, -1);
    }
  }
  return cycles;
  // cycles are given by edge ids, all cycles are simple
  // returns at most bound cycles (given by edge ids)
  // digraph: finds at least one cycle in every connected component
  // undigraph: finds cycle basis
}