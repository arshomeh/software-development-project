#ifndef __MATREC_H__
#define __MATREC_H__

#include "../headers.h"

#define BIG 12000

struct matnode{
	int id;
	struct matnode * next;
};
typedef struct matnode matnode;


extern int *nearmat;
extern int ***pinakasx1x2;//[L][K][2]; //pinakas gia x1x2 toy kathe h
extern 	double **pinakast;//[L][K]; //pinakas gia tmed toy kathe h
extern	int **apostaseis;//[N][N]; //pinakas apostaseon. ego ton dimioyrgo esi tha ton diabazeis


#endif
