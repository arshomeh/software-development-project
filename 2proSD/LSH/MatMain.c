#include "headers.h"

void MatMain(char * Data,int k, int L){
	FILE *fp;//,*out;
	char c;
	int i,j,ts;
	int xx1,xx2,x1x2,xfort;
	double tmed;
	char XXX[BIG];
	printf("we are in Matrix space with data %s\n",Data);
	MK = k;
	fp = fopen(Data,"r");
	if(fp == NULL){
		printf("Can not open data file\n");
		return;
	}

	TableSize = (int)pow(2,(double)k);
	Lmat = (matg *)calloc(L, sizeof (matg));
	while( (c = fgetc( fp )) != EOF ){
        if( c == '\n' ) 
			Number++;//ypologizoume to n
	}
	Number = Number-2;
	rewind(fp);
	fscanf(fp, "%s %s",XXX,XXX);
	fscanf(fp,"%s",XXX);
	fscanf(fp,"%s",XXX);
	
	
	/*desmeuseis pinakwn */
	if((pinakasx1x2 = malloc(L* sizeof *pinakasx1x2)) == NULL)
		return;
    for (i=0; i < L; ++i)
       if(( pinakasx1x2[i] = malloc(k * sizeof *pinakasx1x2[i]))== NULL)
			return;
    for (i=0; i < L; ++i)
        for (j=0; j < k; ++j)
           if((pinakasx1x2[i][j] = malloc(2 * sizeof *pinakasx1x2[i][j])) == NULL)
			return;
       for (i=0; i < L; ++i)
        for (j=0; j < k; ++j)
           for(ts=0; ts<2;ts++)
			 pinakasx1x2[i][j][ts] = 0;    
			 
	//////////////////
	if((pinakast = malloc(L* sizeof *pinakast)) == NULL)
		return;
    for (i=0; i < L; ++i)
        pinakast[i] = NULL;
    for (i=0; i < L; ++i)
       if(( pinakast[i] = malloc(k * sizeof *pinakast[i])) == NULL)
		return;
		
	//////////////////
	if((apostaseis = malloc(Number* sizeof *apostaseis)) == NULL)
		return;
    for (i=0; i < Number; ++i)
        apostaseis[i] = NULL;
    for (i=0; i < Number; ++i)
        if((apostaseis[i] = malloc(Number * sizeof *apostaseis[i])) == NULL)
			return;
			
	/*pairnei tis apostaseis apo to arxeio kai tis vazei ston pinaka */
	for(j = 0;j<Number; j++){
		for(i = 0;i<Number;i++){
			fscanf(fp,"%s",XXX);
			apostaseis[j][i] = atoi(XXX);
		}
	}
	
	/* edo apothikeuei tis 3ades ton x1,x2 kai t poy einai anagkaia gia tis hash functions */
		/*ginodai simfona me tin theoria */
		/*o pinakas[x1][x2][2] exei tis 2ades (int) kai o pinakast[med] exei ta adistoixa median */
	for(i=0;i<L;i++){
		for(j=0;j<k;j++){			
			pinakasx1x2[i][j][0] = getUniformInt(0,Number);
			do{
				pinakasx1x2[i][j][1] = getUniformInt(0, Number);	
			} while(pinakasx1x2[i][j][0]==pinakasx1x2[i][j][1]);
			do{
				xfort = getUniformInt(0,Number);
			}while((xfort==pinakasx1x2[i][j][1])||(xfort==pinakasx1x2[i][j][0]));
			x1x2 = apostaseis[pinakasx1x2[i][j][0]][pinakasx1x2[i][j][1]];
			xx1 = apostaseis[pinakasx1x2[i][j][0]][xfort];
			xx2 = apostaseis[pinakasx1x2[i][j][1]][xfort];
			tmed = (pow(xx1,2) +pow(xx2,2) - pow(x1x2,2)) / (2*x1x2);
			pinakast[i][j] = tmed;
		}
	}	
	/*Ginetai o katakermatismos gia kathe stoixeio  kai benei se L buckets*/
	Lmat = (matg *)calloc(L, sizeof (matg));
	for( i = 0; i < L; i++){    //gia kathe g pernoume tixaious k arithmous
		Lmat[i].hash = NULL;
		Lmat[i].hash = (mathash *)calloc(TableSize, sizeof (mathash));
		Lmat[i].gid = i;
		loadMaHash(&Lmat[i]);
	}
	return;
}
	

int Matquery(int *query,int k, int L,int rad){	
	
	int i;
	int Coun;
	int numofitems;
	Coun = 0;
	numofitems = 0;
	for(i = 0; i < L; i++){					//briskei ton arithmo poy einai sta idia buckets
		numofitems = FindNearN(query,&Lmat[i]);
		Coun = Coun + numofitems; 
	}
	nearmat = malloc(Coun* sizeof (int));
	for(i = 0;i<Coun;i++)
		nearmat[i] = -1;				
	MatCounter = 0;
	for(i = 0; i < L; i++){					//gemizei ton pinaka me toys kontinos, me elegxo omoiotitas
		searchMaHash(query,&Lmat[i],Coun);
	}
	//BestMaRad(query,Coun,rad);			//vriskei ton R-near geitones
	return Coun;		
	
}








