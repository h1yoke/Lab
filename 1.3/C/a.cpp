
#include <iostream>
#include <vector>

int main( void )
{
  int n;
  std::cin >> n;

  std::vector<int> a(n), dp(n, 1), p(n, -1);
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < i; j++)
      if (a[j] < a[i])
        if (dp[i] < dp[j] + 1)
        {
          dp[i] = dp[j] + 1;
          p[i] = j;
        }

  int max_pos = 0;
  for (int i = 1; i < n; i++)
    if (dp[i] > dp[max_pos])
      max_pos = i;

  std::vector<int> result;
  int i = max_pos;
  while (i != -1)
  {
    result.push_back(i);
    i = p[i];
  }

  std::cout << dp[max_pos] << std::endl;
  for (int i = result.size() - 1; i >= 0; i--)
    std::cout << a[result[i]] << " ";
  std::cout << std::endl;

  return 0;
}
