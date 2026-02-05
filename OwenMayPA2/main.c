#include "header.h"

int main(void) {
	
    FILE* musicRead = fopen("musicPlayList.csv", "r");
    if (musicRead == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    Node* list = NULL;
    if (loadData(&list, musicRead)) {
        printf("Loaded successfully\n");
    }

    printList(list);

    fclose(musicRead);

	return 1;
}