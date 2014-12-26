#include "headers.h"


int hamMain(char* data,char * config,char *output,int flag,int flagcomp){
	int num,flag2 = 0;
	int flagi, flaga, flagu;
	char **hamdata;
	double totdis;
	double **distance;
	int *plusinit, *conceninit;
	cluster *clusters;
	int nobits,i,j;
	num = numberOfitems(data,flag);
	printf("number %d\n",num);
	gethamdata(data,&hamdata,num);
	nobits = strlen(hamdata[0]);
	printf("number of bits %d\n",nobits);
	
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
	flagi = plusplus(NULL,NULL,&hamdata, &plusinit, num, c.Clasters,nobits,0,3);


	/**PAM Assignment - A la Lloyd's Update**/
	flag2 = 0;
	flagu = 1;
	clustinitialize(&clusters,&plusinit,c.Clasters);	
	do{
		flaga = pamass(&clusters,NULL,NULL,&hamdata, num, c.Clasters,nobits,0,3);
		flag2 = alalloyd(&clusters,NULL,NULL,&hamdata, num, c.Clasters,nobits,0,3);
	}while (flag2==1);
	totdis = silhouettes(&clusters,&distance,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flaga,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	

	/**PAM Assignment - CLARANS Update*/
	flag2 = 0;
	flagu = 2;
	clustinitialize(&clusters,&plusinit,c.Clasters);
	flaga = pamass(&clusters,NULL,NULL,&hamdata, num, c.Clasters,nobits,0,3);
	flag2 = clarans(&clusters,NULL,NULL,&hamdata,c.Clasters,num,nobits,0,3,c.ClaransIterations,c.ClaransFraction);
	flaga = pamass(&clusters,NULL,NULL,&hamdata, num, c.Clasters,nobits,0,3);
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
		flaga = pamass(&clusters,NULL,NULL,&hamdata, num, c.Clasters,nobits,0,3);
		flag2 = alalloyd(&clusters,NULL,NULL,&hamdata, num, c.Clasters,nobits,0,3);
	}while (flag2==1);
	totdis = silhouettes(&clusters,&distance,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);

	/**PAM Assignment - CLARANS Update**/
	flag2 = 0;
	flagu = 2;
	clustinitialize(&clusters,&conceninit,c.Clasters);
		flaga = pamass(&clusters,NULL,NULL,&hamdata, num, c.Clasters,nobits,0,3);
		flag2 = clarans(&clusters,NULL,NULL,&hamdata,c.Clasters,num,nobits,0,3,c.ClaransIterations,c.ClaransFraction);
		flaga = pamass(&clusters,NULL,NULL,&hamdata, num, c.Clasters,nobits,0,3);
	totdis = silhouettes(&clusters,&distance,c.Clasters, output);
	printclusters(&clusters,flagcomp,output,flagi,flaga,flagu,c.Clasters,200.00,totdis);
	freecluster(&clusters,c.Clasters);
	return 0;
}
