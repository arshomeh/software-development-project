#include "headers.h"

int matMain(char* data,char * config,char *output,int flag,int flagcomp){
	int num;
	//int i,j;
	FILE* fp;
	int flag2;
	int flagi, flaga, flagu;
	double **matdata;
	int *plusinit, *conceninit;
	cluster *clusters;
	double totdis;
	configuration c;
	fp = fopen(output,"w");
	num = numberOfitems(data,flag);
	
	c = setConfig(config,num);
	clusters = calloc(c.Clasters,sizeof(cluster));
	
	printf("num is %d\n",num);
	getmatdata(data,&matdata,num);


	/**K-means++ Initialization**/
	flagi = plusplusmat(&matdata, &plusinit, num, c.Clasters);

	/**PAM Assignment - A la Lloyd's Update**/
	flag2 = 0;
	flagu = 1;
	clustinitialize(&clusters,&plusinit,c.Clasters);	
	do{
		flaga = assmat(&clusters,&matdata,c.Clasters,num);
		flag2 = alalloydmat(&clusters,&matdata,c.Clasters,num);
	}while (flag2==1);
	totdis = silhouettes(&clusters,&matdata,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flaga,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	
	/**PAM Assignment - CLARANS Update*/
	flag2 = 0;
	flagu = 2;
	clustinitialize(&clusters,&plusinit,c.Clasters);
	do{
		flaga = assmat(&clusters,&matdata,c.Clasters,num);
		flag2 = claransmat(&clusters,&matdata,c.Clasters,num,c.ClaransIterations,c.ClaransFraction);
	}while (flag2==1);
	totdis = silhouettes(&clusters,&matdata,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	
	
	/**Concentrate Initialization**/
	flagi = concint(&matdata, &conceninit, num, c.Clasters);
	
	/**PAM Assignment - A la Lloyd's Update**/
	flag2 = 0;
	flagu = 1;	
	clustinitialize(&clusters,&conceninit,c.Clasters);	
	do{
		flaga = assmat(&clusters,&matdata,c.Clasters,num);
		flag2 = alalloydmat(&clusters,&matdata,c.Clasters,num);	
	}while (flag2==1);
	totdis = silhouettes(&clusters,&matdata,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);


	/**PAM Assignment - CLARANS Update**/
	flag2 = 0;
	flagu = 2;
	clustinitialize(&clusters,&conceninit,c.Clasters);
	do{
		flaga =assmat(&clusters,&matdata,c.Clasters,num);
		flag2 = claransmat(&clusters,&matdata,c.Clasters,num,c.ClaransIterations,c.ClaransFraction);
	}while (flag2==1);
	totdis = silhouettes(&clusters,&matdata,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	
	fclose(fp);
	return 0;
}


/*
 * 	do{
		flaga =assmat(&clusters,&matdata,c.Clasters,num);
		int sum =0;		
		for(i=0;i<c.Clasters;i++){
			printf("Cluster[%d] old medoid is object with itemid %d and distance%f\n", i, clusters[i].medid,clusters[i].sumdist);
			sum += clusters[i].sumdist;
		}
		printf("sum before is %d \n", sum);
		flag2 = claransmat(&clusters,&matdata,c.Clasters,num,c.ClaransIterations,c.ClaransFraction);
		sum = 0;
		for(i=0;i<c.Clasters;i++){
			printf("Cluster[%d] new medoid is object with itemid %d and distance%f\n", i, clusters[i].medid,clusters[i].sumdist);
			sum += clusters[i].sumdist;
		}
		printf("and sum after is %d \n", sum);
	}while (flag2==1);
 */
