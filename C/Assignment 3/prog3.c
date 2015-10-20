// Eric Bachmeier
//
// Assignment 3
//
// Program 3

# include <stdio.h>

int main () {
    
    // initialize and create variables
    float input = -1;
    double e = 1, fact = 1;
    int term = 0, current;
    
    // prompt user for float input
    while (input < 0) {
        printf("Enter a positive floating-point number: ");
        scanf("%f", &input);
    }
    
    // calculate e until (1/fact) is less than the input
    while (input <= (1/fact)) {
        
        // increment the number of terms used
        term++;
        current = 1;
        fact = 1;
        
        // calculate the factorial for current value
        while (current <= (term)) {
            fact = (current * fact);
            current++;
        }
        // add the next term to e
        e += (1/fact);
    }
    
    // print the final e value
    printf("The approximated value of e is: %.15f\n", e);
    // print the number of terms required
    printf("The number of terms required to generate e was %d\n", term);
    
    return 0;
}

