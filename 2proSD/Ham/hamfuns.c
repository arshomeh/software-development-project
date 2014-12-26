#include "../headers.h"

int gethamdata(char* data,char *** hamdata,int num){
	char XXX[SIZEofBUFF];
	char binary[SIZE];
	//char line [SIZE*2];
	int i = 0;
	FILE* fp;
	fp = fopen(data,"r");
	(*hamdata)= malloc(num * sizeof(char*));
	fscanf(fp, "%s %s", XXX, XXX);
	while (i<num){//( fgets ( line, sizeof line, fp ) != NULL ) { /* read a line */
			fscanf(fp, "%s %s", XXX, binary); 
			(*hamdata)[i] =  malloc(SIZE * sizeof(char));
			strcpy((*hamdata)[i],binary);
			i++;
	}
	fclose(fp);
	return 0;
}

int hamdist(char* a, int nobits, char* b) {
    int num_mismatches = 0;
    while (nobits) {
		if (*a != *b)
            ++num_mismatches;

        --nobits;
        ++a;
        ++b;
    }
    return num_mismatches;
}
