#include "headers.h"


/**Concentrate initialization method **/
int concint(double *** distarray, int ** sortconc, int num, int clust){
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
	/**sort ta v[i] gia na epistrepsoume */
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
	return 2;
}


/**k-means++ initialization method**/
int plusplus(double ***distarray, double ***eucdata, char*** hamdata, int **kinit, int num, int clust,int nobit, int dim, int flagt){
	int i,j,k,l,flag0=0;
	double tt;
	int distance[num];
	int prob[num+1];
	if(((*kinit) = calloc(clust, sizeof(int))) == NULL){
		perror("conc"); exit(2);}		
	/**arxikipoiseis*/
	//
	(*kinit)[0] = getUniformInt(0,num-1);
	if (flagt==1)
		distance[0] = (*distarray)[(*kinit[0])][0];
	else if(flagt==2)
		distance[0] = compEucDist((*eucdata)[(*kinit[0])],(*eucdata)[0],dim);
	else if(flagt==3)
		distance[0] = hamdist((*hamdata)[(*kinit[0])],nobit,(*hamdata)[0]);			
	//
	prob[0] = prob[num+1] = 0;	
	for(i=1; i<num; i++){
		distance[i] = RAND_MAX;
		prob[i] = 0;
	}
	/**methodos simfona me tin theoria **/
	for(i=0; i<clust-1; i++){
		for(j=0; j<num; j++){
			//
			if (flagt==1){
				if((*distarray)[(*kinit)[i]][j] < distance[j])
					distance[j] = (*distarray)[(*kinit)[i]][j];
			}
			else if(flagt==2){
				if(compEucDist((*eucdata)[(*kinit)[i]],(*eucdata)[j],dim) < distance[j])
					distance[j] = compEucDist((*eucdata)[(*kinit)[i]],(*eucdata)[j],dim);									
			}
			else if(flagt==3){
				if(hamdist((*hamdata)[(*kinit)[i]],nobit,(*hamdata)[j]) < distance[j])
					distance[j] = hamdist((*hamdata)[(*kinit)[i]],nobit,(*hamdata)[j]);
			}			
			prob[j+1] = pow(distance[j],2) + prob[j];
		}
		//
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
	return 1;
}


/**PAM assignment for Matrix space**/
int pamass(cluster **clusters,double ***distarray, double ***eucdata, char*** hamdata, int num, int clust,int nobit, int dim, int flagt){
	int i,j,flag;
	double tt;
	int idfirst=0, idsec=0;
	double distfirst, distsec;
	//FILE* fp;
	//fp = fopen("CHECK_PAM","a+");
	for (j=0;j<clust;j++){
			(*clusters)[j].head = CreateItem((*clusters)[j].head);
	}
	/** kanei assign simfona me ton algorithmo to kathe simeio sto kontinotero tou medoid*/
	for (i=0;i<num;i++){
		flag=0;
		distfirst = RAND_MAX;
		for (j=0;j<clust;j++){
			//
			if(flagt==1)
				tt = (*distarray)[i][(*clusters)[j].medid];	
			else if(flagt==2)
				tt = compEucDist((*eucdata)[i],(*eucdata)[(*clusters)[j].medid],dim);
			else if(flagt==3)
				tt = hamdist((*hamdata)[i],nobit,(*hamdata)[(*clusters)[j].medid]);
				//
			if(tt < distfirst){
				idsec = idfirst;
				distsec = distfirst;
				distfirst = tt;
				idfirst = j;
				flag++;
			}			
		}
		/**periptosi pou mpainei sto kontinotero cluster*/
		if (flag==1){
			int j=1;
			distsec = RAND_MAX;
			do{
				//
				if(flagt==1)
					tt = (*distarray)[i][(*clusters)[j].medid];
				else if(flagt==2)
					tt = compEucDist((*eucdata)[i],(*eucdata)[(*clusters)[j].medid],dim);
				else if(flagt==3)
					tt = hamdist((*hamdata)[i],nobit,(*hamdata)[(*clusters)[j].medid]);	
					//			
				if( tt < distsec){
					idsec = j;
					distsec = tt;
				}
				j++;
			}while (j < clust);
		}
		
//printf("CHECK 2\n");
		(*clusters)[idfirst].head = InsertItem ((*clusters)[idfirst].head,i, idsec, distsec,distfirst);
		//fprintf(fp,"Closest medoid to item %d is medoid with id %d and d(i,m)=%f and 2nd closest has cid %d and d(i,m2)=%f\n",i,idfirst,distfirst, idsec,distsec);		
		//fprintf(fp,"2nd closest has cid %d and d(i,m2)=%f\n",(*clusters)[idfirst].head->secondid,(*clusters)[idfirst].head->distsec);		
		(*clusters)[idfirst].sumdist += distfirst;
		(*clusters)[idfirst].idcount ++;		
	}
	//fclose(fp);
	return 1;
	
}

/**Update a la Lloyd’s**/
int alalloyd(cluster **clusters,double ***distarray, double ***eucdata, char*** hamdata, int num, int clus,int nobits, int dim, int flagt){
	item	*pl1=NULL;
	item	*pl2=NULL;
	int i,j,k,tempid;
	double tempsum=0.0,tempmin;
	int flag = 0;
	/** gia kathe cluster, pairnei ena ena ola ta items */
	for(k = 0;k<clus;k++){
		pl1 = (*clusters)[k].head;
		tempid = (*clusters)[k].medid;
		tempmin = (*clusters)[k].sumdist;
		for(i = 0;i<(*clusters)[k].idcount;i++){
			pl2 = (*clusters)[k].head;
			tempsum = 0;
			/** vriskei to item me to elaxisto topiko kostos kai to kanei medoid*/
			for(j = 0;j<(*clusters)[k].idcount;j++){
				//
				if(flagt==1){
					tempsum += (*distarray)[pl1->itemid][pl2->itemid];}
				else if(flagt==2){
					tempsum += compEucDist((*eucdata)[pl1->itemid],(*eucdata)[pl2->itemid],dim);}
				else if(flagt==3){
					tempsum += hamdist((*hamdata)[pl1->itemid],nobits,(*hamdata)[pl2->itemid]);}
				//
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
	/**an pragmatopoithei allagi adeiazei ta clusters gia na gemisoun stin sinexeia */
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

/**Update CLARANS**/
int clarans(cluster **clusters,double ***distarray, double ***eucdata, char*** hamdata, int clus, int num,int nobits, int dim, int flagt,int s,int q){
	int l=0;
	int flag = 0;
	int uni,m,t,k;
	item	*pl1=NULL;	
	double newcost, bettercost, bestcost=0.0;
	int newmeds[clus], bestmeds[clus];	
	int bound = (clus*num) - 1;
	int i,j,z1,z2;
	/**arxikopoiiseis*/
	for (j=0; j<clus; j++){
		newmeds[j] = (*clusters)[j].medid;
		bestmeds[j] = (*clusters)[j].medid;		
		bestcost += (*clusters)[j].sumdist;
		bettercost += (*clusters)[j].sumdist;		
	}
	/** s is numlocal and i is mincost*/
	for(i=0; i<s; i++){
		j=0;
		while(j<q){
			/**pairnei random neighbour tou current, zeygari (m,t)*/
			uni = getUniformInt(0,bound);
			m = uni%clus;
			t = floor(uni/clus);
			/**ipologizei to kostos toy random neighbour*/
			l++;
			if (flagt==1)
				newcost = computecost(clusters,distarray,NULL,NULL,clus,num,0,0,1,m,t);
			if (flagt==2)
				newcost = computecost(clusters,NULL,eucdata,NULL,clus,num,0,dim,2,m,t);
			if (flagt==3)
				newcost = computecost(clusters,NULL,NULL,hamdata,clus,num,nobits,0,3,m,t);							
			/** an to cost differential einai mikrotero*/
			if(newcost < bettercost){
				bettercost=newcost;
			/**kanei to pam swap kai stin sinexeia pigenei stin arxi ton epanalipseon*/
				(*clusters)[m].medid = t;
				newmeds[m] = t;				
				/**eleutheronei*/
				for(z1 = 0;z1<clus;z1++){
					for(z2 = 0;z2<(*clusters)[z1].idcount;z2++){
						pl1 = (*clusters)[z1].head;
						(*clusters)[z1].head = DeleteItem((*clusters)[z1].head, pl1->itemid);
						pl1 = pl1->next;
					}
					(*clusters)[z1].sumdist = 0;
					(*clusters)[z1].idcount = 0;
				}
				/**kai ksanakanei assign me PAM*/
				//
				if(flagt==1)
					pamass(clusters,distarray,NULL,NULL,num,clus,0,0,1);
				else if(flagt==2)
					pamass(clusters,NULL,eucdata,NULL,num,clus,0,dim,2);			
				else if(flagt==3)	
					pamass(clusters,NULL,NULL,hamdata,num,clus,nobits,0,3);
				//					
				j=0;
				continue;
			}
			j++;				
		}
		if(bettercost<bestcost){
			bestcost = bettercost;
			for (j=0; j<clus; j++)
				bestmeds[j] = newmeds[j];
			flag = 1;								
		}
		for (j=0; j<clus; j++)
			bestmeds[j] = newmeds[j];			
	}
	if (flag == 1){	
		//printf("flag is 1\n");
		for (k=0; k<clus; k++){
			(*clusters)[k].medid = bestmeds[k];	
			//printf("and new medid id %d\n",(*clusters)[k].medid);
		}
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
	//printf("just exited clarans update\n");
	//printf("q is %d and l is %d\n",q,l);
	return flag;
}


/**evaluation method silhouettes */
double silhouettes(cluster **clusters, double ***distarray, int clus, char *output){
	item *pl1=NULL;
	item *pl2=NULL;	
	double totdis=0;
	//FILE* fp;	
	//fp=fopen("silh","a+");
	int i,j,k;//,z1,z2;
	double atempsum, btempsum,clusavd;
	int maxnum = 0;
	for(k=0; k<clus; k++)
		if ((*clusters)[k].idcount > maxnum)
			maxnum = (*clusters)[k].idcount;				
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
			
			btempsum = 0;							
			pl2 = (*clusters)[pl1->secondid].head;
		//	printf("pl1->secondid is %d\n",	pl1->secondid);		
			for(j=0;j<(*clusters)[pl1->secondid].idcount; j++){
				btempsum += (double)(*distarray)[pl1->itemid][pl2->itemid];
				pl2 = pl2->next;
			}
			bi[i] = btempsum/((*clusters)[pl1->secondid].idcount);		
			if(ai[i] < bi[i])
				si[i] = (1 - (ai[i]/bi[i]));
			else if(ai[i] > bi[i])
				si[i] = ((bi[i]/ai[i]) - 1);
			else 
				si[i] = 0;
			clusavd +=	si[i];		
			//fprintf(fp,"a[%d]=%f and b[%d]=%f and s[%d] is %f\n\n",i,ai[i],i,bi[i],i,si[i]); 
			pl1 = pl1->next;
		}
		(*clusters)[k].s = (clusavd = (clusavd/(*clusters)[k].idcount));
		totdis += clusavd;
	}
	//fclose(fp);	
	return (totdis/clus);
}




