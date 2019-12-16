/** \file main.c
 * Contains the main function from which different functions
 * located in other file are called to perform different
 * tasks of the algorithm.
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../include/SensorFusionAlgorithm.h"
#include "../include/input.h"


/** \brief The main function which distributes various tasks to other functions
 *
 *  Expects a csv file ./input/input.csv which contains the sensor readings.
 *  Calls the functions that perform the algorithm iteratively for each time
 *  stamp in the input file and then produces an output file ./output/results.txt
 *  containing the fused value for each time stamp and a list of faulty sensors.
 */
int main(void){
    int timestampsetcounter = 0;
    int numtimestamp = 0;
    double sensorvaluesets[MAX][MAX];
    memset(sensorvaluesets, '\0', MAX*MAX);
    sensorValueRead("./input/input.csv",sensorvaluesets);

    //Creating a file for output which will hold the results
    FILE *fpoutput = fopen("./output/results.txt","w");
    if (fpoutput == NULL) {
        printf("File Open for Write Failed\n");
        return 1;
    }
    fclose(fpoutput);

    //Scans through the entire set of input sets and stops at the end of data set
    while((int)sensorvaluesets[timestampsetcounter][0]!= -1){
        numtimestamp++;
        timestampsetcounter++;
    }
    double fusion_result[numtimestamp];
    double *sensorinputs[numtimestamp];

    //First element is the number of sensors read from the .csv file
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

        //Calling the fusion algorithm functions for readings of current time stamp in loop
        fusion_result[timestampsetcounter] = faulty_sensor_and_sensor_fusion(
        		compute_integrated_support_degree_score(sensorinputs[timestampsetcounter],
        		compute_alpha(eigen_value_calculation(sdm_calculator(
        		sensorinputs[timestampsetcounter],(int)sensorvaluesets[timestampsetcounter][0]),
        		(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]),
				compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(
				sensorinputs[timestampsetcounter],(int)sensorvaluesets[timestampsetcounter][0]),
				(int)sensorvaluesets[timestampsetcounter][0]),(int)sensorvaluesets[timestampsetcounter][0]),
				(int)sensorvaluesets[timestampsetcounter][0]),sdm_calculator(sensorinputs[timestampsetcounter],
				(int)sensorvaluesets[timestampsetcounter][0]),0.85,(int)sensorvaluesets[timestampsetcounter][0]),
				sensorinputs[timestampsetcounter],(int)sensorvaluesets[timestampsetcounter][0]);
        printf("Fusion result : %lf",fusion_result[timestampsetcounter]);
        printf("\n");

        //Opening the output file in append mode
        fpoutput = fopen("./output/results.txt","a+");
        if (fpoutput == NULL) {
            printf("File Open for Write Failed\n");
            return 1;
        }

        //Printing the fusion result into the file
        fprintf(fpoutput, "%s: %lf","Fusion result",fusion_result[timestampsetcounter]);
        fprintf(fpoutput, "%s","\n");
        fclose(fpoutput);
    }
	//faulty_sensor(Z,size);
	//compute_phi(compute_alpha(eigen_value_calculation(sdm_calculator(sensorinputs, size), size),size),size);
    //eigen_vector_calculation(sdm_calculator(sensorinputs,size),size,7);
}
