#pragma G++ optimize ("O2")

#include <vector>
#include <iostream>
#include <queue>
#include <utility>
#include <cstring>
#include <algorithm>

using namespace std;

#define maxn (100000 + 5)

int n, size1, size2;
int match1[maxn];
int match2[maxn];
bool vis1[maxn];
bool vis2[maxn];
int pre[maxn];
long long l1[maxn];
long long l2[maxn];
vector<pair<int, long long>> g[maxn];
long long slack[maxn];
long long inf = 0x7fffffff;
long long ans = 0;
queue<int> que;

void addEdge(int u, int v, long long w) {
  g[u].emplace_back(v, max(w, 0ll));
}

bool check(int v) {
  vis2[v] = true;
  if (match2[v] != -1) {
    que.push(match2[v]);
    vis1[match2[v]] = true;
    return false;
  }
  while (v != -1) {
    match2[v] = pre[v];
    swap(v, match1[pre[v]]);
  }
  return true;
}

void clear(queue<int> &q) {
  queue<int> empty;
  swap(empty, q);
}

void bfs(int i) {
  clear(que);
  que.push(i);
  vis1[i] = true;

  while (true) {
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (auto p : g[u]) {
        auto v = p.first;
        auto w = p.second;
        if (!vis2[v]) {
          auto delta = l1[u] + l2[v] - w;
          if (slack[v] >= delta) {
            pre[v] = u;
            if (delta) {
              slack[v] = delta;
            } else if (check(v)) {
              return;
            }
          }
        }
      }
    }

    auto a = inf;
    for (int j = 0; j < size2; j++) {
      if (!vis2[j]) {
        a = min(a, slack[j]);
      }
    }
    for (int j = 0; j < size1; j++) {
      if (vis1[j]) {
        l1[j] -= a;
      }
    }
    for (int j = 0; j < size2; j++) {
      if (vis2[j]) {
        l2[j] += a;
      } else {
        slack[j] -= a;
      }
    }
    for (int j = 0; j < size2; j++) {
      if (!vis2[j] && slack[j] == 0 && check(j)) {
        return;
      }
    }
  }
}

void solve() {
  for (int i = 0; i < maxn; i++) {
    slack[i] = inf;
    l1[i] = -inf;
    match1[i] = -1;
    match2[i] = -1;
  }

  for (int i = 0; i < size1; i++) {
    for (auto p : g[i]) {
      auto w = p.second;
      l1[i] = max(l1[i], w);
    }
  }

  for (int i = 0; i < size1; i++) {
    memset(vis1, false, sizeof(vis1));
    memset(vis2, false, sizeof(vis2));
    bfs(i);
  }

  for (int i = 0; i < size1; i++) {
    for (auto p : g[i]) {
      if (p.first == match1[i]) {
        if (p.second > 0) {
          ans += p.second;
        } else {
          match1[i] = -1;
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> size1 >> size2;

  int v, degree;
  long long w;
  for (int i = 0; i < size1; i++) {
    cin >> w >> degree;
    for (int j = 0; j < degree; j++) {
      cin >> v;
      addEdge(i, v - 1, w);
    }
  }

  // algorithm
  solve();

  // output
  cout << ans;
  return 0;
}
