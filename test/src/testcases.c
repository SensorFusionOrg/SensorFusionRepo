/******************************************************************************************   
* \File containing test case definitions for each function defined in the program
* Each test case calls the function and gets the returned values. It then checks those values
* against the expected value from the function. If both match, the test case passes 
* otherwise it fails.
*******************************************************************************************/
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include "../include/test.h"
#include "../../include/SensorFusionAlgorithm.h"
#include "../../include/input.h"

void test_sensorinput_from_file(FILE *fpout){
    int numtimestamp = 0;
    int flag = 0;
    double sensorvaluesets[MAX][MAX];
    memset(sensorvaluesets, '\0', MAX*MAX);

    sensorValueRead("./test/include/input/input.csv", sensorvaluesets);
    double ExpectedSensorValues[] = { 8.00, 10.3, 53.2, 52.6, 42.7, 53.2, 52.8, 53.3, 45.7, 53.1,
                                      8.00, 11.3, 12.3, 11.4, 7.10, 8.30, 9.40, 5.10, 9.40, 10.3,
                                      8.00, 20.3, 13.5, 12.3, 13.2, 13.1, 14.0 ,9.30, 0.00, 8.70 };

    for (int timestampsetcounter = 0; timestampsetcounter < numtimestamp; timestampsetcounter++) {
        for(int numsens = 0; numsens < sensorvaluesets[timestampsetcounter][0]; numsens++){
	//Since we are comparing to double, it needs to checked if the difference between the two does not exceed a certain limit. 
	//We cannot use the '==' operator as it may not give correct result in case of comparison between double
            if(fabs(sensorvaluesets[timestampsetcounter][numsens] - *(ExpectedSensorValues + timestampsetcounter*10 + numsens)) > 0.001){
            flag = 1;
            }
        }
    }	
    if(flag==0){
        fprintf(fpout, "%s---> %s\n",__func__, "Passed");
    }else {
        fprintf(fpout, "%s---> %s\n",__func__, "Failed");
    }
}

/************************************************************************************
 * \This function tests the sdm calculator function outputs against the expected value
 * It writes Passed or Failed into a file according to the outcome of the test.
 * 
 * @param :               FILE
 * @return:               void
 ************************************************************************************/


void test_sdm_calculator(FILE *fp){
    int flag = 0;     
    double SDM_ExpectedValue[] = { 1.00000, 0.548812, 0.000028, 1.000000, 0.670320,	
                                  0.548812, 1.000000, 0.000050, 0.548812, 0.818731,	
                                  0.000028, 0.000050, 1.000000, 0.000028, 0.000041,	
                                  1.000000, 0.548812, 0.000028, 1.000000, 0.670320,	
                                  0.670320, 0.818731, 0.000041, 0.670320, 1.000000 };
    double sensorValues[] = {53.2, 52.6, 42.7, 53.2, 52.8};

    double* ActualValue = sdm_calculator(sensorValues,SIZE);
    for(int counter = 0; counter < SIZE*SIZE; counter++){
        if(fabs(ActualValue[counter]-SDM_ExpectedValue[counter])>0.001){
            flag = 1;
            break;
        }
    }
    if(flag==0){
        fprintf(fp, "%s---> %s\n",__func__, "Passed");
    }else {
        fprintf(fp, "%s---> %s\n",__func__, "Failed");
    }
}
/**********************************************************************************************
 * \This function tests the eigen_value_calculation function outputs against the expected value
 * It writes Passed or Failed into a file according to the outcome of the test.
 * 
 * @param :               FILE
 * @return:               void
 **********************************************************************************************/

void test_eigen_value_calculation(FILE *fp){
    int flag = 0;
    double dmatrix[] = 	        { 1.00000, 0.548812, 0.000028, 1.000000, 0.670320,	
                                  0.548812, 1.000000, 0.000050, 0.548812, 0.818731,	
                                  0.000028, 0.000050, 1.000000, 0.000028, 0.000041,	
                                  1.000000, 0.548812, 0.000028, 1.000000, 0.670320,	
                                  0.670320, 0.818731, 0.000041, 0.670320, 1.000000 };

    double eigenValue_ExpectedValue[] = {3.13455, 1, 0.699964, 0.165487, 2.0571e-16};

    double* ActualValue =  eigen_value_calculation(dmatrix,SIZE);

    for(int counter = 0; counter < SIZE; counter++){
       	if(fabs(ActualValue[counter]-eigenValue_ExpectedValue[counter])>0.001){
            flag = 1;
            break;
        }
    }
    if(flag==0){
        fprintf(fp, "%s--> %s\n",__func__, "Passed");
    }else {
        fprintf(fp, "%s--> %s\n",__func__, "Failed");
    }
}
/***********************************************************************************************
 * \This function tests the eigen_vector_calculation function outputs against the expected value
 * It writes Passed or Failed into a file according to the outcome of the test.
 * 
 * @param :               FILE
 * @return:               void
 ***********************************************************************************************/

