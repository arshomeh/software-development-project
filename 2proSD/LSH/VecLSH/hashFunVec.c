/*Hash functions*/
#include "../headers.h"

geuc * LTable = NULL;  /////*gtypeTable = NULL;
int * R = NULL;
tempnode * EUBestn = NULL;
tempnode * eunear = NULL;
int elements = 0;
int EK = 0;
int DIM = 0;
int MM = 0;
int EUcounter = 0;
FILE * ins = NULL;

/*dimiourgia komvou*/
eucnode * createEuNode(double * item,int id,int fid){
	int i;
	eucnode *newnode;
	newnode = (eucnode *)malloc(sizeof(eucnode));
	newnode->id = id;
	newnode->fid = fid;
	newnode->cordinate = (double *)calloc(DIM, sizeof (double));
	for(i = 0 ;i < DIM;i++){
		newnode->cordinate[i] = item[i];
	}
	newnode->next = NULL;
	return newnode;
	
}

/*eisagogi ston pinaka katakermatismou */
void insertEuHash(tempnode * temp,geuc * gtable){
	int hashIndex;
	hashIndex = hashfun(temp, gtable);
	if(hashIndex < 0)
		hashIndex = hashIndex*(-1);
	//printf("temp fid %d\n",temp->fid);
	eucnode *newnode =  createEuNode(temp->cordinate,temp->id,temp->fid);	
	/* head of list for the bucket with index "hashIndex" */ 
	if (!gtable->hash[hashIndex].head) {
		gtable->hash[hashIndex].head = newnode;
		gtable->hash[hashIndex].count = 1;
		return;
	}
	/* adding new node to the list */
	newnode->next = (gtable->hash[hashIndex].head);
	/*
	* update the head of the list and no of
	* nodes in the current bucket
	*/
	gtable->hash[hashIndex].head = newnode;
	gtable->hash[hashIndex].count++;
		
	return;
}

/** provoli**/
void displayEU(geuc * gtable) {
	eucnode *myNode;
	int i;
	for (i = 0; i < elements/NDIV; i++) {
		if (gtable->hash[i].count == 0)
			continue;
		myNode = gtable->hash[i].head;
		if (!myNode)
			continue;
		while (myNode != NULL) {	
			myNode = myNode->next;
		}
	}
	return;
}

/**katastrofi tis vasis **/
void destroyEuc(geuc * gtable){
	//printf("des\n");
	eucnode *temp,*myNode;
	int i;
	for (i = 0;i < elements/NDIV ;i++){
		myNode = gtable->hash[i].head;
		while (myNode != NULL){
			
			gtable->hash[i].head = myNode->next;
			temp = myNode;
			myNode = myNode->next;						  
			//delete apo to inverted gia na doulepsei swsta
			free(temp->cordinate);
			free(temp);
		}
	}
	for(i = 0;i < EK ;i++){
		free(gtable->Hfun[i].cordinate);
	}
	free(gtable->Hfun);
	free(gtable->hash);
}


