/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 4
 * CS3388 Computer Graphics I
 * Western University
 * Doctor Steven S. Beauchemin
 * December 4, 2015
 *
 * Program which uses X11 to implement a recursive ray tracer that can create a number of generic objects with reflection and refraction
 * Compile and Run:    $ cc -std=c99 -o raytracer raytracer.c -I/opt/X11/include -L/opt/X11/lib -lX11 -lm
 *                     $ ./raytracer
 */

#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "colours.h"

#define N_SPHERES 6

#define H 600        // Window height in pixels

#define DEPTH 1

#define REFL 0.7
#define AC 0.15
#define TRAN 0.7		// Density

#define LIGHT_INTENSITY 1.2

/* Variable declarations for the number of objects in the scene */
object_t object[N_OBJECTS];
dmatrix_t Ts[N_OBJECTS];
int nobjects = 0;

/* Function prototypes */
colour_t refractionColour(light_t *light, object_t *object, dmatrix_t *Wi, colour_t background, int depth,
             dmatrix_t *V, dmatrix_t *N, int h, colour_t reflection);

/*
 * build_light
 * This function creates the light source for the ray tracer
 * Input: light object, position matrix, colour, and intensity
 * Output: A light object with the passed attributes
 */
light_t *build_light(light_t *light, dmatrix_t *position, colour_t colour, colour_t intensity) {
    dmat_alloc(&light->position,4,1) ;
    light->position = *position ;
    light->colour.r = colour.r ;
    light->colour.g = colour.g ;
    light->colour.b = colour.b ;
    light->intensity.r = intensity.r ;
    light->intensity.g = intensity.g ;
    light->intensity.b = intensity.b ;
    return light ;
}

/*
 * build_window
 * This function constructs a window with the designated height and aspect ratio
 * Input: a window, height integer, and aspect ratio
 * Output: A constructed window with the proper dimensions
 */
window_t *build_window(window_t *Window, int height, float aspect) {
    Window->height = height ;
    Window->width =  aspect*height ;
    return(Window) ;
}

/*
 * build_camera
 * This function builds the camera object for the view
 * Input: camera object, and a window
 * Output: 
 */
camera_t *build_camera(camera_t *Camera, window_t *Window) {

   dmat_alloc(&Camera->E,4,1) ;

    Camera->E.m[1][1] = Ex ;
    Camera->E.m[2][1] = Ey ;
    Camera->E.m[3][1] = Ez ;
    Camera->E.m[4][1] = 1.0 ;
    
    dmat_alloc(&Camera->G,4,1) ;
    
    Camera->G.m[1][1] = Gx ;
    Camera->G.m[2][1] = Gy ;
    Camera->G.m[3][1] = Gz ;
    Camera->G.m[4][1] = 1.0 ;
    dmat_alloc(&Camera->n,4,1) ;
    Camera->n = *dmat_normalize(dmat_sub(&Camera->E,&Camera->G)) ;
    Camera->n.l = 3 ;
    dmat_alloc(&Camera->UP,4,1) ;
    Camera->UP.l = 3 ;
    Camera->UP.m[1][1] = UPx ;
    Camera->UP.m[2][1] = UPy ;
    Camera->UP.m[3][1] = UPz ;
    Camera->UP.m[4][1] = 1.0 ;
    dmat_alloc(&Camera->u,4,1) ;
    Camera->u = *dmat_normalize(dcross_product(&Camera->UP,&Camera->n)) ;
    Camera->v = *dmat_normalize(dcross_product(&Camera->n,&Camera->u)) ;
    return(Camera) ;
}

/*
 * plane_intersection
 * This function computes the intersection with a plane
 * Input: Two vectors e and d
 * Output: A decimal for the intersection or -1.0 if none
 */
double plane_intersection(dmatrix_t *e, dmatrix_t *d) {
    double t ;
    dmatrix_t *intersection ;
    if (d->m[3][1] >= 0.0) {
        return -1.0 ;
    }
    else {
        t = -1.0*e->m[3][1]/d->m[3][1] ;
        intersection = intersection_coordinates(e,d,t) ;
        if ((fabs(intersection->m[1][1]) < 1.0) && (fabs(intersection->m[2][1]) < 1.0)) {
            delete_dmatrix(intersection) ;
            return t ;
        }
        else {
            delete_dmatrix(intersection) ;
            return -1.0 ;
        }
    }
}

