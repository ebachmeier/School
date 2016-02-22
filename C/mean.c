// Eric Bachmeier
//
// Assignment 4
//
// Program 1

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

// define true and false constants
# define FALSE 0
# define TRUE 1

int main (void) {
    
    // create and initialize variables
    double x, y, total = 0.00, sdSum = 0.00, sdTerms[10], pi;
    int i, p, j, inside, n = -1, valid = FALSE;
    
    // initialize random number generator
    srand((unsigned) time(NULL));
    
    // loop for input validation
    while(!valid){
        printf("Enter a large number: ");
        scanf("%d", &n);
        if (n > -1)
            valid = TRUE;
        else
            printf("Please enter a positive number for N.\n");
    }
    
    printf("\n");
    // calculate pi value 10 times
    for (p = 0; p < 10; p++){
        
        inside = 0; // reset points inside counter to zero
        
        // loop for n amount of points
        for (i = 0; i < n; i++){
            
            // assign two random numbers between 0.00 and 1.00
            x = (double)rand()/(RAND_MAX);
            y = (double)rand()/(RAND_MAX);
        
            // increment if the point is inside the circle
            if ((x * x) + (y * y) <= 1){
                inside++;
            }
        }
    
        // calculate ratio of points inside to points calculated total for pi
        // multiply by 4 to compute pi value
        pi = (double)inside * 4 / i;
    
        // print value of pi to screen
        printf("Pi = %.10f\n", pi);
        
        // add pi value to array to later calculate standard deviation
        sdTerms[p] = pi;
        
        // add pi value to total to later calculate mean
        total += pi;
    }
    
    // calulate and print the mean
    printf("\nThe mean is %.10f\n", (double)total / 10);
    
    // calculate the standard deviation sum
    for (j = 0; j < 10; j++){
        sdSum += pow((sdTerms[j] - ((double)total / 10)), 2);
    }
    
    // print and compute the standard deviation
    printf("\nThe sd is %.4f\n\n", sqrt((double)sdSum / 10));
    
}



