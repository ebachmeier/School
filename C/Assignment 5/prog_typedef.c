// Eric Bachmeier
//
// Assignment 5

# include <stdio.h>
# include <stdlib.h>

// create the tag complex_t for structure with real and imaginary numbers
typedef struct {
    double real;
    double imaginary;
} complex_t;

// function prototypes
complex_t multiply(complex_t a, complex_t b);
complex_t* divide(complex_t *a, complex_t *b);

int main (void) {
    
    // declare the complex number structures
    complex_t a, b, product, *quotient;
    
    printf("\n");
    // prompt the user for two complex numbers
    printf("Enter the real and imaginary components of the first complex number.\n\n\t(a1) + i(b1)\n");
    printf("\t a1 = ");
    scanf("%lf", &a.real);
    printf("\t b1 = ");
    scanf("%lf", &a.imaginary);
    printf("\n");
    printf("Enter the real and imaginary components of the second complex number.\n\n\t(a2) + i(b2)\n");
    printf("\t a2 = ");
    scanf("%lf", &b.real);
    printf("\t b2 = ");
    scanf("%lf", &b.imaginary);
    printf("\n");
    
    // calculate the product and print to screen
    product = multiply(a, b);
    printf("The product of the two numbers is:\t%.4lf", product.real);
    if (product.imaginary >= 0) {
        printf(" + i%.4lf\n", product.imaginary);
    }
    else
        // print a negative sign with postive value of the nagative imaginary number
        printf(" - i%.4lf\n", product.imaginary -= (product.imaginary * 2));
    printf("\n");
    
    // calculate the quotient and print to screen
    quotient = divide(&a, &b);
    // access the real and imaginary members by referring to their pointer
    printf("The quotient of the two numbers is:\t%.4lf", quotient->real);
    if (quotient->imaginary >= 0) {
        printf(" + i%.4lf\n", quotient->imaginary);
    }
    else
        // print a negative sign with postive value of the nagative imaginary number
        printf(" - i%.4lf\n", quotient->imaginary -= (quotient->imaginary * 2));
    printf("\n");
}

// function for muliplication of two complex numbers
complex_t multiply(complex_t a, complex_t b) {
    
    // create structure x to return the product
    complex_t ans;
    
    // set variables for the real and imaginary parts of the two parameters
    double aReal = a.real, bReal = b.real, aImag = a.imaginary, bImag = b.imaginary;
    
    // calculate the real and imaginary parts of the product
    ans.real = (aReal * bReal) - (aImag * bImag);
    ans.imaginary = (bReal * aImag) + (aReal * bImag);
    
    // return the complex number
    return ans;
}

// function for division of two complex numbers
complex_t* divide(complex_t *a, complex_t *b) {
    
    // create pointer to the memory location created by malloc func
    // pointer will be of type complex_t
    complex_t *ans = malloc(sizeof(complex_t));
    
    // set variables for the real and imaginary parts of the two parameters by using the pointers referenced by a and b
    double aReal = a->real, bReal = b->real, aImag = a->imaginary, bImag = b->imaginary;
    
    // calculate the real and imaginary parts of the quotient
    // -> is needed instead of . to access the member of the structure referenced by pointer
    ans->real = ((aReal * bReal) + (aImag * bImag)) / ((bReal * bReal) + (bImag * bImag));
    ans->imaginary = ((bReal * aImag) - (aReal * bImag)) / ((bReal * bReal) + (bImag * bImag));
    
    // return the pointer to the memory address created by malloc where the answer is stored
    return ans;
}
