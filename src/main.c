/** \brief Main file from which different functions located in other files are
 *        called to perform different tasks of the algorithm.
 *
 *  Currently only the implementation of Support Degree Matrix and calculation
 *  of eigen values and vectors has been done by calling the sdm_calculator()
 *  function in SensorFusionAlgorithm file.
 *
 */
#include <stdio.h>
#include <math.h>
#include "SensorFusionAlgorithm.h"

/** \brief The main function which distributes various tasks to other functions
 *
 *  Only the sdm_calculator function has been called as that's the only
 *  function that is completed.
 */
int main(void){

    printf("Calling sdm_calculator \n");
    sdm_calculator();
}
