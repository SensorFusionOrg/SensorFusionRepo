/***************************************************************
 *  Contains the function declarations to be used by the main.c 
 *  to invoke the functions defined in sensorValuesInput.c
 *  
 ***************************************************************/

#ifndef input_h
#define input_h

#define MAX 512
#define TUPLE_SIZE 3

void sensorValueRead(const char *File , double array[][MAX]);
void getData(char *buff, char *sensorToken[TUPLE_SIZE]);
void fillArray(int timeStampSet, int counter, char **sensorTuples[], double sensorValues[], double array[][MAX]);

#endif /* input_h */
