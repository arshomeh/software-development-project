#ifndef __EUCFUNS_H__
#define __EUCFUNS_H__
#include "../headers.h"

int geteucdata(char* data,double *** eucdata,int num,int dim);
int getdim(char* data);
double compEucDist(double* p, double *v,int dim);

#endif
