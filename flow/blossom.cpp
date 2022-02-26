template <typename T>
vector<int> find_max_unweighted_matching(const undigraph<T>& g) {
  vector<int> mate(g.n, -1);    // 匹配
  vector<int> label(g.n);       // "o" or "i" 初始点设为 "o", 这里以"0"代替"o", "1"代替"i"
  vector<int> parent(g.n);      // parent
  vector<int> orig(g.n);        // 花根
  queue<int> q;
  vector<int> aux(g.n, -1);     // 时间戳
  int aux_time = -1;
  auto lca = [&](int x, int y) {
    aux_time++;
    while (true) {
      if (x != -1) {
        if (aux[x] == aux_time) {  // 找到拜访过的点(LCA)
          return x;
        }
        aux[x] = aux_time;
        if (mate[x] == -1) {
          x = -1;
        } else {
          x = orig[parent[mate[x]]];  // 以匹配点的父节点继续寻找
        }
      }
      swap(x, y);
    }
  };
  auto blossom = [&](int v, int w, int a) {
    while (orig[v] != a) {
      parent[v] = w;
      w = mate[v];
      if (label[w] == 1) {  // 以初始点为"o"进行增广
        label[w] = 0;
        q.push(w);
      }
      orig[v] = orig[w] = a;  // 缩花
      v = parent[w];
    }
  };
  auto augment = [&](int v) {
    while (v != -1) {
      int pv = parent[v];
      int nv = mate[pv];
      mate[v] = pv;
      mate[pv] = v;
      v = nv;
    }
  };
  auto bfs = [&](int root) {
    fill(label.begin(), label.end(), -1);
    iota(orig.begin(), orig.end(), 0);
    while (!q.empty()) {
      q.pop();
    }
    q.push(root);
    label[root] = 0;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : g.g[v]) {
        auto &e = g.edges[id];
        int x = e.from ^ e.to ^ v;
        if (label[x] == -1) {  // 找到未拜访点
          label[x] = 1;        // 标记 "i"
          parent[x] = v;
          if (mate[x] == -1) {  // 找到未匹配点
            augment(x);         // 增广
            return true;
          }
          // 找到已匹配点,将匹配点入队,延伸交错树
          label[mate[x]] = 0;
          q.push(mate[x]);
          continue;
        }
        if (label[x] == 0 && orig[v] != orig[x]) {  // 找到已拜访点 且标记同为"o" 代表找到"花"
          int a = lca(orig[v], orig[x]);
          // 找LCA，缩花
          blossom(x, v, a);
          blossom(v, x, a);
        }
      }
    }
    return false;
  };
  auto greedy = [&]() {
    vector<int> order(g.n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end(), mt19937(787788));  // Magic
    // 先匹配一遍
    for (int i : order) {
      if (mate[i] == -1) {
        for (int id : g.g[i]) {
          auto &e = g.edges[id];
          int to = e.from ^ e.to ^ i;
          if (mate[to] == -1) {
            mate[i] = to;
            mate[to] = i;
            break;
          }
        }
      }
    }
  };
  greedy();  // 再瞎匹配一边，对未匹配点增广
  for (int i = 0; i < g.n; i++) {
    if (mate[i] == -1) {
      bfs(i);
    }
  }
  return mate;
}
