#include <stdio.h>

int main()
{
	int x, start, new;
	printf ("Enter the initial population: ");
	scanf ("%d", &start );
    
    new = start;
    x = 1;
    
    printf("The initial population is %d\n", new);
	while (new <= 30000) {
		new = new*1.1;
        printf("The population after %d year(s) is %d\n", x, new);
        x += 1;
    }
	
	return 0;
}
