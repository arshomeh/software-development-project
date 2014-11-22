#include "headers.h"

int eucMain(char* data,char * config,char *output,int flag){
	int num,dim;
	double **eucdata;
	num = numberOfitems(data,flag);
	dim = getdim(data);
	geteucdata(data,&eucdata,num,dim);
	return 0;
}
