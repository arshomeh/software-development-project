#ifndef __HASHFUNVEC_H__
#define __HASHFUNVEC_H__

#include "../headers.h"



struct euchash{
	eucnode *head;
	int count;
};

typedef struct euchash euchash;

struct heuc{
	double T;
	double *cordinate;
};

typedef struct heuc heuc;

struct geuc{
	heuc* Hfun;
	euchash* hash;
};
typedef struct geuc geuc;

extern  geuc *LTable;
extern int * R;
extern int elements ;//eleCount;
extern int EK;
extern int DIM;
extern int MM;
extern	FILE * ins;
extern tempnode *EUBestn;
extern int Distance;

/*hashing functions*/
/*************************/
int computehp(double w, double t, double* p, double* v);
/*************************/

eucnode * createEuNode(double * item,int id,int fid);
void loadEuHash(char * name,geuc * gtable);
void insertEuHash(tempnode * temp,geuc * gtable);
void displayEU(geuc * gtable);
void destroyEuc(geuc * gtable);
void searchEuHash(tempnode *temp,geuc * gtable,int Coun);
int hashfun(tempnode * item, geuc * gtable );

//////////////////////////
double compEucDist(double* p, double *v);
int searchEuin(tempnode * temp,geuc * gtable);
void BestEUnear(tempnode * temp,geuc * gtable);
void BestEUrad(tempnode * temp,int Coun,int radius);
void RealEUnear(tempnode * temp,geuc * gtable);

#endif
