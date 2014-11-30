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

int hamMain(char* data,char * config,char *output,int flag,int flagcomp){
	int num,flag2 = 0;
	int flagi, flaga, flagu;
	char **hamdata;
	double totdis;
	double **distance;
	int *plusinit, *conceninit;
	cluster *clusters;
	FILE* fp;
	int nobits,i,j;
	num = numberOfitems(data,flag);
	printf("nomber %d\n",num);
	gethamdata(data,&hamdata,num);
	nobits = strlen(hamdata[0]);
	printf("nomber of bits %d\n",nobits);
	
	fp = fopen(output,"a+");
	
	configuration c;
	num = numberOfitems(data,flag);
	c = setConfig(config,num);
	clusters = calloc(c.Clasters,sizeof(cluster));
	
	/**arxikopoiisi kai gemisma pinaka apostaseon*/
	if((distance = calloc(num,sizeof(double*))) == NULL){
		perror("1:");
		exit(2);
	}
		
    for (i=0; i < num; i++)
        distance[i] = NULL;
        
    for (i=0; i < num; i++){
       if((distance[i] = calloc(num,sizeof(double))) == NULL){
			perror("2:");
			exit(2);
		}
	}

	for(i = 0;i<num;i++){
		distance[i][i] = 0;
		for(j = i+1;j<num;j++){
			distance[i][j] = hamdist(hamdata[i],nobits,hamdata[j]);
			distance[j][i] = distance[i][j];
		}
	}
	/**K-means++ Initialization**/
	flagi = plusplusham(&hamdata, &plusinit, num, c.Clasters,nobits);
	/**PAM Assignment - A la Lloyd's Update**/
	flag2 = 0;
	flagu = 1;
	clustinitialize(&clusters,&plusinit,c.Clasters);	
	do{
		flaga = assham(&clusters,&hamdata,c.Clasters,num,nobits);
		flag2 = alalloydham(&clusters,&hamdata,c.Clasters,num,nobits);
	}while (flag2==1);
	totdis = silhouettes(&clusters,&distance,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flaga,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	
	/**PAM Assignment - CLARANS Update*/
	flag2 = 0;
	flagu = 2;
	clustinitialize(&clusters,&plusinit,c.Clasters);
	do{
		flaga = assham(&clusters,&hamdata,c.Clasters,num,nobits);
		flag2 = claransham(&clusters,&hamdata,c.Clasters,num,c.ClaransIterations,c.ClaransFraction,nobits);
	}while (flag2==1);
	totdis = silhouettes(&clusters,&distance,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	
	
	/**Concentrate Initialization**/
	flagi = concint(&distance, &conceninit, num, c.Clasters);
	
	/**PAM Assignment - A la Lloyd's Update**/
	flag2 = 0;
	flagu = 1;	
	clustinitialize(&clusters,&conceninit,c.Clasters);	
	do{
		flaga = assham(&clusters,&hamdata,c.Clasters,num,nobits);
		flag2 = alalloydham(&clusters,&hamdata,c.Clasters,num,nobits);	
	}while (flag2==1);
	totdis = silhouettes(&clusters,&distance,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);


	/**PAM Assignment - CLARANS Update**/
	flag2 = 0;
	flagu = 2;
	clustinitialize(&clusters,&conceninit,c.Clasters);
	do{
		flaga =assham(&clusters,&hamdata,c.Clasters,num,nobits);
		flag2 = claransham(&clusters,&hamdata,c.Clasters,num,c.ClaransIterations,c.ClaransFraction,nobits);
	}while (flag2==1);
	totdis = silhouettes(&clusters,&distance,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	
	fclose(fp);
	return 0;
}
