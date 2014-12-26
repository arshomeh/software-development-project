#ifndef __GENERAL_H__
#define __GENERAL_H__

#include "headers.h"

struct configuration{
	int Clasters;
	int HashFunctions;
	int HashTables;
	int ClaransFraction;
	int ClaransIterations;
};
typedef struct configuration configuration;

configuration setConfig(char* config,int num);
int readData(char* data,char* config);
int printData(char* data,int flag);
int getUniformInt(int rStart, int rEnd);
double getUniformDouble(double rStart, double rEnd);
void printclusters(cluster **clusters,int complarga, char *filep, int iflag, int aflag, int uflag,int clus,double ttime, double totdis);
double computecost(cluster **clusters,double ***distarray,double ***eucdata, char*** hamdata,int clus, int num,int nobits, int dim, int flagt,int m, int t);
void freecluster(cluster **clusters,int clus);
void clustinitialize(cluster **clusters,int** tableinit,int clus );
#endif
