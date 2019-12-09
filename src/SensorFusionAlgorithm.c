
#include "SensorFusionAlgorithm.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double** SDMCalculator(double sensorinputs[])
{
    int i,j;
    int size = sizeof(sensorinputs);
    double **d = (double **)malloc(sizeof(double *)*size);
    for(i=0; i<size;i++)
    {
        for(j=0;j<size;j++){
            double temp = sensorinputs[i]-sensorinputs[j];
            if(temp<0){
                temp = -temp;
            }
            d[i][j] = exp(-(temp));
        }
    }
    return d;
}


