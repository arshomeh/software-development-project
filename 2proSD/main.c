#include <stdio.h>
#include <stdlib.h>

#include "headers.h"

int main (int argc, char** argv){  //Tha einai tis morfis: ./medoids –d <input file> –c <configuration file> -o <output file>
	//struct timeval time;
	//gettimeofday(&time, NULL);
	//FILE * OUT = NULL;
	//srand((time.tv_sec*1000)+(time.tv_usec/1000));
	FILE *infile;//*configf,*outputf;
  	int i,j;
   //	int k, L;
    int flagd, flagc, flago;
    char	type[SIZEofBUFF];
   	char	XXX[SIZEofBUFF];
    char 	data[SIZEofBUFF];
	char 	config[SIZEofBUFF];
	char	output[SIZEofBUFF];
	int err = 0;
	flagd = flagc = flago = 0;
	
	/* diavasma parametron */
	if (argc%2 == 0){
		printf("\nIncorrect syntax\n");
		printf("After ' -d ' or ' -c ' or ' -o ' \n");
		printf("You should writh the files \n\n");
		return 0;
	}
	if(argc > 1){
		for (i = 1; i< argc-1;i++){
			err = 1;
			if( strcmp(argv[i],"-d") == 0 || strcmp(argv[i],"-c") == 0 || strcmp(argv[i],"-o") == 0){
				err = 0;
			}
		}
		if(err == 1){
			printf("Incorrect syntax\n");
			exit(0);
		}
	}
    for (i = 0; i< argc;i++){
		if(strcmp(argv[i],"-d") == 0){	
			j = i+1;
			strcpy(data,argv[j]);
			if( strcmp(argv[j],"-c") == 0 || strcmp(argv[j],"-o") == 0)
				return 0;
			flagd++;
		}
		else if(strcmp(argv[i],"-c") == 0){
			j = i+1;
			strcpy(config,argv[j]);
			if( strcmp(argv[j],"-d") == 0 || strcmp(argv[j],"-o") == 0)
				return 0;
			flagc++;
		}
		else if(strcmp(argv[i],"-o") == 0){
			j = i+1;
			strcpy(output,argv[j]);
			if( strcmp(argv[j],"-d") == 0 || strcmp(argv[j],"-c") == 0)
				return 0;
			flago++;
		}
	}
	//elegxoi
	if(flagd > 1 || flagc > 1 || flago > 1){
		printf("\nIncorrect syntax\n");
		printf("Correct syntax is: ./%s –d <input file> –c <configuration file> -o <output file>\n", argv[0]);
		printf("*You can change file sequence\n\n");
		exit(0);
	}
	if(flagd == 0){
		printf("Incorrect syntax! Insert data file\n");
		exit(2);
	}
	if(flagc == 0){
		printf("Incorrect syntax! Insert configuration file\n");
		exit(2);
	}
	if(flago == 0){
		strcpy(output,"\0");
		//OUT = fopen("Output.txt","w");
			//if(OUT == NULL){
			//	printf("Can not open output file\n");
			//	exit(0);
			//}
	}
	//else{
	//	OUT = fopen(output,"w");
	//	if(OUT == NULL){
	//			printf("Can not open output file\n");
	//			exit(0);
	//		}
	//}
		
	//ektiposi ti exei parei apo grammi
	//printf("k is %d L is %d\n",k,L);
	printf("data %s \n",data);
	printf("config %s \n",config);
	printf("output %s \n",output);
	if(flagd == 1){						//an exei dwsei data file (flag is 1) kai kalei tin antistoixi sinartisi
		infile = fopen(data,"r");
		if( infile == NULL){
			printf("Can not open Data file\n");
			exit(0);
		}
		fscanf(infile, "%s %s",XXX,type);			//euclidean
		if( strcmp(XXX,"@metric_space") != 0){
			printf("Error... Incorect data file\n");
			exit(0);
		}
		if( strcmp(type,"vector") == 0){			//DBH
			printf("\nvector\n");
			//VecMain(data,query,k,L);
		}
		else if(strcmp(type,"hamming") == 0){		//Hamming
			printf("hamming\n");
			//printf("%s\n",query);
		//	HamMain(data,query,k,L);
		}
		else if(strcmp(type,"matrix") == 0){
			printf("matrix\n");
			//MatMain(data,query,k,L);
		}
		else if(strcmp(type,"function") == 0){
			printf("function\n");
			//DynMain(data,query,k,L);			
		}
		else{
			printf("Error... Incorect data file\n");
			exit(0);
		}
		fclose(infile);
	}
	//fclose(OUT);
	return 0;
}
