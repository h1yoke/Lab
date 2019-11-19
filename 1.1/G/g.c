
#include <stdio.h>

#define max(A, B) ((A) > (B) ? (A) : (B))
#define min(A, B) ((A) < (B) ? (A) : (B))

int f( int X, int Y, int N )
{
  return N / X + N / Y;
}

int BinSearch( int X, int Y, int N )
{
  int
    l = 0,
    r = N * max(X, Y);

  while (l < r)
  {
    int m = (r + l) / 2;

    if (f(X, Y, m) < N)
      l = m + 1;
    else
      r = m;
  }
  return l;
}

int main( void )
{
  int n, x, y;

  scanf("%i %i %i", &n, &x, &y);
  printf("%i\n", min(x, y) + BinSearch(x, y, n - 1));
  return 0;
}
