#include <stdio.h>

int main(void)
{
    int a;
    int * p;
    char b;
    a = 65;
    p = &a;
    b = *p;
    printf("%d\n", b);
    printf("\n");
    
    a = 3;
    * p = &a;
    int **q = &p;
    int ***r = &q;
    **q = 4;
    printf("%d %d\n", *p, ***r);
    
  return 0;
}
