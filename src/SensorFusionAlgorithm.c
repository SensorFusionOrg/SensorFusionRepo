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
	//printf("size %d\n", size);
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
			//printf("%lf\t",dmatrix[k]);
			k++;

			if(k%size==0){
			 //   printf("\n");
			}
	    }
	}
	return dmatrix;
}
double* eigen_value_calculation(double* dmatrix, int size){
	int i;
	gsl_matrix_view m = gsl_matrix_view_array (dmatrix, size, size);
	gsl_vector *eval = gsl_vector_alloc (size);
	gsl_matrix *evec = gsl_matrix_alloc (size, size);
	gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (size);
	gsl_eigen_symmv (&m.matrix, eval, evec, w);
	gsl_eigen_symmv_free (w);
	gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_DESC);
	double *eval_i = malloc(sizeof(double)*(size));
    for(i = 0; i < size; i++){
	    eval_i[i] = gsl_vector_get (eval, i);
		//printf("eigenvalue = %g\n", eval_i[i]);
	}
    return eval_i;
}

double* eigen_vector_calculation(double* dmatrix, int size, int column){
	int i;
		gsl_matrix_view m = gsl_matrix_view_array (dmatrix, size, size);
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
			//printf("Eigen Vector: %g\n", evec_i[i]);
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
		//printf("list of alpha = %lf\n\n",list_of_alphas[i]*100);
	}
	return list_of_alphas;
}


double* compute_phi(double list_of_alphas[], int size){
	double *list_of_phi = malloc(sizeof(double)*(size));
	list_of_phi[0] = list_of_alphas[0];
//	printf("list of phi = %lf\n",list_of_phi[0]*100);
		for(int i=1; i<size;i++){
			list_of_phi[i] = list_of_phi[i-1] + list_of_alphas[i];
			//printf("list of phi = %lf\n",list_of_phi[i]*100);
		}
		return list_of_phi;
}

double* compute_integrated_support_degree_score(double sensorinputs[], double list_of_alphas[], double list_of_phi[], double dmatrix[],double criterion, int size)
{
	double calculation,temp=0,temp1=0,temp2=0;
	gsl_matrix *y_temp =  gsl_matrix_alloc(size, size);
	gsl_matrix *y =  gsl_matrix_alloc(size, size);
	double *list_of_m_phi = malloc(sizeof(double)*(size));
	double *evec_i = malloc(sizeof(double)*(size));
	int i,j,k,l=0,rows,col,o,p,q,rows1=0,col1=0,rows2,col2;
	for(i=0;i<size;i++)
	{
		list_of_m_phi[i]=list_of_phi[i];
		if(list_of_phi[i]>criterion)
		{
			break;
		}
	}
	gsl_matrix *dmatrix2d =  gsl_matrix_alloc(size, size);
	for (j = 0; j < size; j++){
	    for (k = 0; k < size; k++){
		gsl_matrix_set(dmatrix2d, j, k, dmatrix[l++]);
	//	printf ("m(%d,%d) = %g\n", j, k, gsl_matrix_get (dmatrix2d, j, k));

	}
	}

	for(o=0;o<size;o++){
	evec_i = eigen_vector_calculation(sdm_calculator(sensorinputs,size), size, o);
	for(col=0;col<size;col++)
	{
	for(rows=0;rows<size;rows++)
	{
		calculation = evec_i[col]* gsl_matrix_get(dmatrix2d,rows,col);
		gsl_matrix_set(y_temp, rows, col, calculation);
//	printf ("m(%d,%d) = %g\n", rows, col, gsl_matrix_get (y_temp, rows, col));
	}
	}
	for(rows=0;rows<size;rows++){
		temp = 0;
	for(col=0;col<size;col++)
	{
		temp += gsl_matrix_get (y_temp, rows, col);
		//printf("TEMP:%lf \n",temp);
		}

	if(rows1==8)
	{
			col1++;
			rows1=0;
	}

	gsl_matrix_set(y, rows1++, col1, temp);
	//printf("TEMP cols:%lf \n",temp);
	}
	}
	for(col=0;col<size;col++)
		{
		for(rows=0;rows<size;rows++)
		{
		//	printf ("m(%d,%d) = %g\n", rows, col, gsl_matrix_get (y, rows, col));
		}
		}
	gsl_matrix *Z_temp =  gsl_matrix_alloc(size, size);
	double Z[size];
	for(p=0;p<size;p++)
	{
		for(q=0;q<size;q++)
		{
			temp1 =list_of_alphas[p]* gsl_matrix_get(y,q,p);
			gsl_matrix_set(Z_temp, q, p, temp1);
			//printf ("m(%d,%d) = %g\n", p, q, gsl_matrix_get (Z_temp, q, p));
			//printf("alpha :%lf \n",list_of_alphas[q]);
		}
	}
	for(rows2=0;rows2<size;rows2++){
		temp2 = 0;
	for(col2=0;col2<=i;col2++)
	{
		temp2 += gsl_matrix_get (Z_temp, rows2, col2);
		//printf("TEMP:%lf \n",temp2);
		}

	if(rows2==8)
	{
			col2++;
			rows2=0;
	}
	Z[rows2] = temp2;
	}
			for(rows2=0;rows2<size;rows2++)
			{
				printf ("m(%d) = %lf\n", rows2, Z[rows2] );
			}

			return Z;
}