/*
 * sphere_intersection
 * This function computes the intersection with a sphere
 * Input: Two vectors e and d
 * Output: A decimal for the intersection or -1.0 if none
 */
double sphere_intersection(dmatrix_t *e, dmatrix_t *d) {
    double a = dot_product(d,d) ;
    double b = dot_product(e,d) ;
    double c = dot_product(e,e) - 1.0 ;
    double discriminant = b*b - a*c ;
    if (discriminant < 0.0) {
        return -1.0 ;
    }
    else {
        if (discriminant < EPSILON) {
            return -b/a ;
        }
        else {
            double t1 = -b/a - sqrtl(discriminant)/a ;
            double t2 = -b/a + sqrtl(discriminant)/a ;
            if (t1 < t2) {
                if (t1 > EPSILON) {
                    return t1 ;
                }
                else {
                    return -1.0 ;
                }
            }
            else {
                return t2 ;
            }
        }
    }
}

/*
 * normal_to_surface
 * This function computes the surface normals for specific shapes
 * Input: An object and an intersection
 * Output: A vector with the new points x, y, z
 */
dmatrix_t *normal_to_surface(object_t *object, dmatrix_t *intersection) {
    dmatrix_t *normal ;
    normal = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(normal,4,1) ;
    switch ((*object).type) {
            
        case PLANE          :   normal->m[1][1] = 0.0 ;
                                normal->m[2][1] = 0.0 ;
                                normal->m[3][1] = 1.0 ;
                                break ;
            
        case INFINITE_PLANE :   normal->m[1][1] = 0.0 ;
                                normal->m[2][1] = 0.0 ;
                                normal->m[3][1] = 1.0 ;
                                normal->m[4][1] = 0.0 ;
                                break ;
            
        case SPHERE         :   normal->m[1][1] = intersection->m[1][1] ;
                                normal->m[2][1] = intersection->m[2][1] ;
                                normal->m[3][1] = intersection->m[3][1] ;
                                normal->m[4][1] = 0.0 ;
                                break ;
            
        default				: 	break;
            
    }
    return normal ;
}

/*
 * find_min_hit_time
 * This function computes the hit time for a given ray
 * Input: Array of objects and the number of objects
 * Output: An integer position
 */
int find_min_hit_time(double t0[N_OBJECTS], int n) {
    double min_t = 20.0*Far ;
    int position = -1 ;
    for(int i = 0 ; i < n ; i++) {
        if (t0[i] != -1.0) {
            if (t0[i] < min_t) {
                min_t = t0[i] ;
                position = i ;
            }
        }
    }
    return position ;
}

/*
 * vector_of_reflection
 * This function computes the vector of reflection for a given ray
 * Input: Two vectors S and N
 * Output: A new vector for the reflected ray
 */
dmatrix_t *vector_of_reflection(dmatrix_t *S, dmatrix_t *N) {
    
    dmatrix_t *r ;
    
    r = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(r,4,1) ;
    
    double sn = 2.0*dot_product(N,S) ;
    
    r->m[1][1] = -1.0*S->m[1][1] + sn*N->m[1][1] ;
    r->m[2][1] = -1.0*S->m[2][1] + sn*N->m[2][1] ;
    r->m[3][1] = -1.0*S->m[3][1] + sn*N->m[3][1] ;
    r->m[4][1] = 0.0 ;
       
    return r ;
}

/*
 * ray_direction
 * This function computes the intersection with a sphere
 * Input: Two vectors e and d
 * Output: A decimal for the intersection or -1.0 if none
 */
dmatrix_t *ray_direction(camera_t *Camera, window_t *Window, double height, double width, double i, double j) {
    
    dmatrix_t *d ;
    
    d = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(d,4,1) ;

    d->m[1][1] = -1.0*Near*Camera->n.m[1][1] +
    width*(2.0*i/Window->width - 1.0)*Camera->u.m[1][1] +
    height*(2.0*j/Window->height - 1.0)*Camera->v.m[1][1] ;

    d->m[2][1] = -1.0*Near*Camera->n.m[2][1] +
    width*(2.0*i/Window->width - 1.0)*Camera->u.m[2][1] +
    height*(2.0*j/Window->height - 1.0)*Camera->v.m[2][1] ;

    d->m[3][1] = -1.0*Near*Camera->n.m[3][1] +
    width*(2.0*i/Window->width - 1.0)*Camera->u.m[3][1] +
    height*(2.0*j/Window->height - 1.0)*Camera->v.m[3][1] ;

    d->m[4][1] = 0.0 ;
    
    return(d) ;
}

