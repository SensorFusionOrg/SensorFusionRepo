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
    double Eigenvalues[] = {5.412,1.1082,0.9891,0.1884,0.1446,0.0931,0.0645,0};
    int size = sizeof(Eigenvalues)/sizeof(double);
    if(size>0){
        double c_rate_list[size];
        double acc_c_rate_list[size];
        compute_alpha_and_phi(Eigenvalues,size,c_rate_list,acc_c_rate_list);
        //Displaying Alpha List
        for(int i=0; i< (sizeof(c_rate_list)/sizeof(double));i++){
            printf("alpha[%d] =  %lf; ",i,c_rate_list[i]);
        }
        printf("\n");
        //Displaying Phi List
        for(int i=0; i< (sizeof(acc_c_rate_list)/sizeof(double));i++){
            printf("phi[%d] =  %lf; ",i,acc_c_rate_list[i]);
        }
    }
}
