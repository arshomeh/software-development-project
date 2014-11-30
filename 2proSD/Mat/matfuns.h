#ifndef __MATFUNS_H__
#define __MATFUNS_H__
#include "../headers.h"

int getmatdata(char *data,double ***matdata,int num);
int concint(double ***distarray, int **sortconc, int num,int clust); 
int plusplusmat(double ***distarray, int **kinit, int num, int clust);
int assmat(cluster **clusters,double ***distarray,int clus,int num);
int alalloydmat(cluster **clusters,double ***distarray,int clus,int num);
int claransmat(cluster **clusters,double ***distarray,int clus,int num,int s,int q);
double silhouettes(cluster **clusters, double ***distarray, int clus,char *output);



void freecluster(cluster **clusters,int clus);
void clustinitialize(cluster **clusters,int** tableinit,int clus );
#endif
