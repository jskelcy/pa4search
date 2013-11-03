#include "prefixTree.h"

int hash(char c) {
    if ('0' <= c && c <= '9') {
        return (c - '0');
    } else if ('a' <= c && c <= 'z') {
        return (c - 'a' + 10);
    } else if ('A' <= c && c <= 'Z') {
        return (c - 'A' + 10);
    } else {
        return -1;
    }
}

treeRoot* treeInit() {
    treeRoot *returnTree = (treeRoot *) calloc (1, sizeof(treeRoot));
    returnTree->root = (Node *) calloc(1, sizeof(Node));
    returnTree->ptr = returnTree->root;
    return returnTree;
}

void insertNode(treeRoot *tree,char c) {
    int index = hash(c);
    if (index == -1) {
        return;
    }
    if (tree->ptr->branches == NULL) {
        tree->ptr->branches = (Node **) calloc(36, sizeof(Node*));
    }
    if (tree->ptr->branches[index] == NULL) {
        tree->ptr->branches[index] = (Node *) calloc(1, sizeof(Node));
        tree->ptr->branches[index]->letter = tolower(c);
        tree->ptr = tree->ptr->branches[index];
    } else {
        tree->ptr = tree->ptr->branches[index];
    }
}

void traverse(treeRoot *tree, char c){
    int index = hash(c);
    tree->ptr = tree->ptr->branches[index];
}

void freeBranches(Node *curr) {
    int i;
    if (curr->branches != NULL) {
        for (i = 0; i < 36; i++) {
            if (curr->branches[i] != NULL) {
                freeBranches(curr->branches[i]);
            }
        }
        free(curr->branches);
    }
    if (curr->freak != NULL) {
        FLDestroy(curr->freak);
    }
    free(curr);
}

void freeList(FilenameNode *curr) {
    if (curr != NULL) {
        freeList(curr->next);
        if (curr->filename != NULL) {
            free(curr->filename);
        }
        free(curr);
    }
}

void freeTree(treeRoot *tree) {
    freeBranches(tree->root);
    freeList(tree->filenames);
    free(tree);
}

char *append(char *s, char c) {
    char *copy;
    int i, length;
    if(s == NULL){
        copy = (char *) malloc(sizeof(char)*2);
        copy[0]= c;
        copy[1]= '\0';
        return copy;
    }
    length = strlen(s);
    copy = (char *)malloc(length+2);
    for(i=0; i<length; i++){
        copy[i]=s[i];
    }
    copy[length]= c;
    copy[length + 1] ='\0';
    return copy;
}
