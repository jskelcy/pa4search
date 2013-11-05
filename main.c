#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "WordTree.h"


void printFileNameTree(Node *printPtr, char *printString, int querySize, int printStringPtr){
	Node *nextNode;
	int i;
	puts(printString);
	if ((printPtr->isWord) && ((querySize > 0 && printPtr->count == querySize) || (querySize == 0 && printPtr->count > 0))){
		printString[printStringPtr] = printPtr->letter;
		printString[printStringPtr+1]= '\0';
		printf("%s\n",printString);
		printStringPtr = 0;
	}
	if (printPtr->branches != NULL){
		for (i=0; i<38; i++){
			nextNode = printPtr->branches[i];
			if (nextNode != NULL){
				puts("hello2");
				printString[printStringPtr]=nextNode -> letter;
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
	char *searchQuery = malloc(sizeof(char));
	WordTree *wordTree;
	int i;

	if (argc !=2) {
		printf("invalid input");
		return 1;
	}

	/* added by Tim */
	wordTree = WTCreate(argv[1]);
	/**/
	printf("\ntree->root: %lx\n\n", (long)wordTree->root->root);
	printf("Search query: ");

	while ((c = getchar()) != 'q') {
		/*initialize the file tree*/
		treeRoot *fileTree = treeInit();
		if (c =='s' && ((c = getchar()) == 'a' || c == 'o')) {
			/* get search flag */
			searchFlag = c == 'a';
			getchar();
			printf("Search flag: %s\n", searchFlag ? "and" : "or");
			/* load query (dump IOSTREAM) */
			while ((c = getchar()) != '\n') {
				searchQuery = realloc(searchQuery, len + 1);
				searchQuery[len++] = c;
			}
			searchQuery = realloc(searchQuery, len + 2);
			searchQuery[len++] = ' ';
			searchQuery[len] = '\0';
			printf("Query loaded: %s, %d, %lx\n", searchQuery, len, (long)wordTree->root->ptr);
			/*builing the linked list of possible files names from wordTree*/
			for (i = 0; searchQuery[i]!='\0'; i++) {
				if (searchQuery[i]== ' ') {
					FreqNode *treeBuilder;
					querySize++;
					treeBuilder = getFileNames(wordTree);
					printf("WordTree ptr: %lx\n", (long)wordTree->root->ptr);
					while (treeBuilder!= NULL) {
						for (k = 0; treeBuilder->filename[k] != '\0';k++){
							insertNode(fileTree,treeBuilder->filename[k]);
						}
						printf("Insert to FilenameTree: %s, %lx", treeBuilder->filename, (long)wordTree->root->ptr);
						if (k > longLength) {
							longLength = k;
						}
						fileTree->ptr->count++;
						printf("count: %d\n",fileTree->ptr->count);
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
		puts("Now printing...");
		printString = (char *) malloc(longLength * sizeof(char));
		if (searchFlag != 1) {
			querySize = 0;
		}
		printFileNameTree(fileTree->root, printString, querySize, 0);
		free(printString);
		freeTree(fileTree);
		longLength = 0;
		printf("\nSearch query: ");
	}
	WTDestroy(wordTree);
	return 0;
}
