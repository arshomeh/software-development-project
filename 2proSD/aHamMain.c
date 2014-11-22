#include "headers.h"

int hamMain(char* data,char * config,char *output,int flag){
	int num;
	char **hamdata;
	FILE* fp;
	printf("lal\n");
	num = numberOfitems(data,flag);
	printf("aaa\n");
	gethamdata(data,&hamdata,num);
	printf("rrrr\n");
	int j;
	fp = fopen(output,"w");
	for(j = 0;j <num;j++){
		fprintf(fp,"%s\n",hamdata[j]);
	}
	printf("\n");
	fclose(fp);
	return 0;
}