/**anazitisi sti vasi **/
void searchEuHash(tempnode *temp,geuc * gtable,int Coun){
	
	int hashIndex;
	int j;
	//int N = 0;
	int flag = 0;
	eucnode *myNode;
	hashIndex = hashfun(temp, gtable);
	if(hashIndex < 0)
		hashIndex = hashIndex*(-1);
	myNode = gtable->hash[hashIndex].head;
	while (myNode != NULL) {
		//if(temp->fid == myNode->fid){
			for(j = 0;j<Coun;j++){
				flag = 0;
				if(eunear[j].id == myNode->id){
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				eunear[EUcounter].id = myNode->id;
				eunear[EUcounter].fid = myNode->fid;
				for(j = 0; j<DIM;j++){
					eunear[EUcounter].cordinate[j] = myNode->cordinate[j];
				}
			}
			EUcounter++;
		//}
		myNode = myNode->next;
	}
	return;
	
}

/**sinartisi katakermatismou**/
int hashfun(tempnode * item, geuc * gtable ){
	int i,index;
	int x,fid = 0;
	for (i = 0; i < EK;i++){
		x = computehp(W,gtable->Hfun->T,item->cordinate,gtable->Hfun->cordinate);
		fid = (x*R[i] % M )+ fid;
	}
	index = fid % (elements/NDIV);
	//printf("fid is %d\n",fid);
	item->fid = fid;
	return index;
}

/**ipologismou ton h gia to katakermatismo **/
int computehp(double w, double t, double* p, double* v){
	int i,hp;
	double sum;
	for(i=0; i<DIM; i++)
		sum += p[i]*v[i];
	hp = (int)floor((sum+t)/w);	
	return hp;
}

/**fortoma tis vasis **/
void loadEuHash(char * name,geuc * gtable){
	FILE *fp;
	//FILE *out;
	int i,j;
	tempnode temp;
	char  strX[SIZE]; 
	fp = fopen(name, "r");
    if (fp == NULL){
		exit(0);
	}
	//out = fopen("temp.txt","w+");
	temp.id = -1;
	temp.cordinate = (double *)calloc(DIM, sizeof (double));
	fscanf(fp, "%s %s %s %s",strX,strX,strX,strX);
	for(i = 0;i < elements;i++){
		temp.id = i+1;
		fscanf(fp, "%s",strX);
		for(j = 0;j < DIM; j++){
			char kk[50];
			char *ptr;
			fscanf(fp,"%s",kk);
			temp.cordinate[j] = strtod(kk, &ptr);
		}
		insertEuHash(&temp,gtable);
	}
	//fclose(out);
	fclose(fp);
	free(temp.cordinate);
	return;
}

/////////////////////////////

/**anazitisi esoterika gia ton arithmo ton kontinoteron **/
int searchEuin(tempnode * temp,geuc * gtable) {
	int hashIndex;
	int N = 0;
	eucnode *myNode;
	hashIndex = hashfun(temp, gtable);
	if(hashIndex < 0)
		hashIndex = hashIndex*(-1);
		//printf("index %d\n",hashIndex);
	myNode = gtable->hash[hashIndex].head;
	if (!myNode) {
		return N;
	}
	while (myNode != NULL) {
		//if (temp->fid == myNode->fid){
			N++;
		//}
		myNode = myNode->next;
	}
	return N;
}


/**evresi kontinoterou **/ 
void BestEUnear(tempnode * temp,geuc * gtable){
	int hashIndex,j;
	eucnode *myNode;
	hashIndex = hashfun(temp, gtable);
	if(hashIndex < 0)
		hashIndex = hashIndex*(-1);
	myNode = gtable->hash[hashIndex].head;
	if (!myNode) {
		return;
	}
	while (myNode != NULL){
		if(EUBestn->id == -1){
			EUBestn->id = myNode->id;
			EUBestn->fid = myNode->fid;
			for(j = 0; j<DIM;j++){
					EUBestn->cordinate[j] = myNode->cordinate[j];
			}
			Distance = compEucDist(EUBestn->cordinate, temp->cordinate);
		}
		//if (temp->fid == myNode->fid){
			if(compEucDist(temp->cordinate, myNode->cordinate) < compEucDist(EUBestn->cordinate, temp->cordinate)){
				EUBestn->id = myNode->id;
				EUBestn->fid = myNode->fid;
				for(j = 0; j<DIM;j++){
						EUBestn->cordinate[j] = myNode->cordinate[j];
				}
				Distance = compEucDist(EUBestn->cordinate, temp->cordinate);
			}
		//}
		myNode = myNode->next;
	}
}


/**ektiposi gia range **/
void BestEUrad(tempnode * temp,int Coun,int radius){
	int i;
	printf("\nR-near with range %d\n",radius);
	for(i = 0;i<Coun;i++){
		if(eunear[i].id != -1){
			if(compEucDist(temp->cordinate, eunear[i].cordinate) < radius){
				printf("ItemId : %d \n",eunear[i].id);
			}
		}
	}
}

/**euresi NN me eksantlitiki anazitisi **/
void RealEUnear(tempnode * temp,geuc * gtable){
	
	int i,j,dis = -1;
	tempnode Realn;
	eucnode *myNode;
	Realn.id = -1;
	Realn.fid = -1;

	Realn.cordinate = (double *)calloc(DIM, sizeof (double));
	for(j = 0; j<DIM;j++){
		Realn.cordinate[j] = -1;
	}
	for (i = 0; i < elements/NDIV-1; i++) {
		if (gtable->hash[i].count == 0)
			continue;														
			
		myNode = gtable->hash[i].head;
		if (!myNode)
			continue;
			
		if(Realn.id == -1){
			Realn.id = myNode->id;
			Realn.fid = myNode->fid;
			for(j = 0; j<DIM;j++){
				Realn.cordinate[j] = myNode->cordinate[j];
			}
		}
		while (myNode != NULL) {	
			if(compEucDist(temp->cordinate, myNode->cordinate) < compEucDist(temp->cordinate,Realn.cordinate)){
				Realn.id = myNode->id;
				Realn.fid = myNode->fid;
				for(j = 0; j<DIM;j++){
					Realn.cordinate[j] = myNode->cordinate[j];
				}
				dis = compEucDist(temp->cordinate, Realn.cordinate);
			}
			myNode = myNode->next;
		}
	}
	fprintf(OUT,"NN with ES is ItemId %d with dis %d\n",Realn.id,dis);
	free(Realn.cordinate);
}

/**ipologismos eukleidia apostasis **/
double compEucDist(double* p, double *v){
	double sum = 0;
	double EucDist;
	int i = 0;
	for (i = 0;i<DIM;i++){
		sum += pow((p[i]-v[i]),2);
	}
	return EucDist = sqrt(sum);
}

