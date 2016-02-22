/*            PURPOSE : Matrix and vector allocation and linear algebra routines.
 
 PREREQUISITES : nr.h
 
 */

#include "nr.h"
#include <math.h>

typedef struct {
    double **m ;
    int l, c ;
} dmatrix_t ;

void dmat_alloc(dmatrix_t *A, int l, int c)

{ (*A).m = dmatrix(1,l,1,c) ;
    (*A).l = l ;
    (*A).c = c ;
}

void delete_dmatrix(dmatrix_t *A)

{ free_dmatrix(A->m,1,A->l,1,A->c) ;
    free(A) ;
}

dmatrix_t *dmat_init(dmatrix_t *A, double a)

{ int i, j ;
    
    for (i = 1 ; i <= (*A).l ; i++) {
        for (j = 1 ; j <= (*A).c ; j++) {
            (*A).m[i][j] = a ;
        }
    }
    return(A) ;
}

dmatrix_t *dmat_identity(dmatrix_t *A)

{ int i, j ;
    
    for (i = 1 ; i <= (*A).l ; i++) {
        for (j = 1 ; j <= (*A).c ; j++) {
            if (i == j) {
                (*A).m[i][j] = 1.0 ;
            }
            else {
                (*A).m[i][j] = 0.0 ;
            }
        }
    }
    return(A) ;
}

dmatrix_t *dmat_mult(dmatrix_t *A, dmatrix_t *B)

{ dmatrix_t *C ;
    double s ;
    int i, j, k ;
    
    if ((*A).c != (*B).l) {
        nrerror("MATRIX.H: incompatible matrix sizes") ;
    }
    C = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(C,(*A).l,(*B).c) ;
    
    for (i = 1 ; i <= (*C).l ; i++) {
        for (j = 1 ; j <= (*C).c ; j++) {
            for (s = 0.0, k = 1 ; k <= (*A).c ; k++) {
                s += (*A).m[i][k]*(*B).m[k][j] ;
            }
            (*C).m[i][j] = s ;
        }
    }
    return(C) ;
}

dmatrix_t *dmat_add(dmatrix_t *A, dmatrix_t *B)

{ dmatrix_t *C ;
    int i, j ;
    
    if ((*A).l != (*B).l || (*A).c != (*B).c) {
        nrerror("ADD, dmat_add: incompatible matrix sizes") ;
    }
    C = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(C,(*A).l,(*A).c) ;
    
    for (i = 1 ; i <= (*C).l ; i++) {
        for (j = 1 ; j <= (*C).c ; j++) {
            (*C).m[i][j] = (*A).m[i][j] + (*B).m[i][j] ;
        }
    }
    return(C) ;
}

dmatrix_t *dmat_sub(dmatrix_t *A, dmatrix_t *B)

{ dmatrix_t *C ;
    int i, j ;
    
    if ((*A).l != (*B).l || (*A).c != (*B).c) {
        nrerror("SUB: incompatible matrix sizes") ;
    }
    C = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(C,(*A).l,(*A).c) ;
    
    for (i = 1 ; i <= (*C).l ; i++) {
        for (j = 1 ; j <= (*C).c ; j++) {
            (*C).m[i][j] = (*A).m[i][j] - (*B).m[i][j] ;
        }
    }
    return(C) ;
}

double dmat_norm(dmatrix_t *A)

{ double s ;
    int i ;
    
    if ((*A).l != 1 && (*A).c != 1) {
        nrerror("NORM: incompatible matrix sizes") ;
    }
    else {
        if ((*A).l == 1) {
            for (s = 0.0, i = 1 ; i <= (*A).c ; i++) {
                s += pow((*A).m[1][i],2.0) ;
            }
        }
        else {
            for (s = 0.0, i = 1 ; i <= (*A).l ; i++) {
                s += pow((*A).m[i][1],2.0) ;
            }
        }
    }
    return(sqrt(s)) ;
}

