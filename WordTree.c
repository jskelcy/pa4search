#include "WordTree.h"

WordTree *WTCreate(char *filename) {
    FILE *fp = fopen(filename, "r");
    WordTree *tree;
    struct WORDNODE *root = NULL, *curr = NULL, *ptr, *next;
    char c;
    if (fp == NULL) {
        fclose(fp);
        return NULL;
    }
    tree = malloc(sizeof(WordTree));
    tree->root = treeInit();
	puts("STEP 1");
    while ((c = fgetc(fp)) != EOF) {
        if (c == '<') {
            int length = 0, valid = 1, count = 0;
            char *filename;
            /* get the next word */
			puts("WORD:");
            while ((c = fgetc(fp)) != '>');
            fgetc(fp);
            while ((c = fgetc(fp)) != '\n') {
				printf("%c", c);
                insertNode(tree->root, c);
            }
            fgetc(fp);
			printf("\n");
    		tree->root->ptr->freak = FLCreate();
            /* start reading the filenames */
            while ((c = fgetc(fp)) != '<') {
				puts("READCHAR");
                if (c == ' ' || c == '\n') {
                    if (length != 0) {
                        if (valid) {
                    		int i;
                            /* create filename */
                            filename = malloc((length + 1) * sizeof(char));
                            ptr = root;
                            for (i = 0; i < length; i++) {
                                filename[i] = ptr->c;
								printf("asdfaf: %c\n", ptr->c);
                                ptr = ptr->next;
                            }
                            filename[length] = '\0';
                            FLInsert(tree->root->ptr->freak, filename);
							printf("FILENAME: %s, %d\n", filename, length);
							printf("INSERTED: %s\n", tree->root->ptr->freak->last->filename);
                        }
                        valid ^= 1;
                        length = 0;
                        curr = root;
                    }
                } else {
                    /* build the string list */
					if (valid) {
						printf("BUILD STRING LIST: %c\n", c);
					}
                    if (curr == NULL) {
                        root = malloc(sizeof(struct WORDNODE));
                        curr = root;
                    } else {
                        if (curr != NULL && curr->next == NULL) {
                            curr->next = malloc(sizeof(struct WORDNODE));
                        }
                        curr = curr->next;
                    }
                    curr->c = c;
					printf("%lx\n", (long)curr);
                    length++;
                }
            }
            while ((c = fgetc(fp)) != '>');
			tree->root->ptr = tree->root->root;
        }
    }
	/* garbage collect */
	puts("GARBAGE COLLECT");
    fclose(fp);
    for (ptr = root; ptr != NULL; ptr = next) {
        next = ptr->next;
        free(ptr);
    }
    return tree;
}

void WTTraverse(WordTree *tree, char c) {
	traverse(tree->root, c);
}

FreqNode *getFileNames(WordTree *tree) {
	FreqNode *list = tree->root->ptr->freak->first;
	tree->root->ptr = NULL;
	return list;
}

void WTDestroy(WordTree *tree) {
    freeTree(tree->root);
    free(tree);
}