/*
 * checkShadow
 * This function determines whether there will be a shadow on another object or not
 * Input: An object index, and two matrices for the ray collision point
 * Output: A decimal for the intersection or -1.0 if none
 */
bool checkShadow(dmatrix_t *We, dmatrix_t *d, int h) {

    bool result = false;   
    dmatrix_t *Te, *Td, *Ne, *Nd;
    double t;

    Nd = dmat_mult(&object[h].M, d) ;

    for(int k = 0; (k < N_SPHERES) && (!result); ++k) {
    
        if(h != k) {
        
            Te = dmat_mult(&object[k].Minv, We) ;
            Td = dmat_mult(&object[k].Minv, Nd) ;

            t = ((*(object[k].intersection_function))(Te,Td));

            if((0.0 <= t)&&(t <= 1.0)){
                result = true;
            }

            delete_dmatrix(Te) ;
            delete_dmatrix(Td) ;
        }
    }

    delete_dmatrix(Nd) ;    

    return result;
}

/*
 * buildLightDirectionMatrices
 * This function constructs the matrices for the direction of light from the source
 * Input: The created light object
 * Output: None
 */
void buildLightDirectionMatrices(light_t *light){
    for(int i = 0; i < nobjects; ++i){
        Ts[i] = *dmat_mult(&object[i].Minv,&light->position);
    }    
}

/*
 * ambientColour
 * This function calculates the ambient light of an object
 * Input: The light object and the object being intersected by the view ray
 * Output: The ambient colour of the object at the intersection point
 */
colour_t ambientColour(light_t *light, object_t *object){
    
    colour_t s = colour_scale(object->ambient_coeff, object->ambient_colour);
    s = colour_mult(s, light->intensity);
    s = colour_mult(s, light->colour);

    return s; 
}

/*
 * diffuseColour
 * This function calculates the diffuse light of an object
 * Input: The light object, the object being intersected by the view ray, and the angle of transmission
 * Output: The diffuse colour of the object at the intersection point
 */
colour_t diffuseColour(light_t *light, object_t *object, double Id){

    colour_t s = colour_scale(object->diffuse_coeff, object->diffuse_colour);
    s = colour_mult(s, light->intensity);
    s = colour_mult(s, light->colour);
    s = colour_scale(Id, s);

    return s;    
}

/*
 * specularColour
 * This function calculates the specular light of an object
 * Input: The light object, the object being intersected by the view ray, and the angle of transmission
 * Output: The specular colour of the object at the intersection point
 */
colour_t specularColour(light_t *light, object_t *object, double Is){

    colour_t s = colour_scale(object->specular_coeff, object->specular_colour);
    s = colour_mult(s, light->intensity);
    s = colour_mult(s, light->colour);
    s = colour_scale(Is, s);
    s = colour_scale(object->absorb_coeff, s);    
        
    return s;    
}

/*
 * refract
 * This function calculates the refraction vector when a view ray passes through a transparent object
 * Input: The direction vector, surface normal, density, D.N, and a matrix to hold the reflection vector
 * Output: False if their is total internal reflection, true otherwise
 */
bool refract(dmatrix_t *D, dmatrix_t *N, int sgn, double n, double Ir, dmatrix_t *T){    

    double disc = 1 - n*(1-Ir*Ir);

    if(disc < 0) return false;
    disc = -1.0*n*Ir - sqrt(disc);
    
    T->m[1][1] = n*D->m[1][1] + sgn*disc*N->m[1][1];
    T->m[2][1] = n*D->m[2][1] + sgn*disc*N->m[2][1];
    T->m[3][1] = n*D->m[3][1] + sgn*disc*N->m[3][1];
    T->m[4][1] = 0.0;

    return true;
}

/*
 * shade
 * This function recursively finds the point of intersection with a given
 * camera position and view ray, calculating the colour components at that point
 * Input: The light source, the objects array, the intersection in world coordinate
 * system, direction of gaze, the background colour, and the current rec. depth
 * Output: The colour sum at the point of intersection
 */
