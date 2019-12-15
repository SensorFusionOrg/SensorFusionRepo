/** \brief Main file from which different functions located in other files are
 *        called to perform different tasks of the algorithm.
 *
 *   TODO: Comments for this file and each method of this file has to be updated
 */
#include <stdio.h>
#include <math.h>
#include "SensorFusionAlgorithm.h"

/** \brief The main function which distributes various tasks to other functions
 *
 *
 */
int main(void){
	int size;
	double fusion_result;
	double sensorinputs[] = {150,53.3,52.8,53.1,52.9,52.6,52.7,53.5};
	size = sizeof(sensorinputs)/sizeof(sensorinputs[0]);
	printf("Calling sdm_calculator \n");
	fusion_result = faulty_sensor_and_sensor_fusion(
		compute_integrated_support_degree_score(sensorinputs,compute_alpha(
		eigen_value_calculation(sdm_calculator(sensorinputs,size),size),size),
		compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(
		sensorinputs,size),size),size),size),sdm_calculator(sensorinputs,size),
		0.85,size),sensorinputs,size);
	printf("Fusion result : %lf",fusion_result);
	//faulty_sensor(Z,size);
	// compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(sensorinputs, size), size),size),size);
    //eigen_vector_calculation(sdm_calculator(sensorinputs,size),size,7);
}
