#include <stdio.h>

int subtraiBit(int b1, int b2, int b3, int *cout)
{
  int c = b3 - b1 - b2;
  if (c < 0)
    c = 1, *cout = 1;
  return c;
}

int main()
{
  int cout = 0;
  int aux = subtraiBit(0, 1, 0, &cout);
  printf("%d %d", aux, cout);
  return 0;
}