#include "../headers.h"

int getmatdata(char* data,int ***matdata,int num){
	FILE* fp;
	int i,j;
	char c;
	char XXX[SIZEofBUFF];
	fp = fopen(data,"r");
	(*matdata) = malloc(num* sizeof(int*));
	fscanf(fp, "%s %s",XXX,XXX);
	fscanf(fp,"%s",XXX);
	while( (c = fgetc( fp )) != '\n' &&  (c != '\t')){
		//do nothing
	}
	for(j = 0;j<num; j++)
		(*matdata)[j] = malloc(num* sizeof(int));
	
	int a;
	for(j = 0;j<num; j++){
		for(i = 0;i<num;i++){
			fscanf(fp,"%d",&a);
			(*matdata)[j][i] = a;
		}		
	}
	fclose(fp);
	return 0;
}

/**Concentrate initialization method **/
void concint(int *** distarray, int ** sortconc, int num, int clust){
	int sumdist[num];
	double x;
	double sumtosort[num][2];
	double finalsum, swag;
	int i,j, linesum;
	if(((*sortconc) = malloc(clust* sizeof(double))) == NULL){
		perror("conc"); exit(2);}
	/**compute sum of distances for each line **/
	for (i=0;i<num;i++){
		linesum = 0;
		for(j=0;j<num;j++){
			linesum += (*distarray)[i][j];
		}
		sumdist[i] = linesum;
	}
	/**compute sums v[i] from the theoria */
	for (i=0;i<num;i++){
		sumtosort[i][0] = i;
		finalsum = 0;
		for (j=0;j<num;j++){
			x = (double)((*distarray)[i][j])/sumdist[j];
			finalsum += x;		
		}
		sumtosort[i][1] = finalsum;
	}
	/**bubble sort ta v[i] gia na epistrepsoume */
	for (i = 0; i < (num-1); i++){
		for (j = 0; j < (num-i-1); j++){
			if (sumtosort[j][1] > sumtosort[j+1][1]){
				swag = sumtosort[j][0];
				sumtosort[j][0] = sumtosort[j+1][0];
				sumtosort[j+1][0] = swag;
				swag = sumtosort[j][1];
				sumtosort[j][1] = sumtosort[j+1][1];
				sumtosort[j+1][1] = swag;  
			}	
		}
	}
	for(i=0; i<clust; i++)
		(*sortconc)[i] = sumtosort[i][0];																																																																																																																
	return;
}

