#include "headers.h"

/*int hamdist(char* a, int nobits, char* b) {
    int num_mismatches = 0;
    while (nobits) {
        if (*a != *b)
            ++num_mismatches;

        --nobits;
        ++a;
        ++b;
    }
    return num_mismatches;
}*/

int hamMain(char* data,char * config,char *output,int flag){
	int num;
	char **hamdata;
	short int **distance;
	FILE* fp;
	int nobits,i,j;
	num = numberOfitems(data,flag);
	gethamdata(data,&hamdata,num);
	nobits = strlen(hamdata[0]);
	fp = fopen(output,"w");
	/*int j;
	 for(j = 0;j <num;j++){
		fprintf(fp,"%s\n",hamdata[j]);
	}
	printf("\n");*/
	if((distance = calloc(num,sizeof(short int*))) == NULL){
		perror("1:");
		exit(2);
	}
    for (i=0; i < num; i++)
        distance[i] = NULL;
    for (i=0; i < num; i++){
       if((distance[i] = calloc(num,sizeof(short int))) == NULL){
				printf("i is %d\n",i);
			perror("2:");
			exit(2);
		}
	}
	printf("num is %d\n",num);
	//printf("%s\n%d\n",hamdata[1],nobits);
	for(i = 0;i<num;i++){
		distance[i][i] = 0;
		for(j = i+1;j<num;j++){
			distance[i][j] = (short int)hamdist(hamdata[i],nobits,hamdata[j]);
			distance[j][i] = distance[i][j];
		}
	}
	/*for(i = 0;i<num;i++){
		fprintf(fp,"item%d || ",i);
		for(j = 0;j<num;j++){
			fprintf(fp,"%d ",distance[i][j]);
		}
		fprintf(fp,"\n");
	}*/
	fclose(fp);
	return 0;
}
