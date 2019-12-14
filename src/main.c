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
#include <stdlib.h>
#include "../include/SensorFusionAlgorithm.h"
#include "../include/input.h"
#include <errno.h>

#define NUMBEROFTIMESTAMPS 3
#define MAX 512

/** \brief The main function which distributes various tasks to other functions
 *
 *  Only the sdm_calculator function has been called as that's the only
 *  function that is completed.
 */
int main(void){
	double fusion_result[NUMBEROFTIMESTAMPS];
	int timestampsetcounter = 0;
	double sensorvaluesets[NUMBEROFTIMESTAMPS][MAX];
	double *sensorinputs[NUMBEROFTIMESTAMPS];

	sensorValueRead("../input/input.csv",sensorvaluesets);
	// First element is the number of sensors read from the .csv file
	for (timestampsetcounter = 0; timestampsetcounter < NUMBEROFTIMESTAMPS; timestampsetcounter++) {
		printf("Calculations for timestamp %lf\n", sensorvaluesets[timestampsetcounter][1]);
		printf("Calling sdm_calculator \n");
		sensorinputs[timestampsetcounter] = (double*)malloc(sensorvaluesets[timestampsetcounter][0]*sizeof(double)); 
		for(int indexcounter=2; indexcounter < sensorvaluesets[timestampsetcounter][0]+2; indexcounter++){
			sensorinputs[timestampsetcounter][indexcounter-2] = sensorvaluesets[timestampsetcounter][indexcounter]; 
		}
		fusion_result[timestampsetcounter] = 	faulty_sensor_and_sensor_fusion(compute_integrated_support_degree_score(sensorinputs[timestampsetcounter],compute_alpha(eigen_value_calculation(sdm_calculator(sensorinputs[timestampsetcounter],(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]), compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(sensorinputs[timestampsetcounter],(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]), sdm_calculator(sensorinputs[timestampsetcounter],(int)sensorvaluesets[timestampsetcounter][0]), 0.85, (int)sensorvaluesets[timestampsetcounter][0]),sensorinputs[timestampsetcounter],(int)sensorvaluesets[timestampsetcounter][0]);
		printf("Fusion result : %lf",fusion_result[timestampsetcounter]);
		printf("\n");
	}
	//faulty_sensor(Z,size);
	// compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(sensorinputs, size), size),size),size);
    //eigen_vector_calculation(sdm_calculator(sensorinputs,size),size,7);
}
