/***************************************************************
 *  \Contains the function declarations to be used by the main.c 
 *  to invoke the functions defined in sensorValuesInput.c and
 *  SensorFusionAlgorithm.c
 ***************************************************************/

#ifndef test_h
#define test_h

#include <stdlib.h>
#include <string.h>

#define MAX 512
#define SIZE 5

    FILE *fp, fpin;
    void test_sensorinput_from_file(FILE *fpout);
    void test_sdm_calculator(FILE *fp);
    void test_eigen_value_calculation(FILE *fp);
    void test_eigen_vector_calculation(FILE *fp);
    void test_compute_alpha(FILE *fp);
    void test_compute_phi(FILE *fp);
    void test_compute_integrated_support_degree_score(FILE *fp);
    void test_faulty_sensor_and_sensor_fusion(FILE *fp);


#endif /* test_h */
