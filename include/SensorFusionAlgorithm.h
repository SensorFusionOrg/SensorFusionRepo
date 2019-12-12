/**
 *  Contains the functions which are defined in a very beginning of the
 *  project. These functions will be changed according to the
 *  convenience and flow of the code. The major aim is to reduce the
 *  complexity of the program which will lead to least data confusion
 *  and conversion. The defined functions will be cut down into other
 *  functions if needed for the modularity and the ease of use.
 */

#ifndef SensorFusionAlgorithm_h
#define SensorFusionAlgorithm_h

#include <stdio.h>

/*
 * This function calculates the SDM and its Eigen values and vectors
 */
extern void sdm_calculator();

/*
 * This function will calculate all the principal components of the
 * D matrix
 */
extern double* PrincipalComponents(void);

/*
 * This function will calculate and eliminate the incorrect data
 */
extern double* ComputationScore(void);

/*
 * This function will return the fused output to the main function
 */
extern double* OutputCompute(void);

#endif /* SensorFusionAlgorithm_h */
