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
