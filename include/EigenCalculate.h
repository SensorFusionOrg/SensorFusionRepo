//
//  EigenCalculate.h
//  SensorFusionRepo
//
//  Created by Rishabh Jiresal on 2019-10-31.
//  Copyright © 2019 Rishabh Jiresal. All rights reserved.
//

#ifndef EigenCalculate_h
#define EigenCalculate_h

#define REAL   double
#define TRUE   1
#define FALSE  0
#define ZERO   0.
#define ONE    1.
#define TWO    2.
#define VEKTOR 0
#define MACH_EPS DBL_EPSILON

#define ABS(x) (((x) >= 0.)? (x) : -(x))
#define SQRT(x) sqrt(x)
#define SQR(x) ((x) * (x))
#define SWAP(typ, a, b) { typ t; t = (a); (a) = (b); (b) = t; }
#define BASIS basis()

#endif /* EigenCalculate_h */
