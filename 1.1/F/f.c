
#include <stdio.h>
#include <stdlib.h>

#define ABS(X) (((X) >= 0) ? (X) : -(X))

int Find( long long *A, int Size, long long X )
{
  long long
    l = 0,
    r = Size;

  while (r - l > 1)
  {
    long long m = (r + l) / 2;

    if (A[m] <= X)
      l = m;
    else
      r = m;
  }

  if (r < Size && ABS(X - A[l]) > ABS(A[r] - X))
    return r;
  return l;
}

int main( void )
{
  int N, K, i;
  long long *a;

  scanf("%d", &N);
  scanf("%d", &K);

  a = malloc(sizeof(long long) * N);
  for (i = 0; i < N; i++)
    scanf("%I64d", &a[i]);

  for (i = 0; i < K; i++)
  {
    long long req;

    scanf("%I64d", &req);
    printf("%I64d\n", a[Find(a, N, req)]);
  }

  free(a);
  return 0;
}
