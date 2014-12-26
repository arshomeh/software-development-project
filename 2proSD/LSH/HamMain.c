#include "headers.h"


int HamMain(char * Data,int k, int L){
	int i,j,uni,ii,jj;
	printf("\nk is %d L is %d\n",k,L);
	printf("we are in hamming space with data %s\n",Data);
	char temp[k];
    K = (int)pow(2,(double)k);  						//K o arithmos ton buckets
	gtypeTable = (gtype *)calloc(L, sizeof (gtype));	// pinakas L pou exei g sinartiseis
	

	for( i = 0; i < L; i++){    
		/*dimiourgia ton bitstring gia tis hash functions */
		for(j = 0;j < k; j++){
			for (ii=1; ii<10; ii++){
				int ok=1;
				char pinakas[k];
				uni = getUniformInt(0,63);		
				for(jj=0; jj<ii; jj++){
					if(pinakas[jj]==uni){
						ii--;
						ok = 0;
						break;				
					}
				}
				if (ok==1){
					pinakas[ii] = uni;
				}
			}
			uni = getUniformInt(0,SIZE-2);
			sprintf(&temp[j], "%d", uni); // pernei tixaia k psifia
		}
		gtypeTable[i].digi = NULL;
		gtypeTable[i].hash = NULL;
		
		gtypeTable[i].digi = (char *)calloc(k+1, sizeof (char));
		gtypeTable[i].hash = (hashnode *)calloc((int)pow(2,(double)k), sizeof (hashnode));
		
		strcpy(gtypeTable[i].digi,temp);
		loadToHash(Data,&gtypeTable[i]);
	}
	return 0;
}
int Hamquery(char *binary,int k, int L,int rad){
	int Coun,N,i;
	/*periptosi poy iparxei radius kai dinetai query stin grammi entolwn */
	Coun = 0;
	for(i = 0; i < L; i++){							//metraei posa alla nodes iparxoyn sta L buckets me ayto
		N = searchInner(binary,&gtypeTable[i]);
		Coun = Coun + N; 
	}
	nearn = (hamnodeins *)calloc(Coun, sizeof (hamnodeins));
	for(i = 0;i<Coun;i++){							
		nearn[i].id = -1;
		strcpy(nearn[i].binary,"NULL");
	}
	HamCount = 0;													
	for(i = 0; i < L; i++){							//edw bainoyn ola poy einai sta idia buckets, me elegxo omoiotitas
		searchInHash(binary,&gtypeTable[i],Coun);
	}		
	Bestrad(binary,Coun,rad);					//vriskei ta R-near
	free(nearn);
	nearn = NULL;
	return 0;
}
