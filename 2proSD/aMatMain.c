#include "headers.h"

int matMain(char* data,char * config,char *output,int flag){
	int num;
	int **matdata;
	num = numberOfitems(data,flag);
	getmatdata(data,&matdata,num);
	return 0;
}
