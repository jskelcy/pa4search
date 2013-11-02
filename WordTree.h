#ifndef __WordTree_h__
#define __WordTree_h__
#include "FreqList.h"
#include "prefixTree.c"
#include <stdio.h>
#include <stdlib.h>

typedef struct WordTree WordTree;
struct WordTree {
	treeRoot *root;
};

struct WORDNODE {
	char c;
	struct WORDNODE *next;
};

WordTree *WTCreate(char *);
FreqNode *getFileNames(WordTree *tree, char *);
void traverse(WordTree *, char);
void WTDestroy(WordTree *tree);

#endif
