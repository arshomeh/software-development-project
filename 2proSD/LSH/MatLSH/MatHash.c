#include "../headers.h"

matg *Lmat = NULL;
int *nearmat = NULL;
int TableSize = 0;
int Number = 0;
int MK = 0;
int BestMa = -1;
int MatCounter = 0;
int ***pinakasx1x2 = NULL;	//[L][K][2]; //pinakas gia x1x2 toy kathe h
double **pinakast = NULL;	//[L][K]; //pinakas gia tmed toy kathe h
int **apostaseis = NULL;	//[N][N]; //pinakas apostaseon. ego ton dimioyrgo esi tha ton diabazeis


/**dimiourgia komvou**/
matnode * createMatNode(int id){
	matnode * newnode;
	newnode = (matnode *)malloc(sizeof(matnode));
	newnode->id = id;
	newnode->next = NULL;
	return newnode;
}


/**eisagogi sto hash table **/
void insertMaHash(int item,int *temp,matg * gtable){

	int hashIndex = 0;
	hashIndex = Mathashfun(temp,gtable);

	matnode *newnode =  createMatNode(item);	
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

/**provoli tis domis **/
void Madisplay(matg * gtable) {
	matnode *myNode;
	int i;
	for (i = 0; i < TableSize; i++) {
		if (gtable->hash[i].count == 0)
			continue;
		myNode = gtable->hash[i].head;
		if (!myNode)
			continue;
		while (myNode != NULL) {	
			printf("id is %d\n",myNode->id);
			myNode = myNode->next;
			
		}
	}
	return;
}

void loadMaHash(matg * gtable){
	int *temp;
	int i,j;
	temp = malloc(Number*sizeof(int));
	for(i = 0;i<Number;i++){
		for(j =0;j<Number;j++){
			temp[j] = apostaseis[i][j];
		}
		insertMaHash(i,temp,gtable);
	}
	free(temp);
}


/**katastrofi tis domis**/
void destroyMa(matg * gtable){
	matnode *temp,*myNode;
	int i;
	for (i = 0;i < TableSize ;i++){
		myNode = gtable->hash[i].head;
		while (myNode != NULL){
			gtable->hash[i].head = myNode->next;
			temp = myNode;
			myNode = myNode->next;
			free(temp);
		}
	}

}


/**sinartisi katakermatismoy **/
int Mathashfun(int *item,matg * gtable){
	int index = 0;
	int i,j;
	char c;
	char *ptr;
	char bitstring[MK+1];
	double x1x2,htest;
	double xx1;
	double xx2;
	bitstring[MK] = '\0';
	i = gtable->gid;
	for(j=0;j< MK;j++){
		x1x2 = apostaseis[pinakasx1x2[i][j][0]][pinakasx1x2[i][j][1]];
		xx1 = item[pinakasx1x2[i][j][0]];
		xx2 = item[pinakasx1x2[i][j][1]];
		htest= (pow(xx1,2) +pow(xx2,2) -pow(x1x2,2)) / (2*x1x2);
		if (htest > pinakast[i][j])
			c = '0';
		else	
			c = '1';
		bitstring[j] = c;	
	}
	index = strtol(bitstring, &ptr, 2);
	return index;	
}


/**euresi arithmou sto idio bucket **/
int FindNearN(int *item,matg * gtable){
	int hashIndex;
	int N = 0;
	matnode *myNode;
	hashIndex = Mathashfun(item,gtable);
	myNode = gtable->hash[hashIndex].head;
	if (!myNode) {
		return N;
	}
	while (myNode != NULL){
		N++;
		myNode = myNode->next;
	}
	return N;
}

/**anazitisi se bucket**/
void searchMaHash(int *item,matg * gtable,int Coun){
	int hashIndex,j;
	int flag = 0;
	matnode *myNode;
	hashIndex = Mathashfun(item,gtable);
	myNode = gtable->hash[hashIndex].head;
	if (!myNode) {
		return;
	}
	while (myNode != NULL) {
			for(j = 0;j<Coun;j++){
				flag = 0;
				if(nearmat[j] == myNode->id){
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				nearmat[MatCounter]= myNode->id;
			}
		MatCounter++;
		myNode = myNode->next;
	}
	return;
}



/**ektiposi kontinoteron se range **/
int BestMaRad(int *item,int Coun,int radius){
	int i;
	printf("R-near with radius %d\n",radius);
	for(i = 0;i<Coun;i++){
		if(nearmat[i] != -1){
			if(item[nearmat[i]] < radius){
				printf("ItemId %d \n",nearmat[i]+1);
			}
		}
	}
	return Coun;
}


