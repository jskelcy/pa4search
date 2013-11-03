#include "FreqList.h"

FreqList *FLCreate() {
	FreqList *list = malloc(1, sizeof(FreqList));
	list->first = NULL;
	list->last = NULL;
	return list;
}

void FLInsert(FreqList *list, char *filename, int count) {
	FreqNode *ptr;
	if (list == NULL || filename == NULL || filename[0] == '\0') {
		return;
	}
	ptr = malloc(1, sizeof(FreqNode));
	ptr->filename = filename;
	ptr->count = count;
	ptr->next = NULL;
	if (list->last == NULL) {
		list->first = ptr;
		list->last = ptr;
	} else {
		list->last->next = ptr;
		list->last = ptr;
	}
}

void FLDestroyFLNode(FreqNode *ptr) {
	if (ptr->next != NULL) {
		FLDestroyFLNode(ptr->next);
	}
	free(ptr->filename);
	free(ptr);
}

void FLDestroy(FreqList *list) {
	FLDestroyFLNode(list->first);
	free(list);
}
