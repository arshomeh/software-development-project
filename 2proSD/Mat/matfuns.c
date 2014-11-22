#include "../headers.h"

int getmatdata(char* data,int ***matdata,int num){
	FILE* fp;
	int i,j;
	char c;
	char XXX[SIZEofBUFF];
	fp = fopen(data,"r");
	(*matdata) = malloc(num* sizeof(int*));
	fscanf(fp, "%s %s",XXX,XXX);
	fscanf(fp,"%s",XXX);
	while( (c = fgetc( fp )) != '\n' &&  (c != '\t')){
		//do nothing
	}
	for(j = 0;j<num; j++)
		(*matdata)[j] = malloc(num* sizeof(int));
	
	int a;
	for(j = 0;j<num; j++){
		for(i = 0;i<num;i++){
			fscanf(fp,"%d",&a);
			(*matdata)[j][i] = a;
		}		
	}
	fclose(fp);
	return 0;
}
