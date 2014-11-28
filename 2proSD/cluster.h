#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include "headers.h"



struct item{
	int itemid;
	struct item *next;
};
typedef struct item item;

struct cluster{
	int medid;
	double sumdist;
	int idcount;
	item *head;
	double s;
};
typedef struct cluster cluster;

item *CreateItem(struct item *);
item *InsertItem(struct item *, int);
item *DeleteItem(struct item *, int);
int	IsMemberOfList(item *, int);


#endif
