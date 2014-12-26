#include "headers.h"

int matMain(char* data,char * config,char *output,int flag,int flagcomp){
	int num;
	int flag2;
	int flagi, flaga, flagu;
	double **matdata;
	int *plusinit, *conceninit;
	cluster *clusters;
	double totdis;
	configuration c;
	num = numberOfitems(data,flag);
	
	c = setConfig(config,num);
	clusters = calloc(c.Clasters,sizeof(cluster));
	
	printf("num is %d\n",num);
	getmatdata(data,&matdata,num);


	/**K-means++ Initialization**/
	flagi = plusplus(&matdata,NULL,NULL, &plusinit, num, c.Clasters,0,0,1);


	/**PAM Assignment - A la Lloyd's Update**/
	flag2 = 0;
	flagu = 1;
	clustinitialize(&clusters,&plusinit,c.Clasters);	
	do{
		flaga = pamass(&clusters,&matdata,NULL,NULL, num, c.Clasters,0,0,1);
		flag2 = alalloyd(&clusters,&matdata,NULL,NULL, num, c.Clasters,0,0,1);
	}while (flag2==1);
	totdis = silhouettes(&clusters,&matdata,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flaga,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	

	/**PAM Assignment - CLARANS Update*/
	flag2 = 0;
	flagu = 2;
	clustinitialize(&clusters,&plusinit,c.Clasters);
		flaga = pamass(&clusters,&matdata,NULL,NULL, num, c.Clasters,0,0,1);
		

		flag2 = clarans(&clusters,&matdata,NULL,NULL,c.Clasters,num,0,0,1,c.ClaransIterations,c.ClaransFraction);
		

		flaga = pamass(&clusters,&matdata,NULL,NULL, num, c.Clasters,0,0,1);
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
		flaga = pamass(&clusters,&matdata,NULL,NULL, num, c.Clasters,0,0,1);
		flag2 = alalloyd(&clusters,&matdata,NULL,NULL, num, c.Clasters,0,0,1);	
	}while (flag2==1);
	totdis = silhouettes(&clusters,&matdata,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);



	/**PAM Assignment - CLARANS Update**/
	flag2 = 0;
	flagu = 2;
	clustinitialize(&clusters,&conceninit,c.Clasters);
		flaga = pamass(&clusters,&matdata,NULL,NULL, num, c.Clasters,0,0,1);
		flag2 = clarans(&clusters,&matdata,NULL,NULL,c.Clasters,num,0,0,1,c.ClaransIterations,c.ClaransFraction);
		flaga = pamass(&clusters,&matdata,NULL,NULL, num, c.Clasters,0,0,1);
	totdis = silhouettes(&clusters,&matdata,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	return 0;
}



