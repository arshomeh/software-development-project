#include <stdio.h>
#include <stdlib.h>

#include "headers.h"

int main (int argc, char** argv){  //Tha einai tis morfis: ./medoids –d <input file> –c <configuration file> -o <output file>
	struct timeval time;
	gettimeofday(&time, NULL);
	srand((time.tv_sec*1000)+(time.tv_usec/1000));
  	int i,j;
    int flagd, flagc, flago,flagcomp;
    char 	data[SIZEofBUFF];
	char 	config[SIZEofBUFF];
	char	output[SIZEofBUFF];
	int err = 0;
	flagd = flagc = flago = flagcomp = 0;
	
	/* diavasma parametron */
	/*if (argc%2 == 0){
		printf("\nIncorrect syntax\n");
		printf("After ' -d ' or ' -c ' or ' -o ' \n");
		printf("You should writh the files \n\n");
		return 0;
	}*/
	if(argc > 1){
		if(argc%2 == 0){
			for (i = 1; i< argc;i++){
				err = 1;
				if( strcmp(argv[i],"-d") == 0 || strcmp(argv[i],"-c") == 0 || strcmp(argv[i],"-o") == 0 || strcmp(argv[i],"-complete") == 0){
					err = 0;
				}
			}
		}
		else if(argc%2 != 0){
			for (i = 1; i< argc-1;i++){
				err = 1;
				if( strcmp(argv[i],"-d") == 0 || strcmp(argv[i],"-c") == 0 || strcmp(argv[i],"-o") == 0){
					err = 0;
				}
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
			if( strcmp(argv[j],"-c") == 0 || strcmp(argv[j],"-o" ) == 0 || strcmp(argv[j],"-complete") == 0)
				return 0;
			flagd++;
		}
		else if(strcmp(argv[i],"-c") == 0){
			j = i+1;
			strcpy(config,argv[j]);
			if( strcmp(argv[j],"-d") == 0 || strcmp(argv[j],"-o") == 0 || strcmp(argv[j],"-complete") == 0)
				return 0;
			flagc++;
		}
		else if(strcmp(argv[i],"-o") == 0){
			j = i+1;
			strcpy(output,argv[j]);
			if( strcmp(argv[j],"-d") == 0 || strcmp(argv[j],"-c") == 0 || strcmp(argv[i],"-complete") == 0)
				return 0;
			flago++;
		}
		else if(strcmp(argv[i],"-complete") == 0){
			//j = i+1;
			//if( strcmp(argv[j],"-d") == 0 || strcmp(argv[j],"-c") == 0 || strcmp(argv[i],"-o") == 0)
				//return 0;
			flagcomp++;
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
		strcpy(output,"Output.txt");
	}	


	printf("data %s \n",data);
	printf("config %s \n",config);
	printf("output %s \n",output);
	printf("complete %d \n",flagcomp);
	int flag;
	if(flagd == 1){
		flag = readData(data,config);
	}
	if(flag == 1){
		//hamming
		printf("lala\n");
		hamMain(data,config,output,flag,flagcomp);
	}
	else if(flag == 2){
		//euclidean
		eucMain(data,config,output,flag,flagcomp);
	}
	else if(flag == 3){
		//matrix
		matMain(data,config,output,flag,flagcomp);
	}
	//fclose(OUT);
	return 0;
}
