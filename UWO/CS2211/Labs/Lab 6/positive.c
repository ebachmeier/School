#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x, op;
	printf ("Enter a positve integer value: ");
	scanf ("%d", &x);
    if (x <= 0) {
        printf("The number entered was not a positve integer.\n");
        exit(1);
    }
    op = 0;
    while (x != 1){
        op += 1;
        if (x % 2 > 0) {
            x = x * 3 + 1;
        }
        else
            x /= 2;
        printf("%d\n", x);
    }
    printf("There were %d operations performed.\n", op);
	return 0;
}

