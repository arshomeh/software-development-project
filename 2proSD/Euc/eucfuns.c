#include "../headers.h"

int geteucdata(char* data,float *** eucdata,int num,int dim){
	int i;
	int j;
	char XXX[SIZEofBUFF];
	FILE* fp;
	fp = fopen(data,"r");
	if(((*eucdata)= malloc(num * sizeof(float*))) == NULL){
		perror("1:");
		exit(4);
	}
	fscanf(fp, "%s %s %s %s",XXX,XXX,XXX,XXX);
	for(i = 0;i < num;i++){
		fscanf(fp, "%s",XXX);
		if(((*eucdata)[i] =  malloc(dim * sizeof(float))) == NULL){
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

float compEucDist(float* p, float *v,int dim){
	float sum = 0;
	float EucDist;
	int i = 0;
	for (i = 0;i<dim;i++){
		sum += pow((p[i]-v[i]),2);
	}
	return EucDist = sqrt(sum);
}

/**k-means++ initialization method*/
void pluspluseuc(float ***eucdata, int **kinit, int num, int clust,int dim){
	
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
}


/**PAM assignment for Matrix space**/
void asseuc(cluster **clusters,float ***eucdata,int clus,int num,int dim){
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
	return;	
}

/**Update a la Lloyd’s**/
int alalloydeuc(cluster **clusters,float ***eucdata,int clus,int num,int dim){
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

int claranseuc(cluster **clusters,float ***eucdata,int clus,int num,int s,int q,int dim){
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
				tempdist += compEucDist((*eucdata)[x2],(*eucdata)[pl1->itemid],dim);
				pl1 = pl1->next;	
				if (tempdist < ((*clusters)[x1].sumdist)){
					(*clusters)[x1].medid = x2;
					(*clusters)[x1].sumdist = tempdist;
					flag = 1;
				}
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



