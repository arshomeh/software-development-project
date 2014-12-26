#ifndef __MATHASH_H__
#define __MATHASH_H__

#include "../headers.h"

struct mathash{
	matnode *head;
	int count;
};

typedef struct mathash mathash;


struct matg{
	int gid;
	mathash* hash;
};
typedef struct matg matg;

extern  matg *Lmat;
extern int TableSize;
extern int Number;
extern int MK;
extern int BestMa;
extern int MatCounter;

/*****hashfunctions*************/

matnode * createMatNode(int id);
void loadMaHash(matg * gtable);
void Madisplay(matg * gtable);
void insertMaHash(int item,int *temp,matg * gtable);
int Mathashfun(int *item,matg * gtable);
void destroyMa(matg * gtable);

/////////////////////////
int FindNearN(int *item,matg * gtable);
void searchMaHash(int *item,matg * gtable,int Coun);
int BestMaRad(int *item,int Coun,int radius);

#endif
