template <typename T>
vector<int> cartesian_tree(const vector<T> &v){
  vector<int> pr(v.size(), -1);
  vector<int> st;
  st.push_back(0);
  for (int i = 1; i < (int) v.size(); i++){
    int prv = -1;
    while (!st.empty()){
      int j = st.back();
      if (v[i] < v[j]){
        st.pop_back();
        if (prv != -1){
          pr[prv] = j;
        }
        prv = j;
      } else {
        break;
      }
    }
    if (prv != -1){
      pr[prv] = i;
    }
    st.push_back(i);
  }
  while ((int) st.size() >= 2){
    int x = st.back();
    st.pop_back();
    pr[x] = st.back();
  }
  return pr;
}
