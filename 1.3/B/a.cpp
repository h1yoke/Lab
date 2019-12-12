
#include <fstream>
#include <vector>

int main( void )
{
  std::ifstream in("input.txt");

  std::vector<std::vector<int>> d(0), a;
  std::vector<std::vector<char>> path;
  int n, m;
  in >> n >> m;

  a.resize(n);
  d.resize(n);
  path.resize(n);
  for (int i = 0; i < n; i++)
  {
    a[i].resize(m);
    d[i].resize(m);
    path[i].resize(m);
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      in >> a[i][j];
  in.close|();

  for (int i = 0; i < n; i++)
    for (int j = 0; j <= i; j++)
    {
      d[i][0] += a[j][0];
      path[i][0] = 'D';
    }
  for (int i = 0; i < m; i++)
    for (int j = 0; j <= i; j++)
    {
      d[0][i] += a[0][j];
      path[0][i] = 'R';
    }

  for (int i = 1; i < n; i++)
    for (int j = 1; j < m; j++)
    {
      int max;

      if (d[i - 1][j] > d[i][j - 1])
      {
        max = d[i - 1][j];
        path[i][j] = 'D';
      }
      else
      {
        max = d[i][j - 1];
        path[i][j] = 'R';
      }

      d[i][j] = a[i][j] + max;
    }

  std::vector<char> res;
  int i = n - 1, j = m - 1;
  while (i != 0 || j != 0)
  {
    res.push_back(path[i][j]);
    if (path[i][j] == 'D')
      i--;
    else
      j--;
  }

  std::ofstream out("output.txt");
  out << d[n - 1][m - 1] << std::endl;
  for (int i = res.size() - 1; i >= 0; i--)
    out << res[i];
  out.close();
  return 0;
}
