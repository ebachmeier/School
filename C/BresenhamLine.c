/* 
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3388 Computer Graphics I
 * Western University
 * Doctor Steven S. Beauchemin
 * September 18, 2015
 *
 * Program which uses X11 and implements Bresenham's integer line drawing algorithm.
 * Compile and Run:    $ cc -o program program1.c -I/opt/X11/include -L/opt/X11/lib -lX11
 *                     $ ./program
 */

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLS  512
#define ROWS  512
#define POSX  0
#define POSY  0
#define NUM 1024

typedef struct {
    int x, y;
} intpoint;

Display *InitX(Display *d, Window *w, int *s) {
    d = XOpenDisplay(NULL) ;
    if(d == NULL) {
        printf("Cannot open display\n") ;
        exit(1) ;
    }
    *s = DefaultScreen(d) ;
    *w = XCreateSimpleWindow(d, RootWindow(d, *s), POSX, POSY, COLS, ROWS, 1, BlackPixel(d, *s), WhitePixel(d, *s)) ;
    Atom delWindow = XInternAtom(d, "WM_DELETE_WINDOW", 0) ;
    XSetWMProtocols(d, *w, &delWindow, 1) ;
    XSelectInput(d, *w, ExposureMask | KeyPressMask) ;
    XMapWindow(d, *w) ;
    return(d) ;
}


void SetCurrentColorX(Display *d, GC *gc, unsigned int r, unsigned int g, unsigned int b) {
    XSetForeground(d, *gc, r << 16 | g << 8 | b) ;
}


void SetPixelX(Display *d, Window w, int s, int i, int j) {
    XDrawPoint(d, w, DefaultGC(d, s), i, j) ;
}


void QuitX(Display *d, Window w) {
    XDestroyWindow(d,w) ;
    XCloseDisplay(d) ;
}



void exchangeInt(int *a, int *b)
{ int t ;
    t = *a ;
    *a = *b ;
    *b = t ;
}

void exchangePoint(intpoint *p1, intpoint *p2)
{ intpoint t ;
    t = *p1 ;
    *p1 = *p2 ;
    *p2 = t ;
}

/*
 * Bresenham method
 * Author: Eric Bachmeier
 * Created: September 18, 2015
 * Purpose: This method draws a line implementing Bresenham's integer algorithm
 * Input Parameters:
 *    *d - reference to the Display
 *     s - the created Window that will be the canvas
 *     s - the colour of the line to be drawn
 *    p1 - the starting point for the line
 *    p2 - the end point for the line
 * Output: A line with colour s from the starting point p1 to p2 on the created window w
 */
void Bresenham(Display *d, Window w, int s, intpoint p1, intpoint p2) {

    // initialize variables for the difference in x and y, delta for Pi, the increment amount of x and y, the actual calculated increase, and the x and y values of the start and ending points
    int diffX, diffY, delta, incrementX, incrementY, amountX, amountY, startX, startY, endX, endY;
    
    // get the x and y values from the starting and end point structures
    startX = p1.x;
    startY = p1.y;
    endX = p2.x;
    endY = p2.y;
    
    // get the difference between the starting and ending x / y values
    diffY = abs(endY - startY);
    diffX = abs(endX - startX);
    
    // if the slope on the x axis is decreasing
    if (startX < endX) {
        incrementX = 1;
    }
    // slope is increasing
    else {
        incrementX = -1;
    }
    
    // if the slope on the y axis is decreasing
    if (startY < endY) {
        incrementY = 1;
    }
    // slope is increasing
    else {
        incrementY = -1;
    }
    
    // if the slope is not steep
    if (diffX > diffY) {
        
        // calculate the y axis while moving along the x axis with Pi (delta)
        delta = 2 * diffY - diffX;
        
        // moving from the start to end point given as parameter until points are equal
        while (startX != endX) {
            
            // if Pi (delta) is greater than zero
            if (delta > 0) {
                // increment on the y axis
                startY += incrementY;
                // plot the pixel
                SetPixelX(d, w, s, startX, startY);
                // increment Pi by the calculated amount where Yi + 1 - Yi = 1
                delta += 2 * diffY - 2 * diffX;
            }
            
            // if Pi (delta) is less than or equal to zero
            else {
                // plot the pixel
                SetPixelX(d, w, s, startX, startY);
                // increment Pi by the calculated amount where Yi + 1 - Yi = 0
                delta += 2 * diffY;
            }
            
            // increment on the x axis
            startX += incrementX;
        }
    }
    
    // the slope must be steep here
    else {
        
        // calculate the x axis while moving along the y axis with Pi (delta)
        delta = 2 * diffX - diffY;
        
        // moving from the start to end point given as parameter until points are equal
        while (startY != endY) {
            
            // if Pi (delta) is greater than zero
            if (delta > 0) {
                // increment on the x axis
                startX += incrementX;
                // plot the pixel
                SetPixelX(d, w, s, startX, startY);
                // increment Pi by the calculated amount where Xi + 1 - Xi = 1
                delta += 2 * diffX - 2 * diffY;
            }
            
            // if Pi (delta) is less than or equal to zero
            else {
                // plot the pixel
                SetPixelX(d, w, s, startX, startY);
                // increment Pi by the calculated amount where Xi + 1 - Xi = 0
                delta += 2 * diffX;
            }
            
            // increment on the y axis
            startY += incrementY;
        }
    }

    

}

/*
 * Main method
 * Purpose: Utilizes the functions above to draw circles on the canvas window
 * Input Parameters: None
 * Output: A 512 x 512 white window with circles drawn on it
 */
int main() {

    Display *d ;
    Window w ;
    XEvent e ;
    int s ;
    intpoint p1, p2 ;

    unsigned int r, g, b ;
    double t, dt ;
    
    r = g = b = 0 ;
    dt = 2.0*M_PI/2000.0 ;

    d = InitX(d, &w, &s) ;
    
    SetCurrentColorX(d, &(DefaultGC(d, s)), r, g, b) ;
    
    while (1) {
        XNextEvent(d, &e) ;
        if (e.type == Expose)
            for (t = 0.0 ; t < 2.0*M_PI;) {
                p1.x = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t)) ;
                p1.y = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t)) ;
                t += dt ;
                p2.x = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t)) ;
                p2.y = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t)) ;
                Bresenham(d, w, s, p1, p2) ;
            }
        if(e.type == KeyPress)
            break ;
        if(e.type == ClientMessage)
        break ;
  }
  QuitX(d,w) ;
}