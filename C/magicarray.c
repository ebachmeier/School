// Eric Bachmeier
//
// Assignment 4
//
// Program 2

# include <stdio.h>

// define true and false constants
# define FALSE 0
# define TRUE 1

int main (void) {
    
    // create and initialize variables
    int n = 0, valid = FALSE, x, y, i;
    
    // loop for input validation
    while(!valid){
        printf("Enter the size of magic square: ");
        scanf("%d", &n);
        // validate for odd integer between 1 and 99
        if (n > 0 && n < 100 && n % 2 != 0)
            valid = TRUE;
        else
            printf("Please enter a valid odd integer.\n");
    }
    
    // create and initialize magic array
    int array[n][n];
    
    // set all the values in the array to 0
    for(x = 0; x < n; x++){
        for(y = 0; y < n; y++){
            array[x][y] = 0;
        }
    }
    
    // set x and y to start in first row middle column
    x = 0, y = n / 2, i = 2;
    
    // set first value to 1
    array[x][y] = 1;
    
    while(i < (n * n) + 1){
        
        // increment up a row and right one column
        x--;
        y++;
        
        // out of bounds check
        if (x < 0)
            x = n - 1;
        if (y > n - 1)
            y = 0;
        
        // if the spot isnt already filled, insert the next i value
        if (array[x][y] == 0)
            array[x][y] = i++;
        else {
            // jump to next row if spot is filled
            x += 2;
            y--;
            // out of bounds check
            if (x > n - 1)
                x -= n;
            if (y < 0)
                y = n - 1;
            
            // add the value of the array to the other position
            array[x][y] = i++;
        }
    }
    
    // print the magic array
    printf("\n");
    for(x = 0; x < n; x++){
        for(y = 0; y < n; y++){
            if (y == 0)
                printf("%d", array[x][y]);
            else
                printf("\t%d", array[x][y]);
        }
        // print a new line after every row
        printf("\n");
    }
    printf("\n");
}



