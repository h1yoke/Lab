
#include <stdio.h>
#include <stdlib.h>

int main( void )
{
  int tab[101] = {0}, in, size, i, j;

  size = fscanf(stdin, "%d", &in);
  while (size > 0)
  {
    tab[in]++;
    size = fscanf(stdin, "%d", &in);
  }

  for (i = 0; i < 101; i++)
    for (j = 0; j < tab[i]; j++)
      printf("%d ", i);
  printf("\n");
  return 0;
}