colour_t shade(light_t *light, object_t *object, dmatrix_t *e, dmatrix_t *d, colour_t background, int depth) {
    
    int h, k, nobj = 0;
    double t0[N_OBJECTS], Id, Is ;
    
    dmatrix_t *S, *V, *R, *I, *N, *Te, *Td, *Tdn, *Vr, *Wi, *WVr ;
    
    colour_t colour = colour_init(0.0,0.0,0.0);

    for (k = 0 ; k < N_SPHERES ; k++) {
        
        Te = dmat_mult(&object[k].Minv,e) ;
        Td = dmat_mult(&object[k].Minv,d) ;
 
        t0[k] = (*(object[k].intersection_function))(Te,Td) ;
                
        delete_dmatrix(Te) ;
        delete_dmatrix(Td) ;
        ++nobj;
    }

    if(infinite_plane_zinter(e, d, -2.0) > 0){
        for(;k < nobjects; ++k){
            Te = dmat_mult(&object[k].Minv,e) ;
            Td = dmat_mult(&object[k].Minv,d) ;
     
            t0[k] = (*(object[k].intersection_function))(Te,Td) ;
                    
            delete_dmatrix(Te) ;
            delete_dmatrix(Td) ;
            ++nobj;        
        }
    }
    
    h = find_min_hit_time(t0, nobj) ;
    
    if (h != -1) {

        Te = dmat_mult(&object[h].Minv,e) ;
        Td = dmat_mult(&object[h].Minv,d) ;
    
        I = intersection_coordinates(Te,Td,t0[h]) ;
        Wi = dmat_mult(&object[h].M, I);
        S = vector_to_light_source(I,Ts + h) ;
        N = normal_to_surface(&object[h],I) ;
        V = vector_to_center_of_projection(I,Te) ;
        double Ir = dot_product(V,N);       

        if((depth > 0)&&((object[h].reflectivity > 0)||(object[h].density > 0))){
            Vr = vector_of_reflection(V, N); 
            WVr = dmat_mult(&object[h].M, Vr);

            colour_t reflection = shade(light, object, Wi, WVr, background, depth - 1);

            //Check for reflected light
            if((object[h].reflectivity > 0.0)&&(Ir > 0.0)){                                                             
                colour = colour_add(colour, colour_scale(object[h].reflectivity, reflection) );            
            }

            if(object[h].density > 0){
                colour_t refraction = refractionColour(light,object,Wi,background,depth,V,N,h,reflection);
                colour = colour_add(colour, refraction );
            }

            delete_dmatrix(WVr) ;
            delete_dmatrix(Vr) ;
        }

        // Check for shadows
        if(!checkShadow(Wi,S,h)&&(Ir > 0.0)){                        
            R = vector_to_specular_reflection(I,S) ;        

            Id = dot_product(N,S) ;
            Is = dot_product(R,V) ;
        
            if (Id < 0.0){
                Id = 0.0 ;
            }
            else {
                Id /= (dmat_norm(S)*dmat_norm(N));
            }
            if (Is < 0.0) Is = 0.0 ; 
            else { 
                Is /= (dmat_norm(R)*dmat_norm(V));
                Is = powl(Is,object[h].f) ;
            }

            colour = colour_add(colour, diffuseColour(light, object + h, Id));
            colour = colour_add(colour, specularColour(light, object + h, Is));

            delete_dmatrix(R) ;
        }

        if(Ir > 0.0) colour = colour_add(colour, ambientColour(light, object + h));

        delete_dmatrix(Wi) ;
        delete_dmatrix(V) ;
        delete_dmatrix(N) ;
        delete_dmatrix(Te) ;
        delete_dmatrix(Td) ;
        delete_dmatrix(S) ;
        delete_dmatrix(I) ;    
    }
    else {
        colour = background;
    }
    
    if(depth == DEPTH) {
        colour.r *= MAX_INTENSITY;
        colour.g *= MAX_INTENSITY;
        colour.b *= MAX_INTENSITY;
        
        if(colour.r > MAX_INTENSITY) colour.r = MAX_INTENSITY;
        if(colour.g > MAX_INTENSITY) colour.g = MAX_INTENSITY;
        if(colour.b > MAX_INTENSITY) colour.b = MAX_INTENSITY;
    }
    
    return colour ;
}

