#include <stdio.h>

int main(void)
{
  char a[10] = {0}, b[10] = {0};

  strcpy(a,"ABCDEFGHI");
  a[4] = 0;
  strcpy(b, a);

  printf("%s\n", a);
  printf("%s\n", b);

  printf("\n");
  a[4] = 'X';
  b[4] = 'X';

  printf("%s\n", a);
  printf("%s\n", b);

  return 0;
}
