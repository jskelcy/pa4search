#ifndef __FreqList_h__
#define __FreqList_h__
#include <stdlib.h>

typedef struct FreqList FreqList;
struct FreqList {
	FreqNode *first, *last;
};
typedef struct FreqNode FreqNode;
struct FreqNode {
	char *filename;
	int count;
	FreqNode *next;
};
FreqList *FLCreate();
void FLInsert(FreqList *, char *, int);
void FLDestroy(FreqList *);

#endif
