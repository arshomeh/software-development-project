#include "headers.h"

int matMain(char* data,char * config,char *output,int flag,int flagcomp){
	int num,i,j;
	FILE* fp;
	int flag2= 0;
	int **matdata;
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
	/**Concentrate Initialization**/
	//concint(&matdata, &conceninit, num, c.Clasters);
	
	
	/**K-means++ Initialization**/
	plusplusmat(&matdata, &plusinit, num, c.Clasters);
	clustinitialize(&clusters,&plusinit,c.Clasters);	
	/**clarans update**/
	do{
		assmat(&clusters,&matdata,c.Clasters,num);
		/*int sum =0;		
		for(i=0;i<c.Clasters;i++){
			printf("Cluster[%d] old medoid is object with itemid %d and distance%f\n", i, clusters[i].medid,clusters[i].sumdist);
			sum += clusters[i].sumdist;
		}
		printf("sum before is %d \n", sum);	*/	
		//flag2 = alalloydmat(&clusters,&matdata,c.Clasters,num);
		flag2 = claransmat(&clusters,&matdata,c.Clasters,num,c.ClaransIterations,c.ClaransFraction);
		/*sum = 0;
		for(i=0;i<c.Clasters;i++){
			//printf("Cluster[%d] new medoid is object with itemid %d and distance%f\n", i, clusters[i].medid,clusters[i].sumdist);
			//sum += clusters[i].sumdist;
		}
		printf("and sum after is %d \n", sum);*/	
	}while (flag2==1);
	totdis = silhouettes(&clusters,&matdata,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,1,2,1,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	
	/**alalloyd update**/
	flag2 = 0;
	clustinitialize(&clusters,&plusinit,c.Clasters);
	do{
		assmat(&clusters,&matdata,c.Clasters,num);
		flag2 = alalloydmat(&clusters,&matdata,c.Clasters,num);	
	}while (flag2==1);
	totdis = silhouettes(&clusters,&matdata,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,1,2,1,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	
	
	/**Concentrate Initialization**/
	concint(&matdata, &conceninit, num, c.Clasters);
	flag2 = 0;
	clustinitialize(&clusters,&conceninit,c.Clasters);
	
	/**alalloyd update**/
	do{
		assmat(&clusters,&matdata,c.Clasters,num);
		flag2 = alalloydmat(&clusters,&matdata,c.Clasters,num);	
	}while (flag2==1);
	totdis = silhouettes(&clusters,&matdata,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,1,2,1,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);


	/**clarans update**/
	flag2 = 0;
	clustinitialize(&clusters,&conceninit,c.Clasters);
	do{
		assmat(&clusters,&matdata,c.Clasters,num);
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
	totdis = silhouettes(&clusters,&matdata,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,1,2,1,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	
	flag2 = 0;
	fclose(fp);
	return 0;
}
