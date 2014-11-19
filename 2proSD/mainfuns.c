#include "headers.h"

configuration setConfig(char* config){
	FILE* fp;
	configuration c;
	char ch;
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
				if(strcmp(temp,"number_of_clusters:"))
					c.Clasters = atoi(number);
				if(strcmp(temp,"number_of_hash_functions:"))
					c.HashFunctions = atoi(number);
				if(strcmp(temp,"number_of_hash_tables:"))
					c.HashTables = atoi(number);
				if(strcmp(temp,"clarans_set_fraction:"))
					c.ClaransFraction = atoi(number);
				if(strcmp(temp,"clarans_iterations:"))
					c.ClaransIterations = atoi(number);
			}
			strcpy(temp,"");
			strcpy(number,"");
		}
		sprintf(str,"%c",ch);
		strcat(temp,str);
		flag = 0;
	}
	if(c.HashFunctions == -1)
		c.HashFunctions = 4;
	if(c.HashTables == -1)
		c.HashTables = 5;
	if(c.ClaransFraction == -1)
		c.ClaransFraction = c.Clasters;
	if(c.ClaransIterations == -1)
		c.ClaransIterations = 2;
	return c;
}
