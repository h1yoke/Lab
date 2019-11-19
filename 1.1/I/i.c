
#include <stdio.h>
#include <math.h>

double f( double X )
{
  return X * X + sqrt(X);
}

double BinSearch( double C )
{
  double l = 0.0, r = C;
  int i;

  for (i = 0; i < 100; i++)
  {
    double m = (l + r) / 2.0;

    if (f(m) < C)
      l = m;
    else
      r = m;
  }
  return (r + l) / 2.0;
}

int main( void )
{
  double c;

  scanf("%lf", &c);
  printf("%f\n", BinSearch(c));
  return 0;
}
