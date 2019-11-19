
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int Left;
  int Right;
} PAIR;

void Swap( int *A, int *B )
{
  int tmp = *A;

  *A = *B;
  *B = tmp;
}

PAIR Split( int *A, int Left, int Right )
{
  PAIR res;
  int
    i = Left,
    j = Right,
    x = A[Left + rand() % (Right - Left)];

  while (i <= j)
  {
    while (A[i] < x)
      i++;
    while (A[j] > x)
      j--;

    if (i > j)
      break;

    Swap(&A[i], &A[j]);
    i++;
    j--;
  }

  res.Right = j;
  res.Left = i;
  return res;
}

void Sort( int *A, int Left, int Right )
{
  PAIR m;

  if (Left >= Right)
    return;

  m = Split(A, Left, Right);

  Sort(A, Left, m.Right);
  Sort(A, m.Left, Right);
}

int LowerBound( int *A, int Size, int X )
{
  int
    l = -1,
    r = Size;

  while (r - l > 1)
  {
    int m = (l + r) / 2;

    if (A[m] < X)
      l = m;
    else
      r = m;
  }
  return r;
}

int UpperBound( int *A, int Size, int X )
{
  return LowerBound(A, Size, X + 1);
}

int main( void )
{
  int N, K, i;
  int *a;

  scanf("%d", &N);
  a = malloc(sizeof(int) * N);
  for (i = 0; i < N; i++)
    scanf("%d", &a[i]);
  Sort(a, 0, N - 1);

  scanf("%i", &K);
  for (i = 0; i < K; i++)
  {
    int in1, in2, res1, res2;

    scanf("%i %i", &in1, &in2);
    printf("%i\n", UpperBound(a, N, in2) - LowerBound(a, N, in1));
  }

  free(a);
  return 0;
}
