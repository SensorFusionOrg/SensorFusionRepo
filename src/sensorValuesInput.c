/*********************************************************************   
* Function to read inputs from an input file. The
*
* input: input file in CSV format
* output: SensorValues, a 2-D array to store sensor value sets for     
* each timestamp given in the input file. 
**********************************************************************/
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "../include/input.h"

#define MAX 512
#define TUPLE_SIZE 3

void sensorValueRead(const char *File , double array[][MAX]) {
	FILE *fp = fopen(File,"r");
	if (fp == NULL) {
    		printf("File Open Failed\n");
    		return;
	}
        int count=0;
	int counter = 0; // counts the number of tuples being inputted
	char buff[MAX];
	char **sensorTuples[MAX]; // A pointer representation of 3-D array to store the dataset from CSV
	double sensorValues[MAX];
	int timeStampSet = 0;

    	while((getc(fp))!=EOF) {
		fseek(fp, -1, SEEK_CUR); // to prevent fgets from skipping the first character due to getc in previous step
    		fgets(buff, MAX, (FILE*)fp);
    		count++;
    		if(count != 1) { // to skip the header line in csv
			sensorTuples[counter]=(char**)malloc(sizeof(char*));
    	 		getData(buff, sensorTuples[counter]);
			strcpy(sensorTuples[counter][1],sensorTuples[counter][1]+4); //To get the sensor Number after omitting prefixed string i.e. 'sens10' becomes '10'	
			if(count >2 && strcmp(sensorTuples[counter][0],sensorTuples[counter-1][0])){ //Check if the sensor values are from a single timestamp
				fillArray(timeStampSet, counter, sensorTuples, sensorValues, array);
				timeStampSet++;
				for(int c = 0; c < TUPLE_SIZE; c++)
					strcpy(sensorTuples[0][c],sensorTuples[counter][c]); //copying the last line read by fgets
				counter = 1; // resetting the counter for next time stamp
				continue;
			}
		counter++;
		} 
    	}
	fillArray(timeStampSet, counter, sensorTuples, sensorValues, array); // For the last timestamp
	array[timeStampSet+1][0] = -1;
/*****************************************************************************************************************
*
* Freeing all the elements allocated in this function
******************************************************************************************************************/
	for(int tupleCounter = 0; tupleCounter < counter; tupleCounter++) {
		for (int fieldCounter = 0;fieldCounter < TUPLE_SIZE; fieldCounter++){
		free(sensorTuples[tupleCounter][fieldCounter]);
		}
	}
	for(int rowCounter = 0; rowCounter<counter; rowCounter++){
		free(sensorTuples[rowCounter]);
	}
	fclose(fp);	
}
/********************************************************************************************************************
* Function to fill the array of Sensor Values with the First element as the number of sensor, second element 
* being one of the timestamp and rest of the array with values of the sensors for the particular timestamp at array[1]
* This function use sequential indexing in increasing order. The values not provided are assumed to be zero. Eg. if 
* sensor 1, 2, 5, 6 are given the array stores 6 sensor values from 1 to 6 with sensor 3 and 4 having zero value.
*********************************************************************************************************************/ 
void fillArray(int timeStampSet, int counter, char **sensorTuples[], double *sensorValues, double array[][MAX]){
	memset(sensorValues, '\0', MAX);	
	sensorValues[1] = atof(sensorTuples[counter-1][0]); //timestamp is the second element.
	int maxIndex = 0;
	for (int j=0; j<counter; j++){
		sensorValues[atoi(sensorTuples[j][1])+1] = atof(sensorTuples[j][2]); // Index of array matches the sensor number i.e. array[10] contains value for sens10
		if(maxIndex< atoi(sensorTuples[j][1])) {
			maxIndex = atoi(sensorTuples[j][1]); 
		}	
	}
	sensorValues[0] = maxIndex; //Number of sensors is the first element
	for (int countArray = 0; countArray < maxIndex+2; countArray++){
		array[timeStampSet][countArray] = sensorValues[countArray];
        }
	memset(sensorValues, '\0', MAX);
}
/********************************************************************************************************
* Function to tokenize each line read from .csv and create a tuple which contain timestamp, sensor number 
* and sensor values
*
********************************************************************************************************/   
void getData(char buff[], char *sensorToken[TUPLE_SIZE])
{
	char *token = strtok(buff,",");
	int numTokens=0;
     	
	while(token != NULL) {
		sensorToken[numTokens] = (char *)malloc(sizeof(token));
		strcpy(sensorToken[numTokens],token); 
		numTokens++; 
		token = strtok(NULL,",");
	}	  
}