dmatrix_t *dmat_normalize(dmatrix_t *A)

{ dmatrix_t *B ;
    double n ;
    int i, j ;
    
    B = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(B,(*A).l,(*A).c) ;
    
    n = dmat_norm(A) ;
    for (i = 1 ; i <= (*A).l ; i++) {
        for (j = 1 ; j <= (*A).c ; j++) {
            (*B).m[i][j] = (*A).m[i][j]/n ;
        }
    }
    return(B) ;
}

dmatrix_t *dmat_transpose(dmatrix_t *A)

{ dmatrix_t *B ;
    int i, j ;
    
    B = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(B,(*A).c,(*A).l) ;
    
    for (i = 1 ; i <= (*A).l ; i++) {
        for (j = 1 ; j <= (*A).c ; j++) {
            (*B).m[j][i] = (*A).m[i][j] ;
        }
    }
    return(B) ;
}

dmatrix_t *dcross_product(dmatrix_t *A, dmatrix_t *B)

{ dmatrix_t *dmat_transpose(), *dmat_mult(), C, *D, E ;
    
    D = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(D,1,3) ;
    dmat_alloc(&C,1,3) ;
    dmat_alloc(&E,3,3) ;
    
    if (((*A).l != 1 && (*A).c != 1) || ((*B).l != 1 && (*B).c != 1)) {
        nrerror("TRANSPOSE: Incompatible matrix sizes") ;
    }
    
    if ((*A).l != 1) {
        C = *dmat_transpose(A) ;
    }
    if ((*A).l != 3) {
        nrerror("TRANSPOSE: Incompatible matrix sizes") ;
    }
    
    if ((*B).l != 1) {
        D = dmat_transpose(B) ;
    }
    if ((*B).l != 3) {
        nrerror("TRANSPOSE: Incompatible matrix sizes") ;
    }
    E = *dmat_init(&E,0.0) ;
    E.m[1][2] = -(*D).m[1][3] ;
    E.m[1][3] = (*D).m[1][2] ;
    E.m[2][1] = (*D).m[1][3] ;
    E.m[2][3] = -(*D).m[1][1] ;
    E.m[3][1] = -(*D).m[1][2] ;
    E.m[3][2] = (*D).m[1][1] ;
    D = dmat_transpose(dmat_mult(&C,&E)) ;
    free_dmatrix(C.m,1,C.l,1,C.c) ;
    free_dmatrix(E.m,1,E.l,1,E.c) ;
    
    return(D) ;
}

double determinant(dmatrix_t *A)
{
    int i, j, j1, j2 ;
    double det = 0 ;
    dmatrix_t M ;
    
    if ((*A).l < 1 || (*A).c < 1) {
        nrerror("DET: Erroneous matrix size") ;
    } else if ((*A).l != (*A).c) {
        nrerror("DET: Not a square matrix") ;
    } else if ((*A).l == 1) {
        det = (*A).m[1][1] ;
    } else if ((*A).l == 2) {
        det = (*A).m[1][1]*(*A).m[2][2] - (*A).m[2][1]*(*A).m[1][2] ;
    } else {
        det = 0 ;
        for (j1 = 1 ; j1 <= (*A).l ; j1++) {
            dmat_alloc(&M, (*A).l - 1,(*A).l - 1) ;
            for (i = 2 ; i <= (*A).l ; i++) {
                j2 = 1 ;
                for (j = 1 ;j <= (*A).l ; j++) {
                    if (j == j1)
                        continue ;
                    M.m[i-1][j2] = (*A).m[i][j] ;
                    j2++ ;
                }
            }
            det += pow(-1.0, j1 + 1.0) * (*A).m[1][j1] * determinant(&M) ;
            free_dmatrix(M.m, 1, M.l, 1, M.c) ;
        }
    }
    return(det);
}

double dot_product(dmatrix_t *a, dmatrix_t *b) {
    
    return a->m[1][1]*b->m[1][1]+a->m[2][1]*b->m[2][1]+
    a->m[3][1]*b->m[3][1];
}

