#include "headers.h"

int matMain(char* data,char * config,char *output,int flag){
	int num,i,j;
	FILE* fp;
	int **matdata;
	fp = fopen(output,"w");
	num = numberOfitems(data,flag);
	printf("num is %d\n",num);
	getmatdata(data,&matdata,num);
	//printf("num is %d\n",num);
	/*for(i = 0;i<num;i++){
		fprintf(fp,"item%d || ",i);
		 for(j = 0;j <num;j++){
			fprintf(fp,"%d ",matdata[i][j]);
		}
		fprintf(fp,"\n");
	}*/
	return 0;
}
