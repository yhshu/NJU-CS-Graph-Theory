//
// Created by Yiheng Shu on 2021/4/2.
//


#pragma GCC optimize ("O2")
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int ans = 0;
int size1, size2;
vector<unordered_set<int>> adj_list;
bool *vis;
vector<int> partner;

int dfs(int i);

int main() {

  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // input
  cin >> size1 >> size2;
  vis = new bool[size2];

  for (int i = 0; i < size1; i++) {
    int degree;
    cin >> degree;
    adj_list.emplace_back(unordered_set<int>());
    for (int j = 0; j < degree; j++) {
      int node;
      cin >> node;
      adj_list.at(i).insert(node - 1);
    }
  }

  // algorithm
  for (int i = 0; i < size2; i++) {
    partner.push_back(-1);
  }

  for (int i = 0; i < size1; i++) {
    for (int j = 0; j < size2; j++) {
      vis[j] = false;
    }
    ans += dfs(i);

    if (ans == min(size1, size2))
      break;
  }

  // output
  cout << ans;
  return 0;
}

int dfs(int i) {
  for (int j = 0; j < size2; j++) {
    if (!vis[j] && adj_list.at(i).find(j) != adj_list.at(i).end()) {
      vis[j] = true;
      if (partner.at(j) == -1 || dfs(partner.at(j)) != 0) {
        partner.at(j) = i;
        return 1;
      }
    }
  }
  return 0;
}