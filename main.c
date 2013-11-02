#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "WordTree.h"


void printFileNameTree(treeRoot *printTree, char *printString, int querySize, int printStringPtr){
	printTree->ptr = printTree->root;
	Node *nextNode;
	int i;
	if ((printTree->ptr->isWord) && ((querySize > 0 && printTree->ptr->count == querySize) || (printTree->ptr->count > 0))){
		printString[printStringPtr] = printTree->ptr->letter;
		printString[printStringPtr+1]= '\0';
		printf("%s ",printString);
		printStringPtr = 0;
		printTree->ptr = printTree->root;
	}
	if (printTree->ptr->branches != NULL){
		for (i=0; i<37; i++){
			nextNode = printTree->ptr->branches[i];
			if (nextNode != NULL){
				printString[printStringPtr]=nextNode -> letter;
				printStringPtr++;
				printTree->ptr = nextNode;
				printFileNameTree(printTree, printString, querySize, printStringPtr);
			}
		}
	}
}

/*this method is probs does not free the pointer in each node*/
/*void freeTree(treeRoot *freeTree){
	if (freeTree->ptr->branches == NULL){
		free(prefixTree->ptr);
	}
}*/

int main(int argc, char *argv[]){
	int len =0, k, i;
	int searchFlag;
	char *ch;
	char c;
	int longLength =0;
	int querySize = 1;
	char *searchQuery = NULL;

	if(argc !=2){
		printf("invalid input");
		return 1;
	}

	/* added by Tim */
	WordTree *wordTree = WTCreate(argv[1]);
	return 0;
	/**/
	printf("please enter a search query");

	while( (c = getchar()) != 'q'){
		/*initialize the file tree*/
		treeRoot *fileTree = treeInit();
		if(c =='s'){
			/*loads query into memory*/
			while( (c = getchar()) != '\n'){
				searchQuery = realloc(searchQuery, len+1);
				searchQuery[len++] = c;
			}
			searchQuery[len] = '\n';
			/*sets flag for type of query*/
			if(searchQuery[0]=='a'){
				searchFlag=1;
			}
			if(searchQuery[0]=='o'){
				searchFlag=0;
			}
			/*builing the linked list of possible files names from wordTree*/
			for(i=1; searchQuery[i]!='\n';i++){
				if(searchQuery[i]= ' '){
					querySize++;
					FreqNode *treeBuilder = getFileNames(wordTree);
					while(treeBuilder!= NULL){
						for (k = 0; treeBuilder->filename[k] != '\0';k++){
							insertNode(fileTree,treeBuilder->filename[k]);
						}
						if(k > longLength){
							longLength = k;
						}
						fileTree->ptr->count++;
						fileTree->ptr->isWord = 1;
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
		char *printString = (char *) malloc(longLength * sizeof(char));
		if(searchFlag != 1){
			querySize = 0;
		}
		/* redid this part for collapse code */
		printFileNameTree(fileTree, printString, querySize, 0);
		free(printString);
		freeTree(fileTree);
		printf("please enter a search query");
	}

	return 0;
}
