/** \brief Main file from which different functions located in other files are
 *        called to perform different tasks of the algorithm.
 *
 *   TODO: Comments for this file and each method of this file has to be updated
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../include/SensorFusionAlgorithm.h"
#include "../include/input.h"


/** \brief The main function which distributes various tasks to other functions
 *
 *
 */
int main(void){
	int timestampsetcounter = 0;
	int numtimestamp = 0;
	double sensorvaluesets[MAX][MAX];
	memset(sensorvaluesets, '\0', MAX*MAX);
	sensorValueRead("./input/input.csv",sensorvaluesets);
	
	FILE *fpoutput = fopen("./output/results.txt","w"); // Creating a file for output which will hold the results
	if (fpoutput == NULL) {
    		printf("File Open for Write Failed\n");
    		return 1;
		}
	fclose(fpoutput);					
	while((int)sensorvaluesets[timestampsetcounter][0]!= -1){ // Scans through the entire set of input sets and stops at the end of data set
		numtimestamp++;
		timestampsetcounter++;
	}
	double fusion_result[numtimestamp];
	double *sensorinputs[numtimestamp];
	// First element is the number of sensors read from the .csv file
	for (timestampsetcounter = 0; timestampsetcounter < numtimestamp; timestampsetcounter++) {
		printf("Calculations for timestamp %lf\n", sensorvaluesets[timestampsetcounter][1]);
		printf("Calling sdm_calculator \n");
		fpoutput = fopen("./output/results.txt","a+"); //appending the results in the output file
		if (fpoutput == NULL) {
    			printf("File Open for Write Failed\n");
    		return 1;
		}
		fprintf(fpoutput, "%s: %lf\n", "Calculations for timestamp", sensorvaluesets[timestampsetcounter][1]);
		
		fclose(fpoutput);
		sensorinputs[timestampsetcounter] = (double*)malloc(sensorvaluesets[timestampsetcounter][0]*sizeof(double)); 
		for(int indexcounter=2; indexcounter < sensorvaluesets[timestampsetcounter][0]+2; indexcounter++){
			sensorinputs[timestampsetcounter][indexcounter-2] = sensorvaluesets[timestampsetcounter][indexcounter]; 
		}
		fusion_result[timestampsetcounter] = 	faulty_sensor_and_sensor_fusion(compute_integrated_support_degree_score(sensorinputs[timestampsetcounter],compute_alpha(eigen_value_calculation(sdm_calculator(sensorinputs[timestampsetcounter],(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]), compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(sensorinputs[timestampsetcounter],(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]), sdm_calculator(sensorinputs[timestampsetcounter],(int)sensorvaluesets[timestampsetcounter][0]), 0.85, (int)sensorvaluesets[timestampsetcounter][0]),sensorinputs[timestampsetcounter],(int)sensorvaluesets[timestampsetcounter][0]);
		printf("Fusion result : %lf",fusion_result[timestampsetcounter]);
		printf("\n");
		fpoutput = fopen("./output/results.txt","a+");
		if (fpoutput == NULL) {
    			printf("File Open for Write Failed\n");
    		return 1;
		}
		fprintf(fpoutput, "%s: %lf","Fusion result",fusion_result[timestampsetcounter]);
		fprintf(fpoutput, "%s","\n");
		fclose(fpoutput);
	}
	//faulty_sensor(Z,size);
	// compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(sensorinputs, size), size),size),size);
    //eigen_vector_calculation(sdm_calculator(sensorinputs,size),size,7);

}
