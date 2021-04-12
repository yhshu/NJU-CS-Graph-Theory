//
// Created by Yiheng Shu on 2021/4/3.
//

#pragma GCC optimize ("O2")

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstring>
#include <queue>
#define maxn 100000 + 5
#define inf 0x3f3f3f3f
using namespace std;

int ans = 0;
int size1, size2;
bool vis[maxn];
vector<int> adj_list[maxn];
int match1[maxn];
int match2[maxn];
int l1[maxn];
int l2[maxn];
int dis;

bool search() {
  queue<int> que;
  dis = inf;
  memset(l1, -1, sizeof(l1));
  memset(l2, -1, sizeof(l2));
  for (int i = 0; i < size1; i++) {
    if (match1[i] == -1) {
      que.push(i);
      l1[i] = 0;
    }
  }
  while (!que.empty()) {
    int front = que.front();
    que.pop();

    if (l1[front] > dis)
      break;
    for (int j : adj_list[front]) {
      if (l2[j] == -1) {
        l2[j] = l1[front] + 1;
        if (match2[j] == -1) {
          dis = l2[j];
        } else {
          l1[match2[j]] = l2[j] + 1;
          que.push(match2[j]);
        }
      }
    }
  }
  return dis != inf;
}

int dfs(int i) {
  for (int j : adj_list[i]) {
    if (!vis[j] && l2[j] == l1[i] + 1) {
      vis[j] = true;
      if (match2[j] != -1 && l2[j] == dis)
        continue;
      if (match2[j] == -1 || dfs(match2[j])) {
        match2[j] = i;
        match1[i] = j;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // input
  cin >> size1 >> size2;

  for (int i = 0; i < size1; i++) {
    int degree;
    cin >> degree;
    for (int j = 0; j < degree; j++) {
      int node;
      cin >> node;
      adj_list[i].push_back(node - 1);
    }
  }

  // algorithm
  memset(match1, -1, sizeof(match1));
  memset(match2, -1, sizeof(match2));
  while (search()) {
    memset(vis, false, sizeof(vis));

    for (int i = 0; i < size1; i++) {
      if (match1[i] == -1 && dfs(i)) { ans++; }

      if (ans == min(size1, size2)) {
        break;
      }
    }

    if (ans == min(size1, size2)) {
      break;
    }
  }

  // output
  cout << ans;
  return 0;
}
