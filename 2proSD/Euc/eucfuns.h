#ifndef __EUCFUNS_H__
#define __EUCFUNS_H__
#include "../headers.h"

int geteucdata(char* data,float *** eucdata,int num,int dim);
int getdim(char* data);
float compEucDist(float* p, float *v,int dim);

#endif
