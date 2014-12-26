#include <stdio.h>
#include <stdlib.h>

#include "headers.h"


int main(int argc,char** argv){

	int i,Coun;
	int* query;
	int rad = 3;
	query = malloc(500* sizeof(int));
	MatMain("matrix.csv",4,5);
	for(i = 0;i< 500;i++)
		query[i] = i;
	Coun = Matquery(query,4,5,rad);
	/*for(i = 0;i<Coun;i++){
		if(nearmat[i] != -1){
			if(query[nearmat[i]] < rad){
				printf("ItemId ->%d\n",nearmat[i]+1);
			}
		}
	}*/
	char binary[65];
	strcpy(binary,"1000010111111011111011010010010010010111000010110101111111001111");
	HamMain("hamming.csv",4,5);
	for(i = 0;i< 500;i++)
		query[i] = i;
	//Coun = Hamquery(binary,4,5,6);
	double euc[500];
	for(i= 0 ;i< 500;i++){
		euc[i] = (double)i/10;
	}
	VecMain("euc.csv",4,5);
	Coun = Eucquery(euc,4,5,10000000);

	free(nearmat);
	nearmat = NULL;
	return 0;
}
