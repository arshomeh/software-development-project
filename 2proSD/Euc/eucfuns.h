#ifndef __EUCFUNS_H__
#define __EUCFUNS_H__
#include "../headers.h"

int geteucdata(char* data,double *** eucdata,int num,int dim);
int getdim(char* data);
double compEucDist(double* p, double *v,int dim);


int pluspluseuc(double ***eucdata, int **kinit, int num, int clust,int dim);
int asseuc(cluster **clusters,double ***eucdata,int clus,int num,int dim);
int alalloydeuc(cluster **clusters,double ***eucdata,int clus,int num,int dim);
int claranseuc(cluster **clusters,double ***eucdata,int clus,int num,int s,int q,int dim);
#endif
