
#include <stdio.h>
#include <math.h>

#define sqr(X) ((X) * (X))

typedef struct
{
  double X, Y;
} VEC;

double dist( VEC V1, VEC V2 )
{
  return sqrt(sqr(V2.X - V1.X) + sqr(V2.Y - V1.Y));
}

VEC MakeVec( double X, double Y )
{
  VEC v;
  v.X = X;
  v.Y = Y;

  return v;
}

double f( double X, double V1, double V2, double A )
{
  return
    dist(MakeVec(0.0, 1.0), MakeVec(X, A)) / V1 +
    dist(MakeVec(X, A), MakeVec(1.0, 0.0)) / V2;
}

double TernarySearch( double V1, double V2, double A )
{
  double
    l = 0.0,
    r = 1.0;

  for (int i = 0; i < 100; i++)
  {
    double
      m1 = l + (r - l) / 3.0,
      m2 = r - (r - l) / 3.0;

    if (f(m1, V1, V2, A) < f(m2, V1, V2, A))
      r = m2;
    else
      l = m1;
  }
  return (r + l) / 2.0;
}

int main( void )
{
  double vp, vf, a;

  scanf("%lf %lf %lf", &vp, &vf, &a);
  printf("%f\n", TernarySearch(vp, vf, a));
  return 0;
}
