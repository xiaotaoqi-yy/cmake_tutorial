//
// Created by yy on 18-5-14.
//
#include "MathFunctions.h"
#include <math.h>
#include "TutorialConfig.h"

double mysqrt(double x){
  double result;
// if we have both log and exp then use them
#if defined(HAVE_LOG) && defined(HAVE_EXP)
  result = exp(log(x)*0.5);
#else
  result = pow(x,0.5);
#endif
  return result;
}
