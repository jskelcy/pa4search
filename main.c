#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "WordTree.h"


void printFileNameTree(Node *printPtr, char *printString, int querySize, int printStringPtr){
    Node *nextNode;
    int i;
    if ((printPtr->isWord) && ((querySize > 0 && printPtr->count == querySize) || (querySize == 0))){
        printString[printStringPtr]= '\0';
        printf("%s\n",printString);
    }
    if (printPtr->branches != NULL){
        for (i=0; i<38; i++){
            nextNode = printPtr->branches[i];
            if (nextNode != NULL){
                printString[printStringPtr]=nextNode -> letter;
                printFileNameTree(nextNode, printString, querySize, printStringPtr + 1);
            }
        }
    }
}


int main(int argc, char *argv[]){
    int len =0, k;
    int searchFlag;
    char *printString;
    char c;
    int longLength =0;
    int querySize = 1;
    char *searchQuery = malloc(sizeof(char));
    WordTree *wordTree;
    int i;
    treeRoot *fileTree;

    if (argc !=2) {
        printf("invalid input");
        return 1;
    }

    /* added by Tim */
    wordTree = WTCreate(argv[1]);
    /**/
    printf("Search query: ");

    while ((c = getchar()) != 'q') {
        /*initialize the file tree*/
        fileTree = treeInit();
        if(c != 's'){
            freeTree(fileTree);
            fprintf(stderr, "bad input\n");
            while((c=getchar())!='\n'){}
            printf("Search query: ");
            continue;
        }
        if (c =='s' && ((c = getchar()) == 'a' || c == 'o')) {
            /* get search flag */
            searchFlag = c == 'a';
            if((c=getchar()) != ' ') {
                fprintf(stderr, "bad input\n");
                freeTree(fileTree);
                printf("Search query: ");
                continue;
            }
            /* load querysize (dump IOSTREAM) */
            while ((c = getchar()) != '\n') {
                searchQuery = realloc(searchQuery, len + 1);
                searchQuery[len++] = c;
            }
            searchQuery = realloc(searchQuery, len + 2);
            searchQuery[len++]= ' ';
            searchQuery[len] = '\0';
            if(strlen(searchQuery)<2){
                    fprintf(stderr, "bad input\n");
                    len = 0;
                    free(searchQuery);
                    freeTree(fileTree);
                    printf("Search query: ");
                    continue;
                }
            /*builing the linked list of possible files names from wordTree*/
            for (i = 0; searchQuery[i]!='\0'; i++) {
                if (searchQuery[i]== ' ') {
                    FreqNode *treeBuilder;
                    querySize++;
                    treeBuilder = getFileNames(wordTree);
                    while (treeBuilder!= NULL) {
                        for (k = 0; treeBuilder->filename[k] != '\0';k++){
                            insertNode(fileTree,treeBuilder->filename[k]);
                        }
                        if (k > longLength) {
                            longLength = k;
                        }
                        fileTree->ptr->count++;
                        fileTree->ptr->isWord = 1;
                        fileTree->ptr = fileTree->root;
                        treeBuilder = treeBuilder->next;
                    }
                } else {
                    WTTraverse(wordTree,searchQuery[i]);
                    if (wordTree->root->ptr == NULL) {
                        fprintf(stderr, "Invalid request.\n");
                        resetPointer(wordTree);
                        break;
                    }
                }
            }
            free(searchQuery);
            len = 0;
            searchQuery = malloc(sizeof(char));
        } else {
            printf("bad input");
        }
        querySize--;
        printString = (char *) malloc((longLength+1) * sizeof(char));
        if (searchFlag != 1) {
            querySize = 0;
        }
        printFileNameTree(fileTree->root, printString, querySize, 0);
        free(printString);
        freeTree(fileTree);
        longLength = 0;
        printf("\nSearch query: ");
    }
    free(searchQuery);
    WTDestroy(wordTree);
    return 0;
}
