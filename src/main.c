#include "EigenCalculate.h"
#include "SensorFusionAlgorithm.h"
#include "matrix.h"
#include <stdio.h>

int main(int argc, const char * argv[]) {
   // int i;
    matrix* vector1,b;
    double a[2][2] = {{6,-1},{2,3}};
    double* eval;
    eval = EigenValueCalculate(a);
    vector1 = eigenvector(a,5);
    printMatrix(vector1);
}
