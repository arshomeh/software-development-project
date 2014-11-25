#include "../headers.h"

int geteucdata(char* data,float *** eucdata,int num,int dim){
	int i;
	int j;
	char XXX[SIZEofBUFF];
	FILE* fp;
	fp = fopen(data,"r");
	if(((*eucdata)= malloc(num * sizeof(double*))) == NULL){
		perror("1:");
		exit(4);
	}
	fscanf(fp, "%s %s %s %s",XXX,XXX,XXX,XXX);
	printf("%s",XXX);
	for(i = 0;i < num;i++){
		fscanf(fp, "%s",XXX);
		for(j = 0;j < dim; j++){
			char kk[50];
			char *ptr;
			fscanf(fp,"%s",kk);
			if(((*eucdata)[i] =  malloc(dim * sizeof(float))) == NULL){
				printf("\nj is -->%d || i is -->%d\n",j,i);
				perror("2:");
				exit(4);
			}
			(*eucdata)[i][j] = strtod(kk, &ptr);
		}
	}
	fclose(fp);
	return 0;
}

int getdim(char* data){
	int dim = 1;
	char c;
	char XXX[SIZEofBUFF];
	FILE* fp;
	fp = fopen(data,"r");
	fscanf(fp, "%s %s",XXX,XXX);
	fscanf(fp, "%s %s",XXX,XXX);
	fscanf(fp, "%s %s",XXX,XXX);
	c = getc(fp);
	while(c != '\n'){
		if(c == '\t' || c == ' ')
			dim++;
		c = getc(fp);
	}
	fclose(fp);
	return dim;
}

float compEucDist(float* p, float *v,int dim){
	float sum = 0;
	float EucDist;
	int i = 0;
	for (i = 0;i<dim;i++){
		sum += pow((p[i]-v[i]),2);
	}
	return EucDist = sqrt(sum);
}
