#include "WordTree.h"

WordTree *WTCreate(char *filename) {
    FILE *fp = fopen(filename, "r");
    WordTree *tree;
	struct WORDNODE *root, *curr, *ptr, *next;
    char c;
	int i;
    if (fp == NULL) {
        fclose(fp);
        return NULL;
    }
    root = NULL;
    curr = NULL;
    ptr = NULL;
    next = NULL;
    tree = malloc(sizeof(WordTree));
    tree->root = treeInit();
    while ((c = fgetc(fp)) != EOF) {
        if (c == '<') {
            int length = 0, valid = 1;
            char *filename;
            /* get the next word */
            while ((c = fgetc(fp)) != '>');
            fgetc(fp);
            while ((c = fgetc(fp)) != '\n') {
                insertNode(tree->root, c);
            }
            fgetc(fp);
			if (tree->root->ptr->freak == NULL) {
	    		tree->root->ptr->freak = FLCreate();
			}
            /* start reading the filenames */
            while ((c = fgetc(fp)) != '<') {
                if (c == ' ' || c == '\n') {
                    if (length != 0) {
                        if (valid) {
                            /* create filename */
                            filename = malloc((length + 1) * sizeof(char));
                            ptr = root;
                            for (i = 0; i < length; i++) {
                                filename[i] = ptr->c;
                                ptr = ptr->next;
                            }
                            filename[length] = '\0';
                            FLInsert(tree->root->ptr->freak, filename);
                        }
                        valid ^= 1;
                        length = 0;
                        curr = root;
                    }
                } else {
                    /* build the string list */
                    if (curr == NULL) {
                        root = malloc(sizeof(struct WORDNODE));
                        curr = root;
                    }
                    curr->c = c;
	                if (curr != NULL && curr->next == NULL) {
    	            	curr->next = malloc(sizeof(struct WORDNODE));
        	        }
                    curr = curr->next;
                    length++;
                }
            }
			tree->root->ptr = tree->root->root;
            while ((c = fgetc(fp)) != '>');
        }
    }
    fclose(fp);
    for (ptr = root; ptr != NULL; ptr = next) {
        next = ptr->next;
        free(ptr);
    }
    tree->root->ptr = tree->root->root;
    return tree;
}

void WTTraverse(WordTree *tree, char c) {
	traverse(tree->root, c);
}

FreqNode *getFileNames(WordTree *tree) {
	FreqNode *list = tree->root->ptr->freak->first;
	tree->root->ptr = tree->root->root;
	return list;
}

void resetPointer(WordTree *tree) {
	tree->root->ptr = tree->root->root;
}

void WTDestroy(WordTree *tree) {
    freeTree(tree->root);
    free(tree);
}
