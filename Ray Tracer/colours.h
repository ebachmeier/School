/*            PURPOSE : Functions and structures for raytracer with colours.

        PREREQUISITES : NONE

*/

#include <X11/Xlib.h>

#define Ex               12.0       // Position of camera frame of reference
#define Ey               12.0
#define Ez               3.0

#define Gx               0.0        // Camera gaze direction
#define Gy               0.0
#define Gz               0.0

#define UPx              0.0        // Up vector direction
#define UPy              0.0
#define UPz              1.0

#define Lx               0.0        // Position of the light source
#define Ly               0.0
#define Lz               10.0

#define THETA            45.0       // Viewing angle
#define ASPECT           1.5        // Aspect ratio

/* Object definitions */
#define INFINITE_PLANE   0
#define PLANE            1
#define SPHERE           2

#define EPSILON          0.00001
#define N_OBJECTS        1024
#define MAX_INTENSITY    255.0

#define Near             1.0
#define Far              25.0

typedef struct {
    int width, height ;
} window_t ;

typedef struct {
    dmatrix_t UP ;
    dmatrix_t E ;
    dmatrix_t G ;
    dmatrix_t u, v, n ;
} camera_t ;

typedef struct {
    double r, g, b ;
} colour_t ;

typedef struct {
    int type ;
    double (*intersection_function)(dmatrix_t *,dmatrix_t *) ;
    dmatrix_t M, Minv ;
    colour_t specular_colour, diffuse_colour, ambient_colour, absorb_colour ;
    double reflectivity, absorb_coeff, density, specular_coeff, diffuse_coeff, ambient_coeff, f ;
} object_t ;

typedef struct {
    dmatrix_t position ;
    colour_t colour ;
    colour_t intensity ;
} light_t ;

colour_t colour_init(double r, double g, double b) {
    
    colour_t s ;
    
    s.r = r ;
    s.g = g ;
    s.b = b ;
    
    return s ;
}

colour_t colour_mult(colour_t c1, colour_t c2) {
    
    colour_t s ;
    
    s.r = c1.r*c2.r ;
    s.g = c1.g*c2.g ;
    s.b = c1.b*c2.b ;
    
    return s ;
}

colour_t colour_add(colour_t c1, colour_t c2) {
    
    colour_t s ;
    
    s.r = c1.r + c2.r ;
    s.g = c1.g + c2.g ;
    s.b = c1.b + c2.b ;
    
    return s ;
}

colour_t colour_scale(double a, colour_t c) {
    
    colour_t s ;
    
    s.r = a*c.r ;
    s.g = a*c.g ;
    s.b = a*c.b ;
    
    return s ;
}

double infinite_plane_zinter(dmatrix_t *e, dmatrix_t *d, double z) {
    
    if (d->m[3][1] >= 0.0) return -1.0 ; 
    double t = (z - e->m[3][1])/d->m[3][1] ;
    return (t > EPSILON) ? t:-1.0 ;
    
}

double infinite_plane_intersection(dmatrix_t *e, dmatrix_t *d) {
    if (d->m[3][1] >= 0.0) return -1.0 ;
    else return -1.0*e->m[3][1]/d->m[3][1] ;
}

Display *InitX(Display *d, Window *w, int *s, window_t *Window) {
    
    d = XOpenDisplay(NULL) ;
    if(d == NULL) {
        printf("Cannot open display\n") ;
        exit(1) ;
    }
    *s = DefaultScreen(d) ;
    *w = XCreateSimpleWindow(d,RootWindow(d,*s),0,0,Window->width,Window->height,1,BlackPixel(d,*s),WhitePixel(d, *s)) ;
    Atom delWindow = XInternAtom(d,"WM_DELETE_WINDOW",0) ;
    XSetWMProtocols(d,*w,&delWindow,1) ;
    XSelectInput(d,*w,ExposureMask | KeyPressMask) ;
    XMapWindow(d,*w) ;
    return(d) ;
}

void SetCurrentcolourX(Display *d, GC *gc, unsigned int r, unsigned int g, unsigned int b) {
    
    XSetForeground(d,*gc,r << 16 | g << 8 | b) ;
}

void SetPixelX(Display *d, Window w, int s, int i, int j) {
    
    XDrawPoint(d,w,DefaultGC(d,s),i,j) ;
}

void QuitX(Display *d, Window w) {
    
    XDestroyWindow(d,w) ;
    XCloseDisplay(d) ;
}