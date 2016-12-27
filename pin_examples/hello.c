#include <stdio.h>
#include <stdlib.h>

void array1to2(void * a1, int n2, int n1) {
/*  double (*r)[n2][n1] = (double (*)[n2][n1])or; */
    double (*a2)[n2] = (double(*)[n2])a1;
    printf("%X, %X\n", a1, a2);
    int i, j;
    for (i=0; i<n1; i++)
       for (j=0; j<n2; j++)
           printf("%f\t", a2[i][j]);
}

int main ()
{
  int n2 = 4;
  int n1 = 4;
  double *a1 = malloc(sizeof(double)*n1*n2);
  int i; 
  for (i=0; i<n1*n2; i++)
     a1[i] = (double)i;
  array1to2(a1, n2, n1); 
  printf ("Hello World!\n");
}