/*
 * refractionColour
 * This function recursively calculates the refraction colour of the intersection point
 * Input: The light source, the objects array, the intersection in world coordinates, 
 * the background colour, the current rec. depth, the direction from intersection
 * point to eye, the normal to surface at intersection point, the index of the current 
 * object, and the previously calculated reflection
 * Output: The refraction colour of the intersection point
 */
colour_t refractionColour(light_t *light, object_t *object, dmatrix_t *Wi, colour_t background, int depth,
             dmatrix_t *V, dmatrix_t *N, int h, colour_t reflection){
    
    dmatrix_t *T = (dmatrix_t *)malloc(sizeof(dmatrix_t));
    
    dmat_alloc(T,4,1);

    colour_t k = colour_init(1.0, 1.0, 1.0);
    double c;
    double Ir = dot_product(V,N);
    double n = object[h].density;
    
    if(Ir > 0.0){
        refract(V,N,1,1.0/n,Ir,T);                
    }
    else {
        double et = exp(dmat_norm(V));
        colour_scale(et, object->absorb_colour);
        
        if(refract(V,N,-1,n,Ir,T)){
            c = dot_product(T,N);
        }
        else{
            free(T);
            return colour_mult(k, reflection) ;
        }
    }

    double R0 = 1.0/(n + 1.0);
    double R = n - 1.0;
    R0 = R*R*R0*R0;
    R = R0 + (1 - R0)*pow(1.0-c, 5);
    
    dmatrix_t *Wt = dmat_mult(&object[h].M, T);
    
    colour_t result = colour_scale((1-R), reflection) ;
    colour_t refraction = shade(light, object, Wi, Wt, background, depth - 1);
    refraction = colour_scale(R, refraction);
    result = colour_add(result, refraction);
    result = colour_mult(result, k);
    result = colour_scale(object->absorb_coeff, result);

    free(Wt);
    free(T);
    return result;
}

/*
 * build_object
 * This function builds the object_t with attributes passed
 * Input: The object type, the matrix for the object, ambient, diffuse, specular, and absorb colour and coefficients, the density, and reflectivity
 * Output: The populated object_t shape
 */
object_t *build_object(int object_type, dmatrix_t *M, 
        colour_t ambient_colour, colour_t diffuse_colour, colour_t specular_colour, colour_t absorb_colour,
        double ambient_coeff, double diffuse_coeff, double specular_coeff, double absorb_coeff,
        double f, double reflectivity, double density) {
    
    object_t *object ;
    
    object = malloc(sizeof(*object));
    
    object->type = object_type ;
    object->M = *M ;
    dmat_alloc(&object->Minv,4,4) ;
    object->Minv = *dmat_inverse(&object->M) ;
    
    object->specular_colour.r = specular_colour.r ;
    object->specular_colour.g = specular_colour.g ;
    object->specular_colour.b = specular_colour.b ;
    object->specular_coeff = specular_coeff ;
    object->f = f ;
    
    object->diffuse_colour.r = diffuse_colour.r ;
    object->diffuse_colour.g = diffuse_colour.g ;
    object->diffuse_colour.b = diffuse_colour.b ;
    object->diffuse_coeff = diffuse_coeff ;
    
    object->ambient_colour.r = ambient_colour.r ;
    object->ambient_colour.g = ambient_colour.g ;
    object->ambient_colour.b = ambient_colour.b ;
    object->ambient_coeff = ambient_coeff ;

    object->absorb_colour.r = absorb_colour.r ;
    object->absorb_colour.g = absorb_colour.g ;
    object->absorb_colour.b = absorb_colour.b ;
    object->absorb_coeff = absorb_coeff ;

    object->reflectivity = reflectivity ;
    object->density = density;
    
    switch (object_type) {
          
        case SPHERE         :   object->intersection_function = &sphere_intersection ;
                                break ;
            
        case PLANE          :   object->intersection_function = &plane_intersection ;
                                break ;
            
        case INFINITE_PLANE :   object->intersection_function = &infinite_plane_intersection ;
                                break ;
    }
    
    nobjects++ ;
    return(object) ;
}