dmatrix_t *cofactor(dmatrix_t *A)

{ int i, j, ii, jj, i1, j1 ;
    double det ;
    dmatrix_t *B ;
    dmatrix_t C ;
    
    B = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(B, (*A).l, (*A).c) ;
    dmat_alloc(&C, (*A).l - 1, (*A).c - 1) ;
    for (j = 1 ; j <= (*A).l ; j++) {
        for (i = 1 ; i <= (*A).l ; i++) {
            i1 = 1 ;
            for (ii = 1 ; ii <= (*A).l ; ii++) {
                if (ii == i)
                    continue ;
                j1 = 1 ;
                for (jj = 1 ; jj <= (*A).l ; jj++) {
                    if (jj == j)
                        continue ;
                    C.m[i1][j1] = (*A).m[ii][jj];
                    j1++ ;
                }
                i1++ ;
            }
            det = determinant(&C);
            (*B).m[i][j] = pow(-1.0, i + j + 2.0)*det;
        }
    }
    free_dmatrix(C.m, 1, C.l, 1, C.c) ;
    return(B) ;
}

dmatrix_t *dmat_inverse(dmatrix_t *A)

{ int i, j ;
    double det ;
    dmatrix_t *B ;
    
    B = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(B, (*A).l, (*A).c) ;
    det = determinant(A) ;
    B = dmat_transpose(cofactor(A)) ;
    for (i = 1 ; i <= (*B).l ; i++) {
        for (j = 1 ; j <= (*B).c ; j++) {
            (*B).m[i][j] /= det ;
        }
    }
    return(B) ;
}

void write_dmatrix(dmatrix_t *M)

{ int i, j ;
    
    for (i = 1 ; i <= (*M).l ; i++) {
        for (j = 1 ; j <= (*M).c ; j++) {
            printf("%7.4f ",(*M).m[i][j]) ;
        }
        printf("\n") ;
    }
}

dmatrix_t *vector_to_light_source(dmatrix_t *intersection, dmatrix_t *light_position) {
    
    dmatrix_t *s, *sn ;
    
    s = dmat_sub(light_position,intersection) ;
    sn = dmat_normalize(s) ;
    delete_dmatrix(s) ;
    
    return sn ;
}

dmatrix_t *vector_to_center_of_projection(dmatrix_t *intersection, dmatrix_t *e) {
    
    dmatrix_t *v, *vn ;
    
    v = dmat_sub(e,intersection) ;
    vn = dmat_normalize(v) ;
    delete_dmatrix(v) ;
    
    return vn ;
}

dmatrix_t *vector_to_specular_reflection(dmatrix_t *N, dmatrix_t *S) {
    
    dmatrix_t *r, *rn ;
    
    r = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(r,4,1) ;
    
    double sn = 2.0*dot_product(N,S) ;
    
    r->m[1][1] = -1.0*S->m[1][1] + sn*N->m[1][1] ;
    r->m[2][1] = -1.0*S->m[2][1] + sn*N->m[2][1] ;
    r->m[3][1] = -1.0*S->m[3][1] + sn*N->m[3][1] ;
    r->m[4][1] = 0.0 ;
    
    rn = dmat_normalize(r) ;
    delete_dmatrix(r) ;
    
    return rn ;
}

dmatrix_t *intersection_coordinates(dmatrix_t *e, dmatrix_t *direction, double t) {
    
    dmatrix_t *intersection ;
    
    intersection = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(intersection,4,1) ;
    
    intersection->m[1][1] = e->m[1][1] + direction->m[1][1]*t ;
    intersection->m[2][1] = e->m[2][1] + direction->m[2][1]*t ;
    intersection->m[3][1] = e->m[3][1] + direction->m[3][1]*t ;
    intersection->m[4][1] = 1.0 ;
    
    return intersection ;
}