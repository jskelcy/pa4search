#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "WordTree.h"


void printFileNameTree(Node *printPtr, char *printString, int querySize, int printStringPtr){
    Node *nextNode;
    int i;
    if ((printPtr->isWord) && ((querySize > 0 && printPtr->count == querySize) || (printPtr->count > 0 && querySize == 0))){
        printString[printStringPtr] = printPtr->letter;
        printString[printStringPtr+1]= '\0';
        printf("%s ",printString);
        printStringPtr = 0;
    }
    if (printPtr->branches != NULL){
        for (i=0; i<38; i++){
            nextNode = printPtr->branches[i];
            if (nextNode != NULL){
                printString[printStringPtr] = nextNode->letter;
                printStringPtr++;
                printFileNameTree(nextNode, printString, querySize, printStringPtr);
            }
        }
    }
}

/*this method is probs does not free the pointer in each node*/
/*void freeTree(treeRoot *tree){
  if (tree->ptr->branches == NULL){
  free(tree->ptr);
  }
  }*/

int main(int argc, char *argv[]){
    int len =0, k;
    int searchFlag;
    char *printString;
    char c;
    int longLength =0;
    int querySize = 1;
    char *searchQuery = NULL;
    WordTree *wordTree;
    int i;

    if(argc !=2){
        printf("invalid input");
        return 1;
    }

    /* added by Tim */
    wordTree = WTCreate(argv[1]);
    /**/
    printf("please enter a search query\n");

    while( (c = getchar()) != 'q'){
        /*initialize the file tree*/
        treeRoot *fileTree = treeInit();
        if(c =='s'){
            /*loads query into memory*/
            while( (c = getchar()) != '\n'){
                searchQuery = realloc(searchQuery, len+1);
                searchQuery[len++] = c;
            }
            searchQuery = realloc(searchQuery, len+1);
            searchQuery[len] = '\n';
            /*sets flag for type of query*/
            if(searchQuery[0]=='a'){
                searchFlag=1;
            }
            if(searchQuery[0]=='o'){
                searchFlag=0;
            }
            /*builing the linked list of possible files names from wordTree*/
            for(i=2; searchQuery[i]!='\n';i++){
                printf("this letter we are searching for %x\n",searchQuery[i]);
                if(searchQuery[i]== ' ' || searchQuery[i]=='\n'){
                    FreqNode *treeBuilder;
                    querySize++;
                    treeBuilder = getFileNames(wordTree);
                    while(treeBuilder!= NULL){
                        for (k = 0; treeBuilder->filename[k] != '\0';k++){
                            insertNode(fileTree,treeBuilder->filename[k]);
                        }
                        if(k > longLength){
                            longLength = k;
                        }
                        fileTree->ptr->count++;
                        fileTree->ptr->isWord = 1;
                        printf("inserting: %s\n",treeBuilder->filename);
                        printf("the last letter of the word being inserted: %c, and the count: %d\n", fileTree->ptr->letter,fileTree->ptr->count);
                        fileTree->ptr = fileTree->root;
                        treeBuilder = treeBuilder->next;
                    }
                }else{
                    WTTraverse(wordTree,searchQuery[i]);
                }
            }
        }else{
            printf("bad input");
        }
        printString = (char *) malloc(longLength * sizeof(char));
        if(searchFlag != 1){
            querySize = 0;
        }
        /* redid this part for collapse code */
        printFileNameTree(fileTree->root, printString, querySize, 0);
        free(printString);
        freeTree(fileTree);
        printf("please enter a search query");
    }

    return 0;
}
