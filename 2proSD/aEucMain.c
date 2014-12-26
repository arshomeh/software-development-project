#include "headers.h"

int eucMain(char* data,char * config,char *output,int flag,int flagcomp){
	int num,dim;
	double totdis;
	int flagi, flaga, flagu,flag2;
	double **eucdata;
	double **distance;
	int *plusinit, *conceninit;
	configuration c;
	cluster *clusters;
	num = numberOfitems(data,flag);
	printf("num is %d\n",num);
	dim = getdim(data);
	printf("dim is %d\n",dim);
	
	c = setConfig(config,num);
	clusters = calloc(c.Clasters,sizeof(cluster));
	
	geteucdata(data,&eucdata,num,dim);
	int i,j;
	
	distance = malloc(num* sizeof(double*));
	for(j = 0;j<num; j++)
		distance[j] = malloc(num* sizeof(double));
			
	for(i = 0;i<num;i++){
		distance[i][i] = 0;
		for(j = i+1;j<num;j++){
			distance[i][j] = compEucDist(eucdata[i],eucdata[j],dim);
			distance[j][i] = distance[i][j];
		}
	}
	

	/**K-means++ Initialization**/
	flagi = plusplus(NULL,&eucdata,NULL, &plusinit, num, c.Clasters,0,dim,2);


	/**PAM Assignment - A la Lloyd's Update**/
	flag2 = 0;
	flagu = 1;
	clustinitialize(&clusters,&plusinit,c.Clasters);	
	do{
		flaga = pamass(&clusters,NULL,&eucdata,NULL, num, c.Clasters,0,dim,2);
		flag2 = alalloyd(&clusters,NULL,&eucdata,NULL, num, c.Clasters,0,dim,2);
	}while (flag2==1);
	totdis = silhouettes(&clusters,&distance,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flaga,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	
	/**PAM Assignment - CLARANS Update*/
	flag2 = 0;
	flagu = 2;
	clustinitialize(&clusters,&plusinit,c.Clasters);
		flaga = pamass(&clusters,NULL,&eucdata,NULL, num, c.Clasters,0,dim,2);
		flag2 = clarans(&clusters,NULL,&eucdata,NULL,c.Clasters,num,0,dim,2,c.ClaransIterations,c.ClaransFraction);
		flaga = pamass(&clusters,NULL,&eucdata,NULL, num, c.Clasters,0,dim,2);
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
		flaga = pamass(&clusters,NULL,&eucdata,NULL, num, c.Clasters,0,dim,2);
		flag2 = alalloyd(&clusters,NULL,&eucdata,NULL, num, c.Clasters,0,dim,2);
	}while (flag2==1);
	totdis = silhouettes(&clusters,&distance,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);


	/**PAM Assignment - CLARANS Update**/
	flag2 = 0;
	flagu = 2;
	clustinitialize(&clusters,&conceninit,c.Clasters);
		flaga = pamass(&clusters,NULL,&eucdata,NULL, num, c.Clasters,0,dim,2);
		flag2 = clarans(&clusters,NULL,&eucdata,NULL,c.Clasters,num,0,dim,2,c.ClaransIterations,c.ClaransFraction);
		flaga = pamass(&clusters,NULL,&eucdata,NULL, num, c.Clasters,0,dim,2);
	totdis = silhouettes(&clusters,&distance,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);

	return 0;
}
