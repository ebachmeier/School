/*            PURPOSE : Supports dynamic arrays.

        PREREQUISITES : NONE

*/

#include <stdio.h>
#include <stdlib.h>

void nrerror(char error_text[]) 

{ void exit() ;

  fprintf(stderr,"Run-time error...\n") ;
  fprintf(stderr,"%s\n",error_text) ;
  exit(1) ;
}

double **dmatrix(int nrl, int nrh, int ncl, int nch)

{ int i ;
  double **m ;

  m = (double **)malloc((unsigned) (nrh - nrl +1)*sizeof(double)) ;
  if (!m) {
    nrerror("DMATRIX: allocation failure") ;
  }
  m -= nrl ;

  for (i = nrl ; i <= nrh ; i++) {
    m[i] = (double *)malloc((unsigned) (nch - ncl + 1)*sizeof(double)) ;
    if (!m[i]) {
      nrerror("DMATRIX: allocation failure") ;
    }
    m[i] -= ncl ;
  }
  return (m) ;
}

void free_dmatrix(double **m, int nrl, int nrh, int ncl, int nch)

{ int i ; 

  for (i = nrh ; i >= nrl ; i--) {
    free((char *) (m[i] + ncl)) ;
  }
  free((char *) (m + nrl)) ;
}