void test_eigen_vector_calculation(FILE *fp){
    int flag = 0;
    double dmatrix[] = 	        { 1.00000, 0.548812, 0.000028, 1.000000, 0.670320,	
                                  0.548812, 1.000000, 0.000050, 0.548812, 0.818731,	
                                  0.000028, 0.000050, 1.000000, 0.000028, 0.000041,	
                                  1.000000, 0.548812, 0.000028, 1.000000, 0.670320,	
                                  0.670320, 0.818731, 0.000041, 0.670320, 1.000000 };

    double eigenVector_ExpectedValue[] ={-0.518457,-0.45903,-3.39905e-05,-0.518457,-0.501692};

    double* ActualValue =  eigen_vector_calculation(dmatrix,SIZE,0);
    for(int counter = 0; counter < SIZE; counter++){
       	if(fabs(ActualValue[counter]-eigenVector_ExpectedValue[counter])>0.001){
            flag = 1;
            break;
        }
    }
    if(flag==0){
        fprintf(fp, "%s--> %s\n",__func__, "Passed");
    }else {
        fprintf(fp, "%s--> %s\n",__func__, "Failed");
    }
}
/************************************************************************************
 * \This function tests the compute_alpha function outputs against the expected value
 * It writes Passed or Failed into a file according to the outcome of the test.
 * 
 * @param :               FILE
 * @return:               void
 ************************************************************************************/

void test_compute_alpha(FILE *fp){
    int flag = 0;
    double eigenValue[] = {3.13455, 1, 0.699964, 0.165487, 2.0571e-16};
    double alpha_ExpectedValue[] = {0.62690987, 0.19999996, 0.13999277, 0.03309739, 0.000000};
    double *ActualValue = compute_alpha(eigenValue, SIZE);
    for(int counter = 0; counter < SIZE; counter++){
       	if(fabs(ActualValue[counter]-alpha_ExpectedValue[counter])>0.01){
            flag = 1;
            break;
        }
    }
    if(flag==0){
        fprintf(fp, "%s--> %s\n",__func__, "Passed");
    }else {
        fprintf(fp, "%s--> %s\n",__func__, "Failed");
    }
}
/************************************************************************************
 * \This function tests the compute_phi function outputs against the expected value
 * It writes Passed or Failed into a file according to the outcome of the test.
 * 
 * @param :               FILE
 * @return:               void
 ************************************************************************************/

void test_compute_phi(FILE *fp){
    int flag = 0;
    double alphaValues[] = {0.62690987,0.19999996,0.13999277,0.3309739,0.000000};
    double phi_ExpectedValue[] = {0.62690987, 0.826910, 0.966903, 1.297876, 1.297876};
    double* ActualValue = compute_phi(alphaValues, SIZE);
    for(int counter = 0; counter < SIZE; counter++){
       	if(fabs(ActualValue[counter]-phi_ExpectedValue[counter])>0.001){
            flag = 1;
            break;
        }
    }
    if(flag==0){
        fprintf(fp, "%s--> %s\n",__func__, "Passed");
    }else {
        fprintf(fp, "%s--> %s\n",__func__, "Failed");
    }
}
/**************************************************************************************************************
 * \This function tests the compute_integrated_support_degree_score function outputs against the expected value
 * It writes Passed or Failed into a file according to the outcome of the test.
 * 
 * @param :               FILE
 * @return:               void
 **************************************************************************************************************/

void test_compute_integrated_support_degree_score(FILE *fp){
    int flag = 0;
    double dmatrix[] = 	        { 1.00000, 0.548812, 0.000028, 1.000000, 0.670320,	
                                  0.548812, 1.000000, 0.000050, 0.548812, 0.818731,	
                                  0.000028, 0.000050, 1.000000, 0.000028, 0.000041,	
                                  1.000000, 0.548812, 0.000028, 1.000000, 0.670320,	
                                  0.670320, 0.818731, 0.000041, 0.670320, 1.000000 };
    double sensorValues[] = {53.2, 52.6, 42.7, 53.2, 52.8};
    double alpha[] = {0.62690987,0.19999996,0.13999277,0.3309739,0.000000};
    double phi[] = {0.62690987, 0.826910, 0.966903, 1.297876, 1.297876};

    double Z_ExpectedValue[] = {-1.065072, -0.840775, -0.200074, -1.065072, -0.946284};
    double* ActualValue = compute_integrated_support_degree_score(sensorValues, alpha, phi, dmatrix, 0.85, SIZE);
    for(int counter = 0; counter < SIZE; counter++){
       	if(fabs(ActualValue[counter]-Z_ExpectedValue[counter])>0.001){
            flag = 1;
            break;
        }
    }
    if(flag==0){
        fprintf(fp, "%s---> %s\n",__func__, "Passed");
    }else {
        fprintf(fp, "%s---> %s\n",__func__, "Failed");
    }
}
/***********************************************************************************************************
 * \This function tests the faulty_sensor_and_sensor_fusion function outputs against the expected value
 * It writes Passed or Failed into a file according to the outcome of the test.
 * 
 * @param :               FILE 
 * @return:               void
 ***********************************************************************************************************/

void test_faulty_sensor_and_sensor_fusion(FILE *fp){
    int flag = 0;
    double sensorValues[] = {53.2, 52.6, 42.7, 53.2, 52.8};
    double Z[] = {-1.065072, -0.840775, -0.200074, -1.065072, -0.946284};
    double ExpectedValue = 52.974590;
    double ActualValue = faulty_sensor_and_sensor_fusion(Z, sensorValues, SIZE);
    for(int counter = 0; counter < SIZE; counter++){
       	if(fabs(ActualValue-ExpectedValue)>0.001){
            flag = 1;
            break;
        }
    }
    if(flag==0){
        fprintf(fp, "%s--> %s\n",__func__, "Passed");
    }else {
        fprintf(fp, "%s--> %s\n",__func__, "Failed");
    }
}

