struct
{ double a;
    union
    { double b;
        int c;
        int d;
    } e;
    char f[8];
} s;

union
{ double a;
    struct
    { double b;
        int c;
        int d;
    } e;
    char f[8];
} u;

enum {frosh, soph = 2, jr, sr = 10} class;

#include<stdio.h>
#include<stdlib.h>

int main(void) {
    int one = sizeof(s);
    int two = sizeof(u);
    printf("u: %d\ns: %d\n\n", two, one);
    printf("%d\n", frosh);
    printf("%d\n", soph);
    printf("%d\n", jr);
    printf("%d\n", sr);
    for(class = frosh; class <=sr; ++class)
        printf("%d\n", class);
    
}

