#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "prefixTree.h"

int main(int argc, char *argv[]){
    int len =0;
    int searchFlag;
    char *ch;
    char c;
    int querySize = 1;
    char *searchQuery = NULL;

    if(argc !=2){
        printf("invalid input");
        return 1;
    }

    printf("please enter a search query");

    while( (c = getchar()) != 'q'){
        treeRoot *fileTree = treeInit();
        if(c =='s'){
            //loads query into memory
            while( (c = getchar()) != '\n'){
            searchQuery = realloc(searchQuery, len+1);
            searchQuery[len++] = c;
            }
            searchQuery[len] = '\n';

            //sets flag for type of query
            if(searchQuery[0]=='a'){
                searchFlag=1;
            }
            if(searchQuery[0]=='o'){
                searchFlag=0;
            }
            for(int i=1; searchQuery[i]!='\n';i++){
                if(searchQuery[i]= ' '){
                    querySize++;
                    void *treeBuilder = getFileNames(WordTree);

                    while(treeBuilder!= NULL){
                        for (int k = 0; treeBuilder->fileName[k] != '\0'){
                            insertNode(fileTree,treeBuilder->fileName[k]);
                        }
                        fileTree->ptr->count++;
                        fileTree->ptr = fileTree->root
                        treeBuilder = treeBuilder->next;
                    }

                    WordTree->ptr = WordTree->root;
                }else{
                    traverse(WordTree,searchQuery[i]);
                }
            }
        }else{
            printf("bad input");
        }
    printf("please enter a search query");
    }
    return 0;
}
