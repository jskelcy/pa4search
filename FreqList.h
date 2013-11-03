#ifndef __FreqList_h__
#define __FreqList_h__
#include <stdlib.h>

typedef struct FreqList FreqList;
typedef struct FreqNode FreqNode;
struct FreqList {
	FreqNode *first, *last;
};
struct FreqNode {
	char *filename;
	FreqNode *next;
};
FreqList *FLCreate();
void FLInsert(FreqList *, char *);
void FLDestroy(FreqList *);

#endif
