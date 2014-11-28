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
	char **hamdata;
	int **distance;
	int *plusinit, *conceninit;
	cluster *clusters;
	FILE* fp;
	int nobits,i,j;
	num = numberOfitems(data,flag);
	
	gethamdata(data,&hamdata,num);
	
	nobits = strlen(hamdata[0]);
	fp = fopen(output,"a+");
	double totdis;
	configuration c;
	num = numberOfitems(data,flag);
	c = setConfig(config,num);
	clusters = calloc(c.Clasters,sizeof(cluster));
	
	/**arxikopoiisi kai gemisma pinaka apostaseon*/
	if((distance = calloc(num,sizeof(int*))) == NULL){
		perror("1:");
		exit(2);
	}
		
    for (i=0; i < num; i++)
        distance[i] = NULL;
        
    for (i=0; i < num; i++){
       if((distance[i] = calloc(num,sizeof(int))) == NULL){
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
	
	/**Concentrate Initialization**/
	concint(&distance, &conceninit, num, c.Clasters);
	for(i=0;i<c.Clasters;i++)
		printf("medoid no %d has id %d\n",i, conceninit[i]);
	printf("\nplusplus\n");
	/**K-means++ Initialization**/
	plusplusham(&hamdata,&plusinit,num, c.Clasters,nobits);		
	for(i=0;i<c.Clasters;i++)
		printf("medoid no %d has id %d\n",i, plusinit[i]);
		
	for(i = 0;i<c.Clasters;i++){
		clusters[i].medid = plusinit[i];		
	//	clusters[i].medid = conceninit[i];
		clusters[i].sumdist = 0;
		clusters[i].idcount = 0;
	}
	
	
	do{

		assham(&clusters,&hamdata,c.Clasters,num,nobits);
		int sum =0;		
		for(i=0;i<c.Clasters;i++){
			printf("Cluster[%d] old medoid is object with itemid %d and distance%f\n", i, clusters[i].medid,clusters[i].sumdist);
			sum += clusters[i].sumdist;
		}
		printf("sum before is %d \n", sum);	
		//flag2 = alalloydham(&clusters,&hamdata,c.Clasters,num,nobits);
		//printf("s is %d\n",c.ClaransIterations);
		flag2 = claransham(&clusters,&hamdata,c.Clasters,num,c.ClaransIterations,c.ClaransFraction,nobits);
		sum = 0;
		for(i=0;i<c.Clasters;i++){
			printf("Cluster[%d] new medoid is object with itemid %d and distance%f\n", i, clusters[i].medid,clusters[i].sumdist);
			sum += clusters[i].sumdist;
		}
		printf("and sum after is %d \n", sum);	
	}while (flag2==1);
	totdis = silhouettes(&clusters,&distance,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,1,2,1,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	fclose(fp);
	return 0;
}
