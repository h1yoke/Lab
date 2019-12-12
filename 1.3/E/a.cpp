
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int levensteinInstruction( const std::string &s1, const std::string &s2 )
{
  std::vector<std::vector<int>> dp(s1.length() + 1);
  for (int i = 0; i < dp.size(); i++)
    dp[i].resize(s2.length() + 1);

  dp[0][0] = 0;
  for (int i = 1; i < s1.length() + 1; i++)
    dp[i][0] = i;
  for (int j = 1; j < s2.length() + 1; j++)
    dp[0][j] = j;

  for (int i = 1; i < s1.length() + 1; i++)
    for (int j = 1; j < s2.length() + 1; j++)
      if (s1[i - 1] != s2[j - 1])
        dp[i][j] = std::min({dp[i][j - 1] + 1, dp[i - 1][j] + 1, dp[i - 1][j - 1] + 1});
      else
        dp[i][j] = dp[i - 1][j - 1];

  return dp[s1.length()][s2.length()];
}

int main( void )
{
  std::string s1, s2;
  std::cin >> s1 >> s2;
  std::cout << levensteinInstruction(s1, s2);
  return 0;
}
