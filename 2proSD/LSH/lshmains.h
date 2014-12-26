#ifndef __LSHMAINS_H__
#define __LSHMAINS_H__

#include "headers.h"

int HamMain(char * Data,int k,int L);
int Hamquery(char *binary,int k, int L,int rad);
void MatMain(char * Data,int k,int L);
int Matquery(int* query,int k, int L,int rad);
int VecMain(char * Data,int k,int L);
int Eucquery(double* query,int k, int L,int rad);
#endif
