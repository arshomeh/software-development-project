/*Hash functions*/
#include "../headers.h"

//hashnode *hashTable = NULL;
gtype *gtypeTable = NULL;
hamnodeins *nearn = NULL;
hamnodeins *Bestn = NULL;
int Distance = 0;
int eleCount = 0;
int K = 0;
int HamCount = 0;


	/**dimiourgia komvou**/
hamnode * createNode(char *bits,int id){
	hamnode *newnode;
	newnode = (hamnode *)malloc(sizeof(hamnode));
	newnode->id = id;
	strcpy(newnode->binary,bits);
	newnode->next = NULL;
	return newnode;
}

	/**eisagogi sto hash table*/
void insertToHash(hamnodeins * temp,gtype * gtable){
	int k = sizeof(gtable->digi);
	char bits[k+1];
	int a;
	char c;
	char b;
	int hashIndex;
	char *ptr;
    int ret,j;
    for(j = 0;j < k; j++){
		strcpy(&c,&gtable->digi[j]);
		b = c;
		a=b -'0';
		bits[j] = temp->binary[a];
	}
	bits[j] = '\0';
	ret = strtol(bits, &ptr, 2);
	hashIndex = ret;
	hamnode *newnode =  createNode(temp->binary,temp->id);	
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

/**diagrafi apo to hashh**/
void deleteFromHash(char *binary,gtype * gtable){
		/* find the bucket using hash index */
	int hashIndex;
	int flag = 0;
	hamnode *temp, *myNode;
	char *ptr;
    int ret;
    int k = sizeof(gtable->digi);
	char bits[k+1];
	int a;
	char c;
	char b;
    int j;
    for(j = 0;j < k; j++){
		strcpy(&c,&gtable->digi[j]);
		b = c;
		a=b -'0';
		bits[j] = binary[a];
		
	}
	bits[j] = '\0';
	ret = strtol(bits, &ptr, 2);
	hashIndex = ret;
	
	/* get the list head from current bucket */
	myNode = gtable->hash[hashIndex].head;
	if (!myNode) {
		printf("Given data is not present in hash Table!!\n");
		return;
	}
	temp = myNode;
	while (myNode != NULL) {
		/* delete the node with given key */
		if (strcmp(myNode->binary, binary) == 0) {
			flag = 1;
			if (myNode == gtable->hash[hashIndex].head)
				gtable->hash[hashIndex].head = myNode->next;
			else
			temp->next = myNode->next;

			gtable->hash[hashIndex].count--;
			free(myNode);
			break;
		}
		temp = myNode;
		myNode = myNode->next;
	}
	if (flag)
		printf("Data deleted successfully from Hash Table\n");
	else
		printf("Given data is not present in hash Table!!!!\n");
	return;
}

/**anazitisi sto hash**/
void searchInHash(char *binary,gtype * gtable,int Coun) {
	
	int hashIndex;
	int flag = 0;
	hamnode *myNode;
	//int N = 0;
	char *ptr;
    int ret;
	int k = sizeof(gtable->digi);
	char bits[k+1];
	int a;
	char c;
	char b;
    int j;
    for(j = 0;j < k; j++){
		strcpy(&c,&gtable->digi[j]);
		b = c;
		a=b -'0';
		bits[j] = binary[a];
		
	}
	bits[j] = '\0';
	ret = strtol(bits, &ptr, 2);
	hashIndex = ret;
	myNode = gtable->hash[hashIndex].head;
	if (!myNode) {
		//printf("Search element unavailable in hash table\n");
		return;
	}
	while (myNode != NULL) {
			for(j = 0;j<Coun;j++){
				flag = 0;
				if(nearn[j].id == myNode->id){
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				nearn[HamCount].id = myNode->id;
				strcpy(nearn[HamCount].binary,myNode->binary);
			}
		HamCount++;
		myNode = myNode->next;
	}
	return;
}

/**ektiposi  olon**/
void display(gtype * gtable) {
	hamnode *myNode;
	int i,j = 0;
	for (i = 0; i < K; i++) {
		if (gtable->hash[i].count == 0)
			continue;
		myNode = gtable->hash[i].head;
		if (!myNode)
			continue;
		while (myNode != NULL) {	
			j++;
			printf("%d  ItemID %d |%s|\n",j,myNode->id, myNode->binary );
			myNode = myNode->next;
			
		}
	}
	return;
}

/**katastrofi olon**/
void destroyHam(gtype * gtable){
	//printf("des\n");
	hamnode *temp,*myNode;
	int i;
	for (i = 0;i < K ;i++){
		myNode = gtable->hash[i].head;
		while (myNode != NULL){
			
			gtable->hash[i].head = myNode->next;
			temp = myNode;
			myNode = myNode->next;						  
			//delete apo to inverted gia na doulepsei swsta
			free(temp);
		}
	}
	free(gtable->digi);
	free(gtable->hash);
}

/**fortoma sti vasi**/
void loadToHash(char *name,gtype * gtable){
	FILE *fp;
	int id = 0;
	int c; 
	int n=-1;
	char  str3[SIZE], strX[SIZE],line [SIZE]; 
	/*********************************************/
	fp = fopen(name, "r");
    if (fp == NULL){
		exit(0);
	}
	while( (c = fgetc( fp )) != EOF )
        if( c == '\n' ) n++;
	rewind(fp);
    /****************pernei to string **********/
    hamnodeins temp;
    fscanf(fp, "%s %s", strX, strX);
	while ( fgets ( line, sizeof line, fp ) != NULL ) { /* read a line */
		id++;
		if(id > n)
			break;
		fscanf(fp, "%s %s", strX, str3);    
		temp.id = id;
		strcpy(temp.binary, str3);
		insertToHash(&temp,gtable);
	}
	fclose(fp);
	eleCount = n;

}

/**ipologismos apostasis hamming**/
int HammingDistance(char* a, int na, char* b) {
    int num_mismatches = 0;
    while (na) {
        if (*a != *b)
            ++num_mismatches;

        --na;
        ++a;
        ++b;
    }

    return num_mismatches;
}

/**********iner use*****************************/

/*metrima komvon sot idio bucket*/
int searchInner(char *binary,gtype * gtable) {
	int hashIndex;
	hamnode *myNode;
	char *ptr;
    int ret;
	int k = sizeof(gtable->digi);
	char bits[k+1];
	int a;
	char c;
	char b;
    int j;
    int N = 0;
    for(j = 0;j < k; j++){
		strcpy(&c,&gtable->digi[j]);
		b = c;
		a=b -'0';
		bits[j] = binary[a];
		
	}
	bits[j] = '\0';
	ret = strtol(bits, &ptr, 2);
	hashIndex = ret;
	myNode = gtable->hash[hashIndex].head;
	if (!myNode) {
		return N;
	}
	while (myNode != NULL) {
		N++;
		myNode = myNode->next;
	}
	return N;
}

/**euresi ton kontinon stin aktina**/
void Bestrad(char* binary,int Coun,int radius){
	int i;
	printf("best in radius %d\n",radius);
	for(i = 0;i<Coun;i++){
		if(nearn[i].id != -1){
			if(HammingDistance(binary,SIZE,nearn[i].binary) < radius){
				printf("ItemId %d : ",nearn[i].id);
				printf("%s\n",nearn[i].binary);
			}
		}
	}
}

