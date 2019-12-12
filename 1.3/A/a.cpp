
#include <fstream>
#include <bits/stdc++.h>
#include <vector>

int main( void )
{
  std::ifstream in("input.txt");
  int n, k;
  in >> n >> k;

  std::vector<int> a(n + 1);
  a[1] = 0;
  for (int i = 2; i < n; i++)
    in >> a[i];
  a[n] = 0;

  std::vector<std::pair<int, int>> dp(n + 1);
  dp[1].first = 0;
  dp[1].second = -1;
  for (int i = 2; i < std::min(k + 1, n + 1); i++)
    dp[i] = {a[i], 1};

  for (int i = std::min(k + 1, n + 1); i < n + 1; i++)
  {
    int max = INT_MIN, max_i;
    for (int j = 1; j <= k && j < i; j++)
      if (max < dp[i - j].first)
      {
        max = dp[i - j].first;
        max_i = i - j;
      }

    dp[i].first = a[i] + max;
    dp[i].second = max_i;
  }
  std::vector<int> path;
  int i = n;
  while (i != -1)
  {
    path.push_back(i);
    i = dp[i].second;
  }

  std::ofstream out("output.txt");
  out << dp[n].first << std::endl << path.size() - 1 << std::endl;
  for (int i = path.size() - 1; i >= 0; i--)
    out << path[i] << " ";
  out << std::endl;

  return 0;
}
