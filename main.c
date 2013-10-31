#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "prefixTree.h"

int main(int argc, char *argv[]){
    int len =0;
    char *ch;
    char c;
    char *searchQuery = NULL;

    if(argc !=2){
        printf("invalid input");
        return 1;
    }

    printf("please enter a search query");

    /*allows storge of string of indeterminate length*/
    while( (c = getchar()) != 'q'){
        if(c =='s'){
            while( (c = getchar()) != '\n'){
            searchQuery = realloc(searchQuery, len+1);
            searchQuery[len++] = c;
            }










        }else{
            printf("bad input");
        }
    printf("please enter a search query");
    }
    searchQuery[len] = '\n';
    printf("%s", searchQuery);
    return 0;
}
