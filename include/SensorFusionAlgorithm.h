/*These are the functions which are defined in a very beginning of the project. These functions will be changed according to the convenience and flow of the code. The major aim is to reduce the complexity of the program which will lead to least data confusion and conversion. The defined functions will be cut down into other functions if needed for the modularity and the ease of use.*/

#ifndef SensorFusionAlgorithm_h
#define SensorFusionAlgorithm_h

#include <stdio.h>

extern double** SDMCalculator(double[]); // This function will calculate the support degree matrix and return it to the requesting function
extern double* PrincipalComponents(void); //This function will calculate all the principal components of the D matrix
extern double* ComputationScore(void); //This function will calculate and eliminate the incorrect data
extern double* OutputCompute(void); // This function will return the fused output to the main function

#endif /* SensorFusionAlgorithm_h */
