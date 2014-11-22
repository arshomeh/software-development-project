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
	while( (c = fgetc( fp )) != '\n' )
	for(j = 0;j<num; j++){
		for(i = 0;i<num;i++){
			fscanf(fp,"%s",XXX);
			(*matdata)[j][i] = atoi(XXX);
		}
	}
	fclose(fp);
	return 0;
}
