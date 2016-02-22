// Eric Bachmeier
//
// Assignment 3
//
// Program 1

# include <stdio.h>

// define true and false variables for time validation
# define TRUE 1
# define FALSE 0

int main () {
    
    // create and initialize variables
    int time, duration, dayHour, dayMinute, durHour, durMinute, h, m, x;
    int validTime = FALSE, validDuration = FALSE;
    
    // loop until the day time is valid
    while(!validTime) {
        
        // initialize day time
        printf("Enter a valid day time in 24-hour format: ");
        scanf("%d", &time);
        
        // initialize day hour and minutes
        dayHour = time / 100;
        dayMinute = time % 100;
        
        // check if user input is valid day time
        if (dayHour < 24 && dayMinute < 60 && time > (-1)) {
            validTime = TRUE;
        }
        else {
            printf("Please enter a VALID 24-hour time. \n");
        }
    }
    
    // loop until the time duration is valid
    while(!validDuration) {
        
        // initialize time duration
        printf("Enter a valid time duration: ");
        scanf("%d", &duration);
        
        // initialize time hour and minute
        durHour = duration / 100;
        durMinute = duration % 100;
        
        // check if the user input is valid
        if (durMinute < 60) {
            validDuration = TRUE;
        }
        else {
            printf("Please enter a VALID time duration. \n");
        }
    }
    
    // calculate full hours worth of minutes
    x = (dayMinute + durMinute) / 60;
    // calculate the hours and minutes for the updated time
    m = (dayMinute + durMinute) % 60;
    // if minutes are negative, increment them by one hour
    if (m < 0) {
        m += 60;
        // calculate hours for negative minutes scenario
        h = (dayHour + durHour + x - 1) % 24;
    }
    else {
        // calculate hours including any hours from the minutes calculation
        h = (dayHour + durHour + x) % 24;
    }
    // if hours are negative, increment them by 24 hours
    if (h < 0) {
        h += 24;
    }
    
    // print the incremented time using two significant digits
    printf("The new time is: %.2d%.2d\n", h, m);
}



