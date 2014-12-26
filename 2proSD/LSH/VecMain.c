#include "headers.h"

int VecMain(char * Data,int k,int L){
	FILE *infile;
	//ins = fopen("insert.txt","w");
	int dim = 0;
	int c,z,i,j,N = 0;
	char XXX[SIZEEU];
	char type[SIZEEU];
	printf("We are in Vector space.\n");
	infile = fopen(Data,"r");
	if(infile == NULL){
		printf("Can not open data file %s\n",Data);
		return 0;
	}
	EK = k;
	R  = (int *)calloc(EK, sizeof (int));
	/*arxikopoioisi Ri gia sinartiseis phi*/
	for(i = 0;i < k ;i++){
		R[i] = rand();
	}
	fscanf(infile, "%s %s",XXX,type);
	fscanf(infile, "%s %s",XXX,type);
	fscanf(infile, "%s %s",XXX,type);
	while(c != '\n'){
		if(c == '\t' || c == ' ')
			dim++;
		c = getc(infile);
	}
	/*******Ipologismos plithous***********/
	rewind(infile);
	while( (c = fgetc( infile )) != EOF ){
        if( c == '\n' ) 
			N++;//ypologizoume to n
	}
	rewind(infile);
	/************************************/
	N = N-2;
	elements = N;
	EK = k;
	DIM = dim + 1;
	LTable = (geuc *)calloc(L, sizeof (geuc));
	for(i = 0; i< L;i++){
		//printf("%d\n",L);
		LTable[i].Hfun = NULL;
		LTable[i].hash = NULL;
		LTable[i].Hfun = (heuc *)calloc(k, sizeof (heuc));
		LTable[i].hash = (euchash *)calloc(N/NDIV, sizeof (euchash));
		/* dianismata v gia tin sinartisi katakermatismou */
		for(j =0 ;j< k ;j++){
			LTable[i].Hfun[j].cordinate = (double *)calloc(DIM, sizeof (double));
			for(z = 0;z< DIM;z++){
				LTable[i].Hfun[j].cordinate[z] = getNormalDouble();
			}
			LTable[i].Hfun[j].T = getUniformInt(0,W-1);
		}
		loadEuHash(Data,&LTable[i]);		
	}
	return 0;
}
	/**************************************/
int Eucquery(double *query,int k, int L,int rad){
	tempnode temp;
	int j;
	int Coun = 0;
	int NN;
	/**se peripotsi poy mas dinetai range **/
	temp.cordinate = (double *)calloc(DIM, sizeof (double));
	temp.id = 0;
	for(j = 0;j < DIM; j++){				//diavasma ton sintetagmenon
		temp.cordinate[j] = query[j];
	}
	for(j = 0; j < L; j++){					//metrima stoixeion sta antistoixa buckets
		NN = searchEuin(&temp,&LTable[j]);
		Coun = Coun + NN; 
	}
	
	eunear = (tempnode *)calloc(Coun, sizeof (tempnode));
	int jj;
	for(j = 0;j<Coun;j++){
		eunear[j].id = -1;
		eunear[j].fid = -1;
		eunear[j].cordinate = (double *)calloc(DIM, sizeof (double));
		for(jj = 0 ;jj < DIM;jj++){
			eunear[j].cordinate[jj] = 0;
		}
	}
	EUcounter = 0;
	for(j = 0; j < L; j++){					//vazei ston pinaka tous kontinoys me elegxo omoiotitas
		searchEuHash(&temp,&LTable[j],Coun);
	}
	BestEUrad(&temp,Coun,rad);			//vriskei toys Range kodinous
	for(j = 0;j<Coun;j++){
		free(eunear[j].cordinate);
	}
	free(eunear);
	free(temp.cordinate);
	return Coun;			
}
