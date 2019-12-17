/***************************************************************
 *  \Contains the test case functions to be called
 *
 ***************************************************************/

#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "../include/test.h"
#include "../../include/SensorFusionAlgorithm.h"
#include "../../include/input.h"

int main(void)
{
    FILE *fp = fopen("./test/data/testresults.txt","w");
    if(fp == NULL){
        printf("The file open failed \n");
    }
    
    test_sensorinput_from_file(fp);
    test_sdm_calculator(fp);
    test_eigen_value_calculation(fp);
    test_eigen_vector_calculation(fp);
    test_compute_alpha(fp);
    test_compute_phi(fp);
    test_compute_integrated_support_degree_score(fp);
    test_faulty_sensor_and_sensor_fusion(fp);
    
    return 0;
}
