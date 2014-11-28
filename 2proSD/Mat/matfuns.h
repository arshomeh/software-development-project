#ifndef __MATFUNS_H__
#define __MATFUNS_H__
#include "../headers.h"

int getmatdata(char *data,int ***matdata,int num);
void concint(int ***distarray, int **sortconc, int num,int clust); 
void plusplusmat(int ***distarray, int **kinit, int num, int clust);
void assmat(cluster **clusters,int ***distarray,int clus,int num);
int alalloydmat(cluster **clusters,int ***distarray,int clus,int num);
int claransmat(cluster **clusters,int ***distarray,int clus,int num,int s,int q);
double silhouettes(cluster **clusters, int ***distarray, int clus,char *output);



void freecluster(cluster **clusters,int clus );
void clustinitialize(cluster **clusters,int** tableinit,int clus );
#endif
