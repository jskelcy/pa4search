#ifndef __WordTree_h__
#define __WordTree_h__
#include "prefixTree.h"
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
FreqNode *getFileNames(WordTree *tree);
void WTTraverse(WordTree *, char);
void WTDestroy(WordTree *tree);

#endif
