#include "../headers.h"

int geteucdata(char* data,double *** eucdata,int num,int dim){
	int i;
	int j;
	char XXX[SIZEofBUFF];
	FILE* fp;
	fp = fopen(data,"r");
	if(((*eucdata)= malloc(num * sizeof(double*))) == NULL){
		perror("1:");
		exit(4);
	}
	fscanf(fp, "%s %s %s %s",XXX,XXX,XXX,XXX);
	for(i = 0;i < num;i++){
		fscanf(fp, "%s",XXX);
		if(((*eucdata)[i] =  malloc(dim * sizeof(double))) == NULL){
				printf("\nj is -->%d || i is -->%d\n",j,i);
				perror("2:");
				exit(4);
		}
		for(j = 0;j < dim; j++){
			char kk[50];
			char *ptr;
			fscanf(fp,"%s",kk);
			(*eucdata)[i][j] = strtold(kk, &ptr);
		}
	}
	fclose(fp);
	return 0;
}

int getdim(char* data){
	int dim = 1;
	char c;
	char XXX[SIZEofBUFF];
	FILE* fp;
	fp = fopen(data,"r");
	fscanf(fp, "%s %s",XXX,XXX);
	fscanf(fp, "%s %s",XXX,XXX);
	fscanf(fp, "%s %s",XXX,XXX);
	c = getc(fp);
	while(c != '\n'){
		if(c == '\t' || c == ' ')
			dim++;
		c = getc(fp);
	}
	fclose(fp);
	return dim;
}

double compEucDist(double* p, double *v,int dim){
	double sum = 0;
	double EucDist;
	int i = 0;
	for (i = 0;i<dim;i++){
		sum += pow((p[i]-v[i]),2);
	}
	return EucDist = sqrt(sum);
}

/**k-means++ initialization method*/
int pluspluseuc(double ***eucdata, int **kinit, int num, int clust,int dim){
	
	int i,j,k,l,flag0=0;
	int x;
	double tt;
	int distance[num];
	int prob[num+1];
	if(((*kinit) = calloc(clust, sizeof(int))) == NULL){
		perror("conc"); exit(2);}
		
	/**arxikipoiseis*/
	(*kinit)[0] = getUniformInt(0,num-1);
	distance[0] = compEucDist((*eucdata)[(*kinit[0])],(*eucdata)[0],dim);
	prob[0] = prob[num+1] = 0;	
	for(i=1; i<num; i++){
		distance[i] = RAND_MAX;
		prob[i] = 0;
	}
	
	/**methodos simfona me tin theoria */
	for(i=0; i<clust-1; i++){
		for(j=0; j<num; j++){
			if((x = compEucDist((*eucdata)[(*kinit)[i]],(*eucdata)[j],dim)) < distance[j])
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
int asseuc(cluster **clusters,double ***eucdata,int clus,int num,int dim){
	int i,j,x;
	int tempdist,tempid;
	for (j=0;j<clus;j++){
			(*clusters)[j].head = CreateItem((*clusters)[j].head);
	}
	for (i=0;i<num;i++){
		tempdist = RAND_MAX;
		for (j=0;j<clus;j++){
			if((x = compEucDist((*eucdata)[i],(*eucdata)[(*clusters)[j].medid],dim)) < tempdist){
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
int alalloydeuc(cluster **clusters,double ***eucdata,int clus,int num,int dim){
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
				tempsum += compEucDist((*eucdata)[pl1->itemid],(*eucdata)[pl2->itemid],dim);
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

int claranseuc(cluster **clusters,double ***eucdata,int clus,int num,int s,int q,int dim){
	
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
						if((compEucDist((*eucdata)[i],(*eucdata)[tempmed[j]],dim) < neardist))
							dist = compEucDist((*eucdata)[i],(*eucdata)[tempmed[j]],dim);			
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



