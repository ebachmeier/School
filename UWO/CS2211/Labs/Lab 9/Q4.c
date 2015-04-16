#include <stdio.h>

#ifdef DEBUG
#define PRINT_DEBUG(n) printf("Value of " #n ": %d\n", n)
#else
#define PRINT_DEBUG(n)
#endif


int main(void)
{

int i = 1, j = 2, k = 3;

#ifdef DEBUG
  printf("DEBUG is defined:\n");
#else
  printf("DEBUG is not defined:\n");
#endif

PRINT_DEBUG(i);
PRINT_DEBUG(j);
PRINT_DEBUG(k);
PRINT_DEBUG(i + j);
PRINT_DEBUG(2 * i + j - k);

return 0;
}
