#include <stdio.h>

#define CUBE(x) (printf("%d\n", (x) * (x) * (x)))

#define REMAINDER(n) (printf("%d\n", (n) %= 4))

#define PRODUCT(x,y) ((x) * (y) < 100 ? printf("1\n") : printf("0\n"))

#define SIZE(a) (printf("%d\n", sizeof(a) / sizeof(a[0])))

int main(void)
{
    int a = 2;
    CUBE(a);
    
    int b = 5;
    REMAINDER(b);
    
    PRODUCT(a,b);
    
    int arr[4];
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    SIZE(arr);
    
    return 0;
}