/**k-means++ initialization method**/
void plusplusmat(int *** distarray, int **kinit, int num, int clust){
	
	int i,j,k,l,flag0=0;
	double tt;
	int distance[num];
	int prob[num+1];
	if(((*kinit) = calloc(clust, sizeof(int))) == NULL){
		perror("conc"); exit(2);}
		
	/**arxikipoiseis*/
	(*kinit)[0] = getUniformInt(0,num-1);
	distance[0] = (*distarray)[(*kinit[0])][0];
	prob[0] = prob[num+1] = 0;	
	for(i=1; i<num; i++){
		distance[i] = RAND_MAX;
		prob[i] = 0;
	}
	
	/**methodos simfona me tin theoria **/
	for(i=0; i<clust-1; i++){
		for(j=0; j<num; j++){
			if((*distarray)[(*kinit)[i]][j] < distance[j])
				distance[j] = (*distarray)[(*kinit)[i]][j];
			prob[j+1] = pow(distance[j],2) + prob[j];
		}
		do{
			flag0 = 0;
			/** pairnei random tt kai vriskei diastima r-1<tt<r **/
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
void assmat(cluster **clusters,int *** distarray,int clus,int num){
	int i,j;
	int tempdist,tempid;
	for (j=0;j<clus;j++){
			(*clusters)[j].head = CreateItem((*clusters)[j].head);
	}
	for (i=0;i<num;i++){
		tempdist = RAND_MAX;
		for (j=0;j<clus;j++){
			if((*distarray)[i][(*clusters)[j].medid] < tempdist){
				tempdist = (*distarray)[i][(*clusters)[j].medid];
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
int alalloydmat(cluster **clusters,int *** distarray,int clus,int num){
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
				tempsum += (*distarray)[pl1->itemid][pl2->itemid];
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

int claransmat(cluster **clusters,int *** distarray,int clus,int num,int s,int q){
	int zeugaria[q][2];
	int flag = 0;
	int x1, x2;
	int xx = (clus*num) - 1;
	int z1, z2, i,j;
	item	*pl1=NULL;
	int tempdist;
	int unitemp;
	for(z1=0; z1<s; z1++){ 
		for(z2=0; z2<q; z2++){
			unitemp = getUniformInt(0,xx);
			x1 = (zeugaria[z2][0] = unitemp%clus);
			x2 = (zeugaria[z2][1] = floor(unitemp/clus));
			//printf(" zeugari[%d] %d - %d\n", z2 ,		zeugaria[z2][0],		zeugaria[z2][1]);
			//for(i=0; i < (*clusters)[x1].idcount ; i++){
				pl1 = (*clusters)[x1].head;
				tempdist=0;
				for(j=0; j<(*clusters)[x1].idcount; j++){
					tempdist += (*distarray)[x2][pl1->itemid];
					pl1 = pl1->next;					
				}
				if (tempdist < ((*clusters)[x1].sumdist)){
					(*clusters)[x1].medid = x2;
					(*clusters)[x1].sumdist = tempdist;
					flag = 1;
				}
			//}
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


double silhouettes(cluster **clusters, int ***distarray, int clus, char *output){
	item *pl1=NULL;
	item *pl2=NULL;	
	double totdis=0;
	FILE* fp;	
	int i,j,k,z1,z2;
	double atempsum, btempsum, minavd, tempavd, clusavd;
	int nearcid;
	fp = fopen(output,"a+");		
	/**ksekinaei na vrei to average dissimilarity gia kathe cluster **/
	for(k=0; k<clus; k++){
		double ai[(*clusters)[k].idcount];
		double bi[(*clusters)[k].idcount];
		double si[(*clusters)[k].idcount];		
		pl1 = (*clusters)[k].head;
		clusavd = 0;		
		/**paei na vrei to avg. dissimilarity gia kathe simeio tou cluster**/
		for(i=0; i<(*clusters)[k].idcount; i++){
			atempsum = 0;
			pl2 = (*clusters)[k].head;			
			for(j=0;j<(*clusters)[k].idcount; j++){
				atempsum += (double)(*distarray)[pl1->itemid][pl2->itemid];
				pl2 = pl2->next;
			}
			ai[i] = atempsum/(((*clusters)[k].idcount)-1);
			
			minavd = RAND_MAX;
			for(z1=0; z1<clus ;z1++){
				if(z1==i)
					continue;
				btempsum = 0;	
				pl2 = (*clusters)[z1].head;
				for(z2=0;z2<(*clusters)[z1].idcount; z2++){
					btempsum += (double)(*distarray)[pl1->itemid][pl2->itemid];
					pl2 = pl2->next;
				}

				tempavd = btempsum / ((*clusters)[z1].idcount);
					//			printf("btempsum is %f and count is %d and tempavd is %f\n", btempsum,(*clusters)[z1].idcount, tempavd);
				if(tempavd < minavd){
					minavd = tempavd;
					nearcid = z1;
				}
			}
			bi[i] =minavd;
			if(ai[i] < bi[i])
				si[i] = 1 - (ai[i]/bi[i]);
			else
				si[i] = (ai[i]/bi[i]) - 1;
			clusavd +=	si[i];		
		//	printf("a[%d]=%f and b[%d]=%f and s[%d] is %f\n\n",i,ai[i],i,bi[i],i,si[i]); 
			pl1 = pl1->next;
		}
		(*clusters)[k].s = (clusavd = (clusavd/(*clusters)[k].idcount));
		totdis += clusavd;
	}
	fclose(fp);	
	return (totdis/clus);
}

void clustinitialize(cluster **clusters,int** tableinit,int clus ){
	int i;
	
	for(i = 0;i<clus;i++){		
		(*clusters)[i].medid = (*tableinit)[i];
		(*clusters)[i].sumdist = 0;
		(*clusters)[i].idcount = 0;
	}
	
}

void freecluster(cluster **clusters,int clus ){
	int i,j;
	item *pl1=NULL;
	for(i = 0;i<clus;i++){
		for(j = 0;j<(*clusters)[i].idcount;j++){
			pl1 = (*clusters)[i].head;
			(*clusters)[i].head = DeleteItem((*clusters)[i].head, pl1->itemid);
			pl1 = pl1->next;
		}		
	}
}
