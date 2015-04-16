#include<stdio.h>
#include<stdlib.h>

int *create_array(int n, int initial_value);

int main(void)
{
    create_array(10, 1);
}

int *create_array(int n, int initial_value)
{
    int *array = malloc(sizeof(initial_value) * n);
    int *pointer = array;
    while (pointer - array < n)
        *pointer++ = initial_value;
    return array;
}
