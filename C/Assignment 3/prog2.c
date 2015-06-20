// Eric Bachmeier
// 250738776
//
// Assignment 3
//
// Program 2

# include <stdio.h>

int main () {
    
    // initialize and create variables
    float loan = -1, yearRate = -1, monthPay = -1, n = -1, monthRate;
    int payCount = 0;
    
    // prompt user for loan amount and ensure it is positve
    while (loan < 0) {
        printf("Enter the amount of the loan: ");
        scanf("%f", &loan);
    }
    
    // prompt user for the interest rate (yearly) and validate that it is positive
    while (yearRate < 0) {
        printf("Enter the yearly interest rate as a decimal: ");
        scanf("%f", &yearRate);
    }
    
    // prompt user for the monthly payment amount and validate that it is positive
    while (monthPay < 0) {
        printf("Enter the monthly payment amount: ");
        scanf("%f", &monthPay);
    }
    
    // prompt user for the number of monthly payments and validate that it is positive
    while (n < 0) {
        printf("Enter the number of monthly payments: ");
        scanf("%f", &n);
    }
    
    // calculate the monthly interest rate
    monthRate = yearRate / 12;
    
    // calculate the interest while the amount is more than the monthly payment and depending on the n value
    while(loan > 0 && payCount < n) {
        loan = (loan * (1 + monthRate)) - monthPay;
        if (loan < 0) {
            printf("The balance on the loan is: $0\n");
        }
        else
            printf("The balance on the loan is: $%.2f\n", loan);
        payCount++;
    }
    
    // print the amount of the last payment to the loan if it was a partial payment
    if (loan < 0) {
        printf("The last payment is: $%.2f\n", monthPay + loan);
    }
    else
        printf("The balance is not yet paid off\n");
    
    return 0;
}
