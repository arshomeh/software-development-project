#include "headers.h"

int eucMain(char* data,char * config,char *output,int flag){
	int num,dim;
	FILE* fp;
	float **eucdata;
	float **distance;
	fp = fopen(output,"w");
	num = numberOfitems(data,flag);
	printf("num is %d\n",num);
	dim = getdim(data);
	printf("dim is %d\n",dim);
	geteucdata(data,&eucdata,num,dim);
	int i,j;
	for(i = 0;i<num;i++){
		 for(j = 0;j <dim;j++){
			fprintf(fp,"%f \n",eucdata[i][j]);
		}
		printf("\n");
	}
	distance = malloc(num* sizeof(float*));
	
	for(j = 0;j<num; j++)
		distance[j] = malloc(num* sizeof(float));
		
	/*for(i = 0;i<num;i++){
		distance[i][i] = 0;
		for(j = i+1;j<num;j++){
			distance[i][j] = compEucDist(eucdata[i],eucdata[j],dim);
			distance[j][i] = distance[i][j];
		}
	}*/
	fclose(fp);
	return 0;
}
