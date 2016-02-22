// Eric Bachmeier
//
// Assignment 4
//
// Program 3

# include <stdio.h>

// function prototype
void pay_amount (int dollars, int *twenties, int *tens, int *fives, int *toonies, int *loonies);

int main (void) {
    
    // create and initialize variables
    int dollars = -1, twenties, tens, fives, toonies, loonies;
    
    // get positive dollar amount from user
    while (dollars < 0){
        printf("Enter the amount of dollars: $");
        scanf("%d", &dollars);
        if (dollars < 0)
            printf("Please enter a positive amount of dollars.\n");
    }
    
    // call the pay amount function
    pay_amount (dollars, &twenties, &tens, &fives, &toonies, &loonies);
    
    // print the calculated values to the screen
    printf("\nThe smallest number of bills and coins to make up $%d is: \n", dollars);
    printf("%d x $20's\n", twenties);
    printf("%d x $10's\n", tens);
    printf("%d x $5's\n", fives);
    printf("%d x $2's\n", toonies);
    printf("%d x $1's\n\n", loonies);
}

// function declaration
void pay_amount (int dollars, int *twenties, int *tens, int *fives, int *toonies, int *loonies) {
    
    // calculate the amount of twenties needed for dollar amount
    // change the amount in memory using pointer
    *twenties = dollars / 20;
    // increment dollars amount for next bill / coin
    dollars %= 20;
    
    *tens = dollars / 10;
    dollars %= 10;
    
    *fives = dollars / 5;
    dollars %= 5;
    
    *toonies = dollars / 2;
    dollars %= 2;
    
    // the amount of loonies is the amount of leftover dollars
    *loonies = dollars;
}


