#include "../headers.h"

int gethamdata(char* data,char *** hamdata,int num){
	char XXX[SIZEofBUFF];
	char binary[SIZE];
	char line [SIZE*2];
	int i = 0;
	FILE* fp;
	fp = fopen(data,"r");
	(*hamdata)= malloc(num * sizeof(char *));
	
	while ( fgets ( line, sizeof line, fp ) != NULL ) { /* read a line */
			fscanf(fp, "%s %s", XXX, binary); 
			(*hamdata)[i] =  malloc(SIZE * sizeof(char *));
			strcpy((*hamdata)[i],binary);
			i++;
	}
	fclose(fp);
	return 0;
}
