#ifndef __MYRECORDS_H__
#define __MYRECORDS_H__

#include "../headers.h"

#define BITS 65
#define SIZE 65
#define LINE 100
#define LG 5
#define GK 4
#define SIZEofBUFF 20

/*node tipe for hamming*/

struct hamnode{
	int id;
	char binary [BITS];
	struct hamnode * next;
};
typedef struct hamnode hamnode;

struct hamnodeins{
	int id;
	char binary [BITS];
};
typedef struct hamnodeins hamnodeins;
 
extern hamnodeins *nearn;
extern int HamCount;

#endif
