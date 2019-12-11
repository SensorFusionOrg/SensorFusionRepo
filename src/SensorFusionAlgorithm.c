
#include "SensorFusionAlgorithm.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

void SDMCalculator()
{
	double sensorinputs[] = {1, 12, 6, 4, 7, 6, 8};
	 int i,j,x,k=0;
			    int size = sizeof(sensorinputs)/sizeof(sensorinputs[0]);
			    printf("size %d\n", size);
			    double d[size][size];
			    double *e = malloc(sizeof(double)*(size*size));
			    for(i=0; i<size;i++)
			    {
			        for(j=0;j<size;j++){
			            double temp = sensorinputs[i]-sensorinputs[j];
			            if(temp<0){
			                temp = -temp;
			            }
			            temp = exp(-(temp));
			            d[i][j] =temp;
			            e[k]= temp;
			            printf("%lf\t",e[k]);
			            k++;
			            if(k%size==0)
			            	printf("\n");
			        }
			    }
			    gsl_matrix_view m = gsl_matrix_view_array (e, size, size);
			    gsl_vector *eval = gsl_vector_alloc (size);
			    gsl_matrix *evec = gsl_matrix_alloc (size, size);
			    gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (size);
			    gsl_eigen_symmv (&m.matrix, eval, evec, w);
			    gsl_eigen_symmv_free (w);
			    gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_ASC);
			    {
			    int i;
			    for (i = 0; i < size; i++)
			    {
			    double eval_i = gsl_vector_get (eval, i);
			    gsl_vector_view evec_i = gsl_matrix_column (evec, i);
			    printf ("eigenvalue = %g\n", eval_i);
			    printf ("eigenvector = \n");
			    gsl_vector_fprintf (stdout, &evec_i.vector, "%g");
			    }
			    }
			    gsl_vector_free (eval);
			    gsl_matrix_free (evec);
   // return e;
}



