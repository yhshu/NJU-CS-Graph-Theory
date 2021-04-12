#pragma G++ optimize ("O2")

#include <vector>
#include <iostream>
#include <queue>
#include <utility>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

#define maxn (100000 + 5)

int size1, size2;
int match[maxn];
bool vis1[maxn];
bool vis2[maxn];
long long l1[maxn];
long long l2[maxn];
vector<pair<int, long long>> g[maxn];
map<pair<int, int>, long long> weight;
long long slack;
long long inf = 0x3f3f3f3f;
long long ans = 0;

void addEdge(int u, int v, long long w) {
  g[u].emplace_back(v, max(w, 0ll));
}

long long get_w(int i, int j) {
  for (auto p : g[i]) {
    if (p.first == j) {
      return p.second;
    }
  }
  return 0;
}

bool dfs(int i) {
  vis1[i] = true;
  for (int j = 0; j < size2; j++) {
    if (vis2[j]) continue;
    auto t = l1[i] + l2[j] - get_w(i, j);
    if (!t) {
      vis2[j] = true;
      if (match[j] == -1 || dfs(match[j])) {
        match[j] = i;
        return true;
      }
    } else if (slack > t) slack = t;
  }
  return false;
}

void solve() {
  memset(match, -1, sizeof(match));
  memset(l2, 0, sizeof(l2));

  for (int i = 0; i < size1; i++) {
    l1[i] = -inf;
    for (auto p : g[i]) {
      l1[i] = max(l1[i], p.second);
    }
  }

  for (int k = 0; k < size1; k++) {
    while (true) {
      slack = inf;
      memset(vis1, false, sizeof(vis1));
      memset(vis2, false, sizeof(vis2));
      if (dfs(k)) break;
      for (int i = 0; i < size1; i++)
        if (vis1[i]) l1[i] -= slack;
      for (int j = 0; j < size2; j++)
        if (vis2[j]) l2[j] += slack;
    }
  }

  for (int j = 0; j < size2; j++) {
    ans += get_w(match[j], j);
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
