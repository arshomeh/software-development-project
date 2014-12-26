#ifndef __HASHFUN_H__
#define __HASHFUN_H__

#include "../headers.h"

struct hashnode{
	hamnode *head;
	int count;
};

typedef struct hashnode hashnode;

struct gtype{
	char* digi;
	hashnode* hash;
};
typedef struct gtype gtype;
extern  gtype *gtypeTable;
extern int eleCount;
extern int K;
extern hamnodeins *Bestn;
extern int Distance;

/*hashing functions*/
hamnode * createNode(char *bits,int id);
void loadToHash(char * name,gtype * gtable);
void insertToHash(hamnodeins * temp,gtype * gtable);
void destroyHam(gtype * gtable);
void deleteFromHash(char *bits,gtype * gtable);
void searchInHash(char *bits,gtype * gtable,int Coun);
void display(gtype * gtable);
/*****************************************/
int HammingDistance(char* a, int na, char* b);
int searchInner(char *binary,gtype * gtable);
void Bestrad(char* binary,int Coun,int radius);
#endif
