/** \brief Main file from which different functions located in other files are
 *        called to perform different tasks of the algorithm.
 *
 *
 *  Currently only the implementation of Support Degree Matrix and calculation
 *  of eigen values and vectors has been done by calling the sdm_calculator()
 *  function in SensorFusionAlgorithm file.
 *
 */
#include <stdio.h>
#include <math.h>
#include "SensorFusionAlgorithm.h"

/** \brief The main function which distributes various tasks to other functions
 *
 *  Only the sdm_calculator function has been called as that's the only
 *  function that is completed.
 */
int main(void){
	int size;
	double sensorinputs[] = {53.2, 55.3, 54.2, 52.2, 45.2, 55.2, 55, 54.5};
	size = sizeof(sensorinputs)/sizeof(sensorinputs[0]);
	printf("Calling sdm_calculator \n");
	compute_integrated_support_degree_score(sensorinputs,compute_alpha(eigen_value_calculation(sdm_calculator(sensorinputs,size),size),size), compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(sensorinputs,size),size),size),size), sdm_calculator(sensorinputs,size), 0.85, size);
   // compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(sensorinputs, size), size),size),size);
    //eigen_vector_calculation(sdm_calculator(sensorinputs,size),size,7);
}
