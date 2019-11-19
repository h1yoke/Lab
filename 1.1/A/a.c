
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

int main( void )
{
  int N, i;
  int *a;

  scanf("%d", &N);
  a = malloc(sizeof(int) * N);
  for (i = 0; i < N; i++)
    scanf("%d", &a[i]);

  Sort(a, 0, N - 1);

  for (i = 0; i < N; i++)
    printf("%d ", a[i]);
  printf("\n");

  free(a);
  return 0;
}
