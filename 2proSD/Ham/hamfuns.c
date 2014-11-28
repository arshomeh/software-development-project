#include "../headers.h"

int gethamdata(char* data,char *** hamdata,int num){
	char XXX[SIZEofBUFF];
	char binary[SIZE];
	char line [SIZE*2];
	int i = 0;
	FILE* fp;
	fp = fopen(data,"r");
	(*hamdata)= malloc(num * sizeof(char *));
	
	while ( fgets ( line, sizeof line, fp ) != NULL ) { /* read a line */
			fscanf(fp, "%s %s", XXX, binary); 
			(*hamdata)[i] =  malloc(SIZE * sizeof(char *));
			strcpy((*hamdata)[i],binary);
			i++;
	}
	fclose(fp);
	return 0;
}

int hamdist(char* a, int nobits, char* b) {
    int num_mismatches = 0;
    while (nobits) {
		if (*a != *b)
            ++num_mismatches;

        --nobits;
        ++a;
        ++b;
    }
    return num_mismatches;
}

/**k-means++ initialization method*/
void plusplusham(char ***hamdata, int **kinit, int num, int clust,int nobit){
	
	int i,j,k,l,flag0=0;
	int x;
	double tt;
	int distance[num];
	int prob[num+1];
	if(((*kinit) = calloc(clust, sizeof(int))) == NULL){
		perror("conc"); exit(2);}
		
	/**arxikipoiseis*/
	(*kinit)[0] = getUniformInt(0,num-1);
	distance[0] = hamdist((*hamdata)[(*kinit[0])],nobit,(*hamdata)[0]);
	prob[0] = prob[num+1] = 0;	
	for(i=1; i<num; i++){
		distance[i] = RAND_MAX;
		prob[i] = 0;
	}
	
	/**methodos simfona me tin theoria */
	for(i=0; i<clust-1; i++){
		for(j=0; j<num; j++){
			if((x = hamdist((*hamdata)[(*kinit)[i]],nobit,(*hamdata)[j])) < distance[j])
				distance[j] = x;
			prob[j+1] = pow(distance[j],2) + prob[j];
		}
		do{
			flag0 = 0;
			/** pairnei random tt kai vriskei diastima r-1<tt<r */
			tt = getUniformDouble(0,prob[num]);
			for(l=0; l<num; l++){		
				if(tt < (double)prob[l]){
					for(k=0; k<i+1; k++){			
						if(j == (*kinit)[k]){
							flag0 = 1;
							break;
						}
					}
					/** efoson den exei ksanadialextei dialegei ton r me r **/
					if (flag0 == 0){
						(*kinit)[i+1] = l;	
						flag0 = 0;					
						break;
					}
					break;
				}
			}
		}while(flag0 == 1);
	}	
}


/**PAM assignment for Matrix space**/
void assham(cluster **clusters,char ***hamdata,int clus,int num,int nobits){
	int i,j,x;
	int tempdist,tempid;
	for (j=0;j<clus;j++){
			(*clusters)[j].head = CreateItem((*clusters)[j].head);
	}
	for (i=0;i<num;i++){
		tempdist = RAND_MAX;
		for (j=0;j<clus;j++){
			if((x = hamdist((*hamdata)[i],nobits,(*hamdata)[(*clusters)[j].medid])) < tempdist){
				tempdist = x;
				tempid = j;
			}
		}
		(*clusters)[tempid].head = InsertItem ((*clusters)[tempid].head,i);
		(*clusters)[tempid].sumdist += tempdist;
		(*clusters)[tempid].idcount ++;
	}
	return;	
}

/**Update a la Lloyd’s**/
int alalloydham(cluster **clusters,char ***hamdata,int clus,int num,int nobits){
	item	*pl1=NULL;
	item	*pl2=NULL;
	int i,j,k,tempsum=0, tempmin, tempid;
	int flag = 0;
	for(k = 0;k<clus;k++){
		pl1 = (*clusters)[k].head;
		tempid = (*clusters)[k].medid;
		tempmin = (*clusters)[k].sumdist;
		for(i = 0;i<(*clusters)[k].idcount;i++){
			pl2 = (*clusters)[k].head;
			tempsum = 0;
			for(j = 0;j<(*clusters)[k].idcount;j++){
				tempsum += hamdist((*hamdata)[pl1->itemid],nobits,(*hamdata)[pl2->itemid]);
				pl2 = pl2->next;
			}
			if (tempsum < tempmin){
				tempid = pl1->itemid;
				tempmin = tempsum;
				flag = 1;
			}
			pl1 = pl1->next;
		}
		(*clusters)[k].sumdist = tempmin;
		(*clusters)[k].medid = tempid;
	}
	if (flag == 1){
		for(i = 0;i<clus;i++){
			for(j = 0;j<(*clusters)[i].idcount;j++){
				pl1 = (*clusters)[i].head;
				(*clusters)[i].head = DeleteItem((*clusters)[i].head, pl1->itemid);
				pl1 = pl1->next;
			}
			(*clusters)[i].sumdist = 0;
			(*clusters)[i].idcount = 0;
		}
	}
	return flag;
}

int claransham(cluster **clusters,char *** hamdata,int clus,int num,int s,int q,int nobits){
	int zeugaria[q][2];
	int flag = 0;
	int x1, x2;
	int xx = (clus*num) - 1;
	int z1, z2, i,j;
	item	*pl1=NULL;
	int tempdist;
	int unitemp;
	for(z1=0; z1<s; z1++){
		// printf("ss\n");
		for(z2=0; z2<q; z2++){
			unitemp = getUniformInt(0,xx);
			x1 = (zeugaria[z2][0] = unitemp%clus);
			x2 = (zeugaria[z2][1] = floor(unitemp/clus));
			pl1 = (*clusters)[x1].head;
			tempdist=0;			
			//printf(" zeugari[%d] %d - %d\n", z2 ,		zeugaria[z2][0],		zeugaria[z2][1]);
			for(i=0; i < (*clusters)[x1].idcount ; i++){
				tempdist += hamdist((*hamdata)[x2],nobits,(*hamdata)[pl1->itemid]);
				pl1 = pl1->next;	
			}
			if (tempdist < ((*clusters)[x1].sumdist)){
				(*clusters)[x1].medid = x2;
				(*clusters)[x1].sumdist = tempdist;
				flag = 1;
			}
		}
	}
	if (flag == 1){
		for(i = 0;i<clus;i++){
			for(j = 0;j<(*clusters)[i].idcount;j++){
				pl1 = (*clusters)[i].head;
				(*clusters)[i].head = DeleteItem((*clusters)[i].head, pl1->itemid);
				pl1 = pl1->next;
			}
			(*clusters)[i].sumdist = 0;
			(*clusters)[i].idcount = 0;
		}
	}
	return flag;
}
