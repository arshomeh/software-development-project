#include "../headers.h"

int geteucdata(char* data,double *** eucdata,int num,int dim){
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
	for(i = 0;i < num;i++){
		fscanf(fp, "%s",XXX);
		if(((*eucdata)[i] =  malloc(dim * sizeof(double))) == NULL){
				printf("\nj is -->%d || i is -->%d\n",j,i);
				perror("2:");
				exit(4);
		}
		for(j = 0;j < dim; j++){
			char kk[50];
			char *ptr;
			fscanf(fp,"%s",kk);
			(*eucdata)[i][j] = strtold(kk, &ptr);
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

double compEucDist(double* p, double *v,int dim){
	double sum = 0;
	double EucDist;
	int i = 0;
	for (i = 0;i<dim;i++){
		sum += pow((p[i]-v[i]),2);
	}
	return EucDist = sqrt(sum);
}

