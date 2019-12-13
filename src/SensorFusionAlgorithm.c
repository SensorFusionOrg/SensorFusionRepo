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
double* sdm_calculator(double sensorinputs[], int size){

    int i,j,k=0;
	printf("size %d\n", size);
	double d[size][size];
	double *dmatrix = malloc(sizeof(double)*(size*size));

	for(i=0; i<size;i++){

	    for(j=0;j<size;j++){
		    double temp = sensorinputs[i]-sensorinputs[j];

			if(temp<0){
			    temp = -temp;
			}

			temp = exp(-(temp));
			d[i][j] =temp;
			dmatrix[k]= temp;
			printf("%lf\t",dmatrix[k]);
			k++;

			if(k%size==0){
			    printf("\n");
			}
	    }
	}
	return dmatrix;
}
double* eigen_value_calculation(double* e, int size){
	int i;
	gsl_matrix_view m = gsl_matrix_view_array (e, size, size);
	gsl_vector *eval = gsl_vector_alloc (size);
	gsl_matrix *evec = gsl_matrix_alloc (size, size);
	gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (size);
	gsl_eigen_symmv (&m.matrix, eval, evec, w);
	gsl_eigen_symmv_free (w);
	gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_DESC);
	double *eval_i = malloc(sizeof(double)*(size));
    for(i = 0; i < size; i++){
	    eval_i[i] = gsl_vector_get (eval, i);
		printf("eigenvalue = %g\n", eval_i[i]);
	}
    return eval_i;
}

double* eigen_vector_calculation(double* e, int size, int column){
	int i;
		gsl_matrix_view m = gsl_matrix_view_array (e, size, size);
		gsl_vector *eval = gsl_vector_alloc (size);
		gsl_matrix *evec = gsl_matrix_alloc (size, size);
		gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (size);
		gsl_eigen_symmv (&m.matrix, eval, evec, w);
		gsl_eigen_symmv_free (w);
		gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_DESC);
		double *evec_i = malloc(sizeof(double)*(size));
		for(i=0;i<size;i++)
		{
			evec_i[i]= gsl_matrix_get(evec, i, column);
			//printf("%g\n", evec_i[i]);
		}
		return evec_i;
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
double* compute_alpha(double eval_i[],int size){
	double *list_of_alphas = malloc(sizeof(double)*(size));
	double sum_of_evals = 0.0;
	for(int i=0; i<size; i++){
		sum_of_evals += eval_i[i];
	}
	for(int i=0;i <size;i++) {
		list_of_alphas[i] = eval_i[i]/sum_of_evals;
		printf("list of alpha = %lf\n",list_of_alphas[i]*100);
	}
	return list_of_alphas;
}


double* compute_phi(double list_of_alphas[], int size){
	double *list_of_phi = malloc(sizeof(double)*(size));
	list_of_phi[0] = list_of_alphas[0];
		for(int i=1; i<size;i++){
			list_of_phi[i] = list_of_phi[i-1] + list_of_alphas[i];
			printf("list of phi = %lf\n",list_of_phi[i]*100);
		}
		return list_of_phi;
}


