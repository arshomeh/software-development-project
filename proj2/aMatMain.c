#include "headers.h"

int matMain(char* data,char * config,char *output,int flag){
	int num,i,j;
	FILE* fp;
	int flag2= 0;
	int **matdata;
	int *plusinit, *conceninit;
	cluster *clusters;
	configuration c;
	
	fp = fopen(output,"w");
	num = numberOfitems(data,flag);
	
	c = setConfig(config,num);
	clusters = calloc(c.Clasters,sizeof(cluster));
	
	printf("num is %d\n",num);
	getmatdata(data,&matdata,num);
	concint(&matdata, &conceninit, num, c.Clasters);
	//for(i=0;i<c.Clasters;i++)
		//printf("conceninit[%d] is  %d\n", i,conceninit[i]);
	plusplusint(&matdata, &plusinit, num, c.Clasters);
	//for(i=0;i<c.Clasters;i++)
		//printf("plusinit[%d] is  %d\n", i,plusinit[i]);
	
	for(i = 0;i<c.Clasters;i++){
		clusters[i].medid = plusinit[i];		
		//clusters[i].medid = conceninit[i];
		clusters[i].sumdist = 0;
		clusters[i].idcount = 0;
	}
	do{
		assmat(&clusters,&matdata,c.Clasters,num);
		for(i=0;i<c.Clasters;i++)
			printf("Cluster[%d] old medoid is object with itemid %d and distance%f\n", i, clusters[i].medid,clusters[i].sumdist);		
		flag2 = alalloydmat(&clusters,&matdata,c.Clasters,num);
		for(i=0;i<c.Clasters;i++)
			printf("Cluster[%d] new medoid is object with itemid %d and distance%f\n", i, clusters[i].medid,clusters[i].sumdist);
	}while (flag2==1);
	flag2 = claransmat(&clusters,&matdata,c.Clasters,num,c.ClaransIterations,c.ClaransFraction);
	fclose(fp);
	return 0;
}
