#ifndef __MAINFUNS_H__
#define __MAINFUNS_H__
#include "headers.h"

struct configuration{
	int Clasters;
	int HashFunctions;
	int HashTables;
	int ClaransFraction;
	int ClaransIterations;
};
typedef struct configuration configuration;

configuration setConfig(char* config);

#endif