/*
 * main method
 * Author: Eric Bachmeier
 * Created: December 5, 2015
 * Purpose: This is the main method for executing the recursive ray tracer
 * Input Parameters: None
 * Output: A window defined by the H height with objects traced on it with reflectivity and refraction
 */
int main() {
    
    Display *d ;
    Window w ;
    XEvent e ;
    
    int i, j, s ;
    
    camera_t Camera ;
    window_t Window ;
    light_t light ;
    dmatrix_t M, light_position ;
    colour_t pixel, background, light_intensity, light_colour, ambient_colour, diffuse_colour, specular_colour, absorb_colour;
    double height, width, aspect, ambient_coeff, diffuse_coeff, specular_coeff, f, reflectivity, absorb_coeff, density ;
    
    /* Set the background colour */
    
    background.r = 0.0 ;
    background.g = 0.0 ;
    background.b = 0.0 ;
    
    /* Set up light position, intensity, and colour */
    
    dmat_alloc(&light_position,4,1) ;
    
    light_position.m[1][1] = Lx ;
    light_position.m[2][1] = Ly ;
    light_position.m[3][1] = Lz ;
    light_position.m[4][1] = 1.0 ;
    
    light_intensity.r = LIGHT_INTENSITY ;
    light_intensity.g = LIGHT_INTENSITY ;
    light_intensity.b = LIGHT_INTENSITY ;
    
    light_colour.r = 1.0 ;
    light_colour.g = 1.0 ;
    light_colour.b = 1.0 ;
    
    light = *build_light(&light,&light_position,light_colour,light_intensity) ;
    
    /* Build display window and synthetic camera */
    
    Window = *build_window(&Window,H,ASPECT) ;
    Camera = *build_camera(&Camera,&Window) ;
    
    /* Create a first sphere */
    
    dmat_alloc(&M,4,4) ;
    M = *dmat_identity(&M) ;
    
    M.m[1][4] = -8.0 ; // // // -8.0
    M.m[2][4] = 0.0 ;  // // //  0.0
    M.m[3][3] = 2.0 ;
    M.m[2][2] = 2.0 ;
    M.m[1][1] = 2.0 ;
    
    specular_colour.r = 1.0 ;
    specular_colour.g = 1.0 ;
    specular_colour.b = 1.0 ;
    specular_coeff = 0.4 ;
    f = 10.0 ;
    
    diffuse_colour.r = 1.0 ;
    diffuse_colour.g = 0.0 ;
    diffuse_colour.b = 1.0 ;
    diffuse_coeff = 0.4 ;
    
    ambient_colour.r = 1.0 ;
    ambient_colour.g = 0.0 ;
    ambient_colour.b = 1.0 ;
    ambient_coeff = 0.2 ;
    
    reflectivity = REFL ;
    absorb_coeff = AC;
    density = TRAN ;
    absorb_colour.r = 1.0 ;
    absorb_colour.g = 0.0 ;
    absorb_colour.b = 1.0 ;
    object[nobjects] = *build_object(SPHERE,&M,ambient_colour,diffuse_colour,specular_colour,absorb_colour,ambient_coeff,diffuse_coeff,specular_coeff,absorb_coeff,f,reflectivity,density) ;
    
    /* Create a second sphere */
    
    dmat_alloc(&M,4,4) ;
    M = *dmat_identity(&M) ;
    
    M.m[1][4] = -4.0 ;   // // // -4.0
    M.m[2][4] = 0.0 ;    // // //  0.0
    M.m[2][2] = 2.0 ;
    
    specular_colour.r = 1.0 ;
    specular_colour.g = 1.0 ;
    specular_colour.b = 1.0 ;
    specular_coeff = 0.4 ;
    f = 10.0 ;
    
    diffuse_colour.r = 0.0 ;
    diffuse_colour.g = 0.0 ;
    diffuse_colour.b = 1.0 ;
    diffuse_coeff = 0.4 ;
    
    ambient_colour.r = 0.0 ;
    ambient_colour.g = 0.0 ;
    ambient_colour.b = 1.0 ;
    ambient_coeff = 0.2 ;
    
    reflectivity = REFL ;
    absorb_coeff = AC;
    density = TRAN ;
    absorb_colour.r = 0.0 ;
    absorb_colour.g = 0.0 ;
    absorb_colour.b = 1.0 ;
    object[nobjects] = *build_object(SPHERE,&M,ambient_colour,diffuse_colour,specular_colour,absorb_colour,ambient_coeff,diffuse_coeff,specular_coeff,absorb_coeff,f,reflectivity,density) ;
    
    /* Create a third sphere */
    
    dmat_alloc(&M,4,4) ;
    M = *dmat_identity(&M) ;
    
    M.m[1][4] = 0.0 ;
    M.m[2][4] = 0.0 ;
    M.m[1][1] = 3.0 ;
    
    specular_colour.r = 1.0 ;
    specular_colour.g = 1.0 ;
    specular_colour.b = 1.0 ;
    specular_coeff = 0.4 ;
    f = 10.0 ;
    
    diffuse_colour.r = 1.0 ;
    diffuse_colour.g = 0.078 ;
    diffuse_colour.b = 0.65 ;
    diffuse_coeff = 0.4 ;
    
    ambient_colour.r = 1.0 ;
    ambient_colour.g = 0.078 ;
    ambient_colour.b = 0.65 ;
    ambient_coeff = 0.2 ;
    
   	reflectivity = REFL ;
    absorb_coeff = AC;
    density = TRAN ;
    absorb_colour.r = 1.0 ;
    absorb_colour.g = 0.078 ;
    absorb_colour.b = 0.65 ;
    object[nobjects] = *build_object(SPHERE,&M,ambient_colour,diffuse_colour,specular_colour,absorb_colour,ambient_coeff,diffuse_coeff,specular_coeff,absorb_coeff,f,reflectivity,density) ;
    
    /* Create a fourth sphere */
    
    dmat_alloc(&M,4,4) ;
    M = *dmat_identity(&M) ;
    
    M.m[1][4] = 5.0 ;
    M.m[2][4] = 0.0 ;
    M.m[1][1] = 0.5 ;
    M.m[2][2] = 0.5 ;
	M.m[3][3] = 0.5 ;    
    
    specular_colour.r = 1.0 ;
    specular_colour.g = 1.0 ;
    specular_colour.b = 1.0 ;
    specular_coeff = 0.4 ;
    f = 10.0 ;
    
    diffuse_colour.r = 1.0 ;
    diffuse_colour.g = 0.85 ;
    diffuse_colour.b = 0.0 ;
    diffuse_coeff = 0.4 ;
    
    ambient_colour.r = 1.0 ;
    ambient_colour.g = 0.85 ;
    ambient_colour.b = 0.0 ;
    ambient_coeff = 0.2 ;
    
    reflectivity = REFL ;
    absorb_coeff = AC;
    density = TRAN ;
    absorb_colour.r = 1.0 ;
    absorb_colour.g = 0.85 ;
    absorb_colour.b = 0.0 ;
    object[nobjects] = *build_object(SPHERE,&M,ambient_colour,diffuse_colour,specular_colour,absorb_colour,ambient_coeff,diffuse_coeff,specular_coeff,absorb_coeff,f,reflectivity,density) ;
    
    /* Create a fifth sphere */
    
    dmat_alloc(&M,4,4) ;
    M = *dmat_identity(&M) ;
    
    M.m[1][4] = 8.0 ;
    M.m[2][4] = 0.0 ;
    
    specular_colour.r = 1.0 ;
    specular_colour.g = 1.0 ;
    specular_colour.b = 1.0 ;
    specular_coeff = 0.4 ;
    f = 10.0 ;
     
    diffuse_colour.r = 1.0 ;
    diffuse_colour.g = 0.0 ;
    diffuse_colour.b = 0.0 ;
    diffuse_coeff = 0.4 ;
    
    ambient_colour.r = 1.0 ;
    ambient_colour.g = 0.0 ;
    ambient_colour.b = 0.0 ;
    ambient_coeff = 0.2 ;
    
    reflectivity = REFL ;
    absorb_coeff = AC;
    density = TRAN ;
    absorb_colour.r = 1.0 ;
    absorb_colour.g = 0.0 ;
    absorb_colour.b = 0.0 ;
    object[nobjects] = *build_object(SPHERE,&M,ambient_colour,diffuse_colour,specular_colour,absorb_colour,ambient_coeff,diffuse_coeff,specular_coeff,absorb_coeff,f,reflectivity,density) ;
    
    /* Create a sixth sphere */
    
    dmat_alloc(&M,4,4) ;
    M = *dmat_identity(&M) ;
    
    M.m[1][4] = 0.0 ;
    M.m[2][4] = -4.0 ;
    M.m[3][4] = 2.0 ;
    M.m[1][1] = 4.0 ;
    M.m[2][2] = 2.0 ;
    M.m[3][3] = 2.0 ;
    
    specular_colour.r = 1.0 ;
    specular_colour.g = 1.0 ;
    specular_colour.b = 1.0 ;
    specular_coeff = 0.4 ;
    f = 10.0 ;
 
    diffuse_colour.r = 0.0 ;
    diffuse_colour.g = 1.0 ;
    diffuse_colour.b = 0.0 ;
    diffuse_coeff = 0.4 ;
    
    ambient_colour.r = 0.0 ;
    ambient_colour.g = 1.0 ;
    ambient_colour.b = 0.0 ;
    ambient_coeff = 0.2 ;
    
    reflectivity = REFL ;
    absorb_coeff = AC;
    density = TRAN ;
    absorb_colour.r = 0.0 ;
    absorb_colour.g = 1.0 ;
    absorb_colour.b = 0.0 ;
    object[nobjects] = *build_object(SPHERE,&M,ambient_colour,diffuse_colour,specular_colour,absorb_colour,ambient_coeff,diffuse_coeff,specular_coeff,absorb_coeff,f,reflectivity,density) ;
    
    /* Create tiled floor with planes */
    
    for (i = -6 ; i < 6 ; i++) {
        for (j = -6 ; j < 6 ; j++) {
            
            dmat_alloc(&M,4,4) ;
            M = *dmat_identity(&M) ;
            
            M.m[1][4] = (double)2*i ;
            M.m[2][4] = (double)2*j ;
            M.m[3][4] = -2.0 ;
             
            specular_colour.r = 1.0 ;
            specular_colour.g = 1.0 ;
            specular_colour.b = 1.0 ;
            specular_coeff = 0.4 ;
            f = 10.0 ;
            
            diffuse_colour.r = 1.0 ;
            diffuse_colour.g = 1.0 ;
            diffuse_colour.b = 1.0 ;
            diffuse_coeff = 0.4 ;
            
            ambient_colour.r = (double)(abs(i+j)%2) ;
            ambient_colour.g = (double)(abs(i+j)%2) ;
            ambient_colour.b = (double)(abs(i+j)%2) ;
            ambient_coeff = 0.2 ;
            
            absorb_colour.r = (double)(abs(i+j)%2) ;
            absorb_colour.g = (double)(abs(i+j)%2) ;
            absorb_colour.b = (double)(abs(i+j)%2) ;
            absorb_coeff = 0.2 ;
            
            reflectivity = REFL ;
    		density = 0.5 ;
    		object[nobjects] = *build_object(PLANE,&M,ambient_colour,diffuse_colour,specular_colour,absorb_colour,ambient_coeff,diffuse_coeff,specular_coeff,absorb_coeff,f,reflectivity,density) ;
        }
    }
    
    buildLightDirectionMatrices(&light);
    
    /* Set near plane dimensions */
    aspect = ASPECT ;
    height = Near*tan(M_PI/180.0 * THETA/2.0) ;
    width = height*aspect ;
    
    dmatrix_t *direction ;
    
    d = InitX(d,&w,&s,&Window) ;
    XNextEvent(d, &e) ;
    
    while (1) {
        XNextEvent(d,&e) ;
        if (e.type == Expose) {
            
            for (i = 0 ; i < Window.width ; i++) {
                for (j = 0  ; j < Window.height ; j++) {
                    direction = ray_direction(&Camera,&Window,height,width,(double)i,(double)j) ;
                    pixel = shade(&light,object,&Camera.E,direction,background,DEPTH) ;
                    SetCurrentcolourX(d,&(DefaultGC(d,s)),(int)pixel.r,(int)pixel.g,(int)pixel.b) ;
                    SetPixelX(d,w,s,i,Window.height - (j + 1)) ;
                    delete_dmatrix(direction) ;
                    
                }
            }
        }
        if (e.type == KeyPress)
            break ;
        if (e.type == ClientMessage)
            break ;
    }
    QuitX(d,w) ;
}