#ifndef __EUCFUNS_H__
#define __EUCFUNS_H__
#include "../headers.h"

int geteucdata(char* data,float *** eucdata,int num,int dim);
int getdim(char* data);
float compEucDist(float* p, float *v,int dim);


void pluspluseuc(float ***eucdata, int **kinit, int num, int clust,int dim);
void asseuc(cluster **clusters,float ***eucdata,int clus,int num,int dim);
int alalloydeuc(cluster **clusters,float ***eucdata,int clus,int num,int dim);
int claranseuc(cluster **clusters,float ***eucdata,int clus,int num,int s,int q,int dim);
#endif
