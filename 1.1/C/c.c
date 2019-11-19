
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long inverse_count = 0;

void Merge( int *Array, int L, int M, int R )
{
  int i = 0, j = 0;
  int left_len = M - L, right_len = R - M;
  int buf[R - L];

  while (i < left_len && j < right_len)
    if (Array[L + i] < Array[M + j])
    {
      buf[i + j] = Array[L + i];
      i++;
    }
    else
    {
      buf[i + j] = Array[M + j];
      j++;
      inverse_count += M - (L + i);
    }

  while (i < left_len)
  {
    buf[i + j] = Array[L + i];
    i++;
  }

  while (j < right_len)
  {
    buf[i + j] = Array[M + j];
    j++;
  }

  memcpy(Array + L, buf, sizeof(int) * (i + j));
}

void MergeSort( int *Array, int L, int R )
{
  int m;
  if (R - L <= 1)
    return;

  m = (L + R) / 2;
  MergeSort(Array, L, m);
  MergeSort(Array, m, R);
  Merge(Array, L, m, R);
}

int main( void )
{
  int N, i, j;
  int *a;

  scanf("%d", &N);
  a = malloc(sizeof(int) * N);
  for (i = 0; i < N; i++)
    scanf("%d", &a[i]);

  MergeSort(a, 0, N);

  printf("%I64d\n", inverse_count);

  free(a);
  return 0;
}
