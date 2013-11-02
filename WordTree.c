WordTree *WTCreate(char *filename) {
    FILE *fp = fopen(filename, "r");
    WordTree *tree;
    WORDNODE *root, *curr, *ptr, *next;
    char c;
    if (fp == NULL) {
        fclose(fp);
        return NULL;
    }
    tree = malloc(sizeof(WordTree));
    tree->root = treeInit();
    tree->root->freak = FLCreate();
    while ((c = fgetc(fp)) != EOF) {
        if (c == '<') {
            int length = 0, state, count;
            char *filename;
            /* get the next word */
            while ((c = fgetc(fp)) != '>');
            fgetc(fp);
            while ((c = fgetc(fp)) != '\n') {
                insertNode(tree->root, c);
            }
            fgetc(fp);
            /* start reading the filenames */
            while ((c = fgetc(fp)) != '<') {
                if (c == ' ' || c == '\n') {
                    int i;
                    if (length != 0) {
                        if (state == 0) {
                            /* create filename */
                            filename = malloc((length + 1) * sizeof(char));
                            ptr = root;
                            for (i = 0; i < length; i++) {
                                filename[i] = ptr->c;
                                ptr = ptr->next;
                            }
                            filename[length] = '\0';
                        } else {
                            /* create count and insert */
                            count = 0;
                            for (ptr = root; ptr != NULL; ptr = ptr->next) {
                                count *= 10;
                                count += (ptr->c) - '0';
                            }
                            FLInsert(tree->root->freak, filename, count);
                        }
                        state ^= 1;
                        length = 0;
                        curr = root;
                    }
                } else {
                    /* build the string list */
                    if (root == NULL) {
                        root = malloc(1, sizeof(WORDNODE));
                        curr = root;
                    } else {
                        if (curr->next == NULL) {
                            curr->next = malloc(1, sizeof(WORDNODE));
                        }
                        curr = curr->next;
                    }
                    curr->c = c;
                    length++;
                }
            }
            while ((c = fgetc(fp)) != '>');
        }
    }
    fclose(fp);
    for (ptr = root; ptr != NULL; ptr = next) {
        next = ptr->next;
        free(ptr);
    }
    return tree;
}

void traverse(WordTree *tree, char c) {
	traverse(tree->root, c);
}

FreqNode *getFileNames(WordTree *tree) {
	FreqNode *list = tree->root->ptr->freak->first;
	tree->root->ptr = NULL;
	return list;
}

void WTDestroy(WordTree *tree) {
    freeTree(tree);
    free(tree);
}
