#pragma G++ optimize ("O2")

#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;

#define maxn (100000 + 5)

int size1, size2;
int match[maxn];
bool vis[maxn];
long long l1[maxn];
long long l2[maxn];
vector<pair<int, long long>> g[maxn];
long long inf = 0x3f3f3f3f;
long long ans = 0;
long long c[maxn];
int p[maxn];

void addEdge(int u, int v, long long w) {
  g[u].emplace_back(v, max(w, 0ll));
}

long long get_w(int i, int j) {
  for (auto pair : g[i]) {
    if (pair.first == j) {
      return pair.second;
    }
  }
  return 0;
}

void bfs(int u) {
  int a, v = 0, vl = 0;
  long long d;
  for (int i = 0; i < size1; i++) {
    p[i] = 0;
    c[i] = inf;
  }
  match[v] = u;
  do {
    a = match[v];
    d = inf;
    vis[v] = true;

    for (int b = 0; b < size2; b++)
      if (!vis[b]) {
        if (c[b] > l1[a] + l2[b] - get_w(a, b)) {
          c[b] = l1[a] + l2[b] - get_w(a, b);
          p[b] = v;
        }
        if (c[b] < d) {
          d = c[b];
          vl = b;
        }
      }
    for (int b = 0; b < size2; b++)
      if (vis[b]) {
        l1[match[b]] -= d;
        l2[b] += d;
      } else {
        c[b] -= d;
      }
    v = vl;
  } while (match[v]);

  while (v) {
    match[v] = match[p[v]];
    v = p[v];
  }
}

void solve() {
  for (int i = 0; i < size1; i++) {
    match[i] = 0;
    l1[i] = l2[i] = 0;
  }
  for (int i = 0; i < size1; i++) {
    for (int j = 0; j < size2; j++) vis[j] = false;
    bfs(i);
  }
  for (int j = 0; j < size2; j++)
    ans += get_w(match[j], j);
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
