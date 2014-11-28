#ifndef __HAMFUNS_H__
#define __HAMFUNS_H__
#include "../headers.h"

int gethamdata(char* data,char *** hamdata,int num);
int hamdist(char* a, int nobits, char* b);
//void concint(int ***distarray, int **sortconc, int num,int clust); 
void plusplusham(char ***hamdata, int **kinit, int num, int clust,int nobits);
void assham(cluster **clusters,char ***hamdata,int clus,int num,int nobits);
int alalloydham(cluster **clusters,char ***hamdata,int clus,int num,int nobits);
int claransham(cluster **clusters,char ***hamdata,int clus,int num,int s,int q,int nobits);
//double silhouettes(cluster **clusters, int ***distarray, int clus,char *output);
#endif
