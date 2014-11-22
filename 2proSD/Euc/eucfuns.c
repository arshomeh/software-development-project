#include "../headers.h"

int geteucdata(char* data,double *** eucdata,int num,int dim){
	int i;
	int j;
	char XXX[SIZEofBUFF];
	FILE* fp;
	fp = fopen(data,"r");
	(*eucdata)= malloc(num * sizeof(double*));
	fscanf(fp, "%s %s %s %s",XXX,XXX,XXX,XXX);
	for(i = 0;i < num;i++){
		fscanf(fp, "%s",XXX);
		for(j = 0;j < dim; j++){
			char kk[50];
			char *ptr;
			fscanf(fp,"%s",kk);
			(*eucdata)[i] =  malloc(dim * sizeof(double));
			(*eucdata)[i][j] = strtod(kk, &ptr);
		}
	}
	fclose(fp);
	return 0;
}

int getdim(char* data){
	int dim;
	char c;
	char XXX[SIZEofBUFF];
	FILE* fp;
	fp = fopen(data,"r");
	fscanf(fp, "%s %s",XXX,XXX);
	fscanf(fp, "%s %s",XXX,XXX);
	while(c != '\n'){
		if(c == '\t' || c == ' ')
			dim++;
		c = getc(fp);
	}
	fclose(fp);
	return dim;
}
