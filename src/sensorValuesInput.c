/** \file sensorValuesInput.c
 * Containing logic to read sensor values from an input file
 */
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "../include/input.h"


/** \brief Function to read inputs from an input file
 *
 *  @param[in] *File Name of file consisting of sensor readings
 *  @param[in,out] array A 2D array to store sensor value sets for
 *   each timestamp given in the input file.
 */
void sensorValueRead(const char *File , double array[][MAX]){
    FILE *fp = fopen(File,"r");
    int count=0;
    char buff[LINE];
    char *sensorTuples[TUPLE_SIZE]; /**< A pointer representation of 2-D array to store each field in a line from CSV */
    char *timestmpValue = NULL;
    int flag = 0;
    int cc = 0;

    while((getc(fp))!=EOF) {

        //To prevent fgets from skipping the first character due to getc in previous step
        fseek(fp, -1, SEEK_CUR);
        fgets(buff, LINE, (FILE*)fp);
        count++;

        //To skip the header line in csv
        if(count!= 1) {
            getData(buff, sensorTuples);

            //To get the sensor Number after omitting prefixed string i.e. 'sens10' becomes '10'
            strcpy(sensorTuples[1],sensorTuples[1]+4);
            if (timestmpValue!=NULL){

            	//To indicate that there is another timestamp for which sensor values are provided
                if(strcmp(timestmpValue,sensorTuples[0])){
                flag = 1;
                }
            }
            timestmpValue = sensorTuples[0];
            if (flag ==1){
                cc++;
                flag = 0;
            }

            //Store the sensor values for each timestamp
            fillArray(sensorTuples, cc, array);
        }
    }

    //Placing a sentinel to indicate end of sensor value set
	array[cc][0] = -1;

    //Freeing all the elements allocated in this function
    for(int rowCounter = 0; rowCounter<TUPLE_SIZE; rowCounter++){
        free(sensorTuples[rowCounter]);
    }
}

/** \brief Function to fill the array of Sensor Values.
 *
 * The generated array would have first element as the number of sensors, second element
 * as one of the timestamps and the rest of the array with values of the sensors for
 * the particular timestamp. This function uses sequential indexing in increasing order.
 * The values not provided are assumed to be zero. Eg. If sensor 1, 2, 5, 6 are given
 * the array stores 6 sensor values from 1 to 6 with sensor 3 and 4 having zero value.
 *
 * @param[in] *sensorTuples
 * @param[in] cc
 * @param[in,out] array
 */
void fillArray(char *sensorTuples[],int cc, double array[][MAX]){
	
	//Time stamp is the second element.
    array[cc][1] = atof(sensorTuples[0]);

    //Index of array matches the sensor number i.e. array[10] contains value for sens10
    array[cc][atoi(sensorTuples[1])+1] = atof(sensorTuples[2]);
    if((int)array[cc][0] < (int)atof(sensorTuples[1])){
        array[cc][0] = (int)atof(sensorTuples[1]);
    }
}

/** \brief Function to tokenize each line read from .csv
 *
 * It creates a tuple which contains timestamp, sensor number
 * and sensor values.
 *
 * @param[in] buff
 * @param[in] *sensorToken
 */
void getData(char buff[], char *sensorToken[]){
    char *token = strtok(buff,",");
    int numTokens=0;

    while(token != NULL) {
        sensorToken[numTokens] = (char *)malloc(sizeof(token));
        if(sensorToken[numTokens]==NULL){
            printf("Malloc in getData Failed. \n");
		}
        strcpy(sensorToken[numTokens],token);
        numTokens++;
        token = strtok(NULL,",");
    }
}
