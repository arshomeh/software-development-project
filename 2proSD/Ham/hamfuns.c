#include "../headers.h"

int gethamdata(char* data,char *** hamdata,int num){
	char XXX[SIZEofBUFF];
	char binary[SIZE];
	//char line [SIZE*2];
	int i = 0;
	FILE* fp;
	fp = fopen(data,"r");
	(*hamdata)= malloc(num * sizeof(char*));
	fscanf(fp, "%s %s", XXX, XXX);
	while (i<num){//( fgets ( line, sizeof line, fp ) != NULL ) { /* read a line */
			fscanf(fp, "%s %s", XXX, binary); 
			(*hamdata)[i] =  malloc(SIZE * sizeof(char));
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
int plusplusham(char ***hamdata, int **kinit, int num, int clust,int nobit){
	
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
	return 1;	
}


/**PAM assignment for Matrix space**/
int assham(cluster **clusters,char ***hamdata,int clus,int num,int nobits){
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
	return 1;	
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
	
	int flag = 0;
	int x1;
	int bound = (clus*num) - 1;
	int z1, z2, i,j;
	item	*pl1=NULL;
	int tempdist, clusdist,bestdistfroms;
	int temptotaldist = 0;
	int neardist, dist, previd, unitemp;
	int tempmed[clus], bestfroms[clus];
	/**arxikopoiiseis*/
	for (j=0; j<clus; j++){
		tempmed[j] = (*clusters)[j].medid;
		bestfroms[j] = (*clusters)[j].medid;		
		temptotaldist += (*clusters)[j].sumdist;
	}
	clusdist = (bestdistfroms = temptotaldist);
	/** gia kathe s elegxei q zeygaria */
	for(z1=0; z1<s; z1++){ 
		for(z2=0; z2<q; z2++){
			/**dialegei tixaia to zeugos (clusterid, pointid)*/
			unitemp = getUniformInt(0,bound);
			x1 = unitemp%clus;
			previd = tempmed[x1];
			tempmed[x1] = floor(unitemp/clus);
			tempdist = 0;
			/**afou ekane to swap ipologizei to neo sinoliko costos tou clustering*/
			for(i=0; i<num; i++){
				neardist = RAND_MAX;
				for (j=0; j<clus; j++){
						if((hamdist((*hamdata)[i],nobits,(*hamdata)[tempmed[j]]) < neardist))
							dist = hamdist((*hamdata)[i],nobits,(*hamdata)[tempmed[j]]);			
				}
				tempdist += dist;	
			}
			/**an to sinoliko kostos einai mikrotero, to krataei, ean den einai "akironei" tin allagi*/
			if(tempdist < temptotaldist)
				temptotaldist = tempdist;
			else
				tempmed[x1] = previd;
		}
		/**an oi allages poy eginan dinoyn mikrotero kostos apo tis allages se proigoumeno s, tote tis krataei*/
		if(temptotaldist < bestdistfroms){
			bestdistfroms = temptotaldist;
			for (i=0; i<clus; i++)
				bestfroms[i] = tempmed[i];
		}
	}
	/**an to kalitero apotelesma poy edosan oi s epanalipseis einai kalitero apo auto poy eixame */
	if(bestdistfroms < clusdist){
		flag = 1;
		for (i=0; i<clus; i++)
				(*clusters)[i].medid = bestfroms[i];
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
