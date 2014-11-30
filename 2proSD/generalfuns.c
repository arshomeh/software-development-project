#include "headers.h"

configuration setConfig(char* config,int num){
	FILE* fp;
	configuration c;
	char ch;
	double z;
	int flag = 0;
	char temp[SIZEofBUFF];
	char number[SIZEofBUFF];
	char str[SIZEofBUFF];
	fp = fopen(config,"r");
	c.Clasters = -1;
	c.HashFunctions = -1;
	c.HashTables = -1;
	c.ClaransFraction = -1;
	c.ClaransIterations = -1;
	if(fp == NULL){
		return c;
	}
	strcpy(temp,"");
	strcpy(number,"");
	
	while(!feof(fp)){
		ch = fgetc(fp);
		if(ch == ' '){
			ch = fgetc(fp);
			while (ch != '\n'){
				if(ch >= 0 || ch <= 9){
					sprintf(str,"%c",ch);
					strcat(number,str);
					flag = 1;	
				}
				ch = fgetc(fp);
			}
			if(flag == 1){
				//printf("num is %s\n",number);
				//printf("temp is %s\n",temp);
				if(strcmp(temp,"number_of_clusters:") == 0){
					c.Clasters = atoi(number);
				}
				if(strcmp(temp,"number_of_hash_functions:") == 0)
					c.HashFunctions = atoi(number);
				if(strcmp(temp,"number_of_hash_tables:") == 0)
					c.HashTables = atoi(number);
				if(strcmp(temp,"clarans_set_fraction:") == 0)
					c.ClaransFraction = atoi(number);
				if(strcmp(temp,"clarans_iterations:") == 0)
					c.ClaransIterations = atoi(number);
			}
			strcpy(temp,"");
			strcpy(number,"");
		}
		sprintf(str,"%c",ch);
		if(ch != '\n')
			strcat(temp,str);
		flag = 0;
	}
	if(c.HashFunctions == -1)
		c.HashFunctions = 4;
	if(c.HashTables == -1)
		c.HashTables = 5;
	if(c.ClaransFraction == -1){
		if((z = (0.12 * c.Clasters*(num - c.Clasters)))>250)
			c.ClaransFraction = (int)z;
		else 
			c.ClaransFraction = 250;
	}
	if(c.ClaransIterations == -1)
		c.ClaransIterations = 2;
	if(c.Clasters == -1){
		printf("ERROR: You should give the number of clusters!\n");
		exit(5);
	}
	return c;
}

int readData(char* data,char* config){
	FILE* fp;
	int flag = -1; // 1 for ham, 2 for euc, 3 for matrix 
	char XXX[SIZEofBUFF];
	char type[SIZEofBUFF];
	fp = fopen(data,"r");
	if(fp == NULL){
		perror("read data");
		exit(1);
	}
	fscanf(fp,"%s %s",XXX,type);			
	if( strcmp(XXX,"@metric_space") != 0){
		printf("Error... Incorect data file\n");
		exit(1);
	}
	if( strcmp(type,"vector") == 0){			
		printf("\nvector\n");
		flag = 2;
		//VecMain(data,query,k,L);
	}
	else if(strcmp(type,"hamming") == 0){		
		printf("hamming\n");
		flag = 1;
		//	HamMain(data,query,k,L);
	}
	else if(strcmp(type,"matrix") == 0){
		printf("matrix\n");
		flag = 3;
		//MatMain(data,query,k,L);
	}
	if(flag == -1){
		printf("wrong data file\n");
		exit(1);
	}
	fclose(fp);
	//printData(data,flag);
	//point c = lloyd(data,flag,k);
	return flag;
}

int numberOfitems(char* data,int flag){
	FILE* fp;
	char c;
	int n = 0;
	char XXX[SIZEofBUFF];
	char binary[SIZE];
	char line [SIZE];
	fp = fopen(data,"r");
	if(fp == NULL){
		perror("print data:");
		exit(4);
	}
	if(flag == 1){//hamming
		n = -1;
		while( (c = fgetc( fp )) != EOF )
			if( c == '\n' ) n++;
		rewind(fp);
		fscanf(fp, "%s %s", XXX, XXX);
		while ( fgets ( line, sizeof line, fp ) != NULL ) { /* read a line */
			fscanf(fp, "%s %s", XXX, binary);    
		}
	}
	else if(flag == 2){//euclidean
		while( (c = fgetc( fp )) != EOF ){
			if( c == '\n' ) 
				n++;//ypologizoume to n
			}
		rewind(fp);
		n = n-2;
	}
	else if(flag == 3){//matrix
		while( (c = fgetc( fp )) != EOF ){
			if( c == '\n' ) 
				n++;//ypologizoume to n			
		}
		rewind(fp);
		n = n-2;
		n = 0;
		fscanf(fp, "%s %s",XXX,XXX);
		fscanf(fp,"%s",XXX);
		while( (c = fgetc( fp )) != '\n' ){
			if( c == ',') 
				n++;//ypologizoume to n		
		}
		rewind(fp);
		n = n+1;
	}
	return n;
}

int getUniformInt(int rStart, int rEnd){
	int r;	
	r = rStart + (int)((rand() / (RAND_MAX + 1.0)) *(rEnd - rStart +1.0)); 
	return r;
}

double getUniformDouble(double rStart, double rEnd){
	double r;
	r = rStart + (rEnd-rStart)*((double)(rand())/((double)RAND_MAX));
	return r;
}

void printclusters(cluster **clusters,int complarga, char *filep, int iflag, int aflag, int uflag,int clus, double ttime, double totdis){
	FILE* fp;
	int k,i;
	item *pl1=NULL;	
	fp = fopen(filep,"a+");
	fprintf(fp, "Algorithm: I%dA%dU%d, x:{1,2}\n", iflag,aflag,uflag);
	/**a little extra**/
	if (iflag==1)
		fprintf(fp, "Initialization method K-means++ [Park-Jun]\n");
	else if (iflag==2)
		fprintf(fp, "Initialization method Concentrate [Arthur-Vassilvitskii]\n");
	if (aflag==1)
		fprintf(fp, "Assignment method PAM\n");
	else if (aflag==2)
		fprintf(fp, "Assignment method Reverse-LSH\n");
	if (uflag==1)
		fprintf(fp, "Update method \"A la Lloyds\" [Park-Jun]\n\n");
	else if (uflag==2)
		fprintf(fp, "Update method CLARANS [Ng-Han]\n\n");
	for(k=0;k<clus;k++)
		fprintf(fp, "CLUSTER-%d {size:%d medoid(id):%d}\n", k, (*clusters)[k].idcount,(*clusters)[k].medid);	
	fprintf(fp, "Clustering time: %f seconds\n", ttime);								
	fprintf(fp, "Average dissimilarity given by Silhouettes method:  {");
	for(k=0;k<clus;k++)
		fprintf(fp, "s[%d]=%f, ", k, (*clusters)[k].s);		
	fprintf(fp, "}\nTotal average dissimilarity of Dataset is %f\n\n",totdis);
	if (complarga == 1){
		fprintf(fp,"Complete Clustering is given below:\n");
		for(k=0;k<clus;k++){
			pl1 = (*clusters)[k].head;		
			fprintf(fp, "CLUSTER-%d  { ", k);	
			for(i=0; i<(*clusters)[k].idcount; i++){
				fprintf(fp," %d,", pl1->itemid);
				pl1 = pl1->next;
			}
			fprintf(fp,"}\n");
		}	
	}
	fclose(fp);
}

