#ifndef __VECREC_H__
#define __VECREC_H__

#include "../headers.h"

#define NDIV 2
#define W 4
#define M 2147483642 //2^32 - 5
#define SIZEEU 2000
/*node type for euclidean*/


struct eucnode{
	int id;
	int fid;
	double *cordinate; 
	struct eucnode* next;
};
typedef struct eucnode eucnode;

struct tempnode{
	int id;
	int fid;
	double *cordinate; 
};

typedef struct tempnode tempnode;


extern tempnode *eunear;
extern int EUcounter;






#endif
