/** \brief Contains functions performing the actual algorithm
 *
 *  Currently only the implementation of Support Degree Matrix and calculation
 *  of eigen values and vectors has been done here. An external library called
 *  gsl library is used for this purpose.
 */
#include "SensorFusionAlgorithm.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

/** \brief Calculate Support Degree Matrix and its Eigen values & vectors
 *
 *  Currently the sensor input data has been hard-coded in sensorinputs[]
 *  array. This will be later changed to dynamically handle inputs from
 *  a function that reads csv file and outputs an array containing sensor
 *  inputs.
 */
void sdm_calculator(){

    double sensorinputs[] = {1, 12, 6, 4, 7, 6, 8};
    int i,j,x,k=0;
	int size = sizeof(sensorinputs)/sizeof(sensorinputs[0]);
	printf("size %d\n", size);
	double d[size][size];
	double *e = malloc(sizeof(double)*(size*size));

	for(i=0; i<size;i++){

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

			if(k%size==0){
			    printf("\n");
			}
	    }
	}
	gsl_matrix_view m = gsl_matrix_view_array (e, size, size);
	gsl_vector *eval = gsl_vector_alloc (size);
	gsl_matrix *evec = gsl_matrix_alloc (size, size);
	gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (size);
	gsl_eigen_symmv (&m.matrix, eval, evec, w);
	gsl_eigen_symmv_free (w);
	gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_ASC);
    int i;

    for(i = 0; i < size; i++){
	    double eval_i = gsl_vector_get (eval, i);
		gsl_vector_view evec_i = gsl_matrix_column (evec, i);
		printf("eigenvalue = %g\n", eval_i);
		printf("eigenvector = \n");
		gsl_vector_fprintf (stdout, &evec_i.vector, "%g");
	}
	gsl_vector_free (eval);
	gsl_matrix_free (evec);
    //return e;
}

/* \brief Calculates the contribution rates i.e. alphas of every sensor and
 *        accumulated contribution rates i.e., phi m
 *
 * Takes in the list of eigen values and two empty lists. Then fills the
 * one empty list with the contribution rate of every sensor and the other
 * empty list with accumulated contribution rates.
 * @param[in] evals List of Eigen Values. The Eigen Value at index n
 *                   corresponds to the nth sensor found in index n
 *                   of sensorinputs array.
 * @param[in] size  Number of eigen values which is same as the
 *                  number of sensors and number of contribution
 *                  rate values.
 * @param[in,out] list_of_alphas The c_rate_list which is empty and after
 *                               function execution, the list is filled with
 *                               contribution rates of every sensor.
 * @param[in,out] list_of_phi The acc_c_rate_list which is empty and after
 *                            function execution, the list is filled with
 *                            accumulated contribution rates i.e., phi
 */
void compute_alpha_and_phi(double evals[],int size,double list_of_alphas[],double list_of_phi[]){
	double sum_of_evals = 0.0;
	for(int i=0; i<size; i++){
		sum_of_evals += evals[i];
	}
	for(int i=0;i <size;i++) {
		list_of_alphas[i] = evals[i]/sum_of_evals;
	}
	list_of_phi[0] = list_of_alphas[0];
	for(int i=1; i<size;i++){
		list_of_phi[i] = list_of_phi[i-1] + list_of_alphas[i];
	}
}



