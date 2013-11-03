#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "FreqList.h"

typedef struct FilenameNode {
	char *filename;
	struct FilenameNode *next;
} FilenameNode;

typedef struct treeRoot{
   struct Node *root;
   struct Node *ptr;
   FilenameNode *filenames;
   int depth;
} treeRoot;

typedef struct Node{
    char letter;
    struct Node** branches;
    struct FreqList *freak;
    char isWord;
    int count;
} Node;

treeRoot *treeInit();
void traverse(treeRoot *tree,char c);
void insertNode(treeRoot *tree, char c);
void freeTree(treeRoot *tree);
char *append(char *s, char c);
