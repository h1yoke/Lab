
#include <stdio.h>
#include <math.h>

#define max(A, B) ((A) > (B) ? (A) : (B))
#define min(A, B) ((A) < (B) ? (A) : (B))

unsigned long long BinSearch( int W, int H, int N )
{
  unsigned long long
    l = min(W, H),
    r = N * max(W, H);

  while (r - l > 1)
  {
    unsigned long long m = (r + l) / 2;

    if (log10(m / W) + log10(m / H) >= log10(N))
      r = m;
    else
      l = m;
  }
  return r;
}

int main( void )
{
  int w, h, n;
  scanf("%i %i %i", &w, &h, &n);
  printf("%I64d\n", BinSearch(w, h, n));
  return 0;
}
