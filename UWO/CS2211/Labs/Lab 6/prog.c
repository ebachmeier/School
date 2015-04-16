#include <stdio.h>
#include <math.h>

int main()
{
  int i, x;

  printf("Number \t Square Root\n\n");

  for (i=0; i<=30; i++) {
       x = sqrt(1.0 * i);
       printf("%d \t\t %d \n", i, x);
  }   
  return 0;
}
