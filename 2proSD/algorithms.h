#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__
#include "headers.h"

int concint(double ***distarray, int **sortconc, int num,int clust); 
int plusplus(double ***distarray, double ***eucdata, char*** hamdata,  int **kinit,int num, int clust,int nobits, int dim, int flagt);
int pamass(cluster **clusters, double ***distarray, double ***eucdata, char*** hamdata, int num, int clust,int nobit, int dim, int flagt);
int alalloyd(cluster **clusters,double ***distarray, double ***eucdata, char*** hamdata,  int num, int clus,int nobit, int dim, int flagt);
int clarans(cluster **clusters,double ***distarray, double ***eucdata, char*** hamdata, int num, int clus,int nobits, int dim, int flagt,int s,int q);
double silhouettes(cluster **clusters, double ***distarray, int clus,char *output);

#endif
