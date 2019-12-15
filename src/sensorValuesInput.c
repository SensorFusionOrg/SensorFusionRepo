/*********************************************************************   
* File containing logic to read sensor values from an input file.
* 
**********************************************************************/
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "../include/input.h"

/*********************************************************************   
* Function to read inputs from an input file. The
*
* @input: input file in CSV format
* @output: SensorValues, a 2-D array to store sensor value sets for     
* each timestamp given in the input file. 
**********************************************************************/

void sensorValueRead(const char *File , double array[][MAX])
{
	FILE *fp = fopen(File,"r");
        int count=0;
	char buff[50];
	char *sensorTuples[TUPLE_SIZE]; // A pointer representation of 2-D array to store each field in a line from CSV
	char *timestmpValue = NULL;
	int flag = 0;
	int cc = 0;

    	while((getc(fp))!=EOF) {
		fseek(fp, -1, SEEK_CUR); // to prevent fgets from skipping the first character due to getc in previous step
    		fgets(buff, 50, (FILE*)fp);
    		count++;
    		if(count!= 1) { // to skip the header line in csv

    	 		getData(buff, sensorTuples);
			strcpy(sensorTuples[1],sensorTuples[1]+4); //To get the sensor Number after omitting prefixed string i.e. 'sens10' becomes '10'
			if (timestmpValue!=NULL){
				if(strcmp(timestmpValue,sensorTuples[0]))
					flag = 1;		// To indicate that there is another timestamp for which sensor values are provided
					
			}
			timestmpValue = sensorTuples[0];
			if (flag ==1){
				cc++;
				flag = 0;
			}
			fillArray(sensorTuples, cc, array);	// Store the sensor values for each timestamp
		} 
    	}
	array[cc][0] = -1;	// Placing a sentinel to indicate end of sensor value set
/*****************************************************************************************************************
*
* Freeing all the elements allocated in this function
******************************************************************************************************************/
	for(int rowCounter = 0; rowCounter<TUPLE_SIZE; rowCounter++){
		free(sensorTuples[rowCounter]);
	}	
}
/********************************************************************************************************************
* Function to fill the array of Sensor Values with the First element as the number of sensor, second element 
* being one of the timestamp and rest of the array with values of the sensors for the particular timestamp at array[1]
* This function use sequential indexing in increasing order. The values not provided are assumed to be zero. Eg. if 
* sensor 1, 2, 5, 6 are given the array stores 6 sensor values from 1 to 6 with sensor 3 and 4 having zero value.
*********************************************************************************************************************/ 
void fillArray(char *sensorTuples[],int cc, double array[][MAX]){
		
	array[cc][1] = atof(sensorTuples[0]); //timestamp is the second element.	
	array[cc][atoi(sensorTuples[1])+1] = atof(sensorTuples[2]); // Index of array matches the sensor number i.e. array[10] contains value for sens10
	if((int)array[cc][0] < (int)atof(sensorTuples[1]))
		array[cc][0] = (int)atof(sensorTuples[1]);
	
}
/********************************************************************************************************
* Function to tokenize each line read from .csv and create a tuple which contain timestamp, sensor number 
* and sensor values
*
********************************************************************************************************/   
void getData(char buff[], char *sensorToken[])
{
	char *token = strtok(buff,",");
	int numTokens=0;
     	
	while(token != NULL) {
		sensorToken[numTokens] = (char *)malloc(sizeof(token));
		if(sensorToken[numTokens]==NULL)
		{
			printf("Malloc in getData Failed. \n");
		}
		strcpy(sensorToken[numTokens],token); 
		numTokens++; 
		token = strtok(NULL,",");
	}	  
}
