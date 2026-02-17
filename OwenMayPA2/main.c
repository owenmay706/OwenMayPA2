#include "header.h"

int main(void) {
	
    //opening files
    FILE* musicRead = fopen("musicPlayList.csv", "r");
    if (musicRead == NULL) {
        printf("Failed to open file\n");
        return 1;
    }


    Node* list = NULL;
    if (loadData(&list, musicRead)) {
        printf("Loaded successfully\n");
    } 

    FILE* musicWrite = fopen("musicPlayList.csv", "w");

    //promptForRecord(&list);


    play1_song(list);
    //leaving program
    exitProgram(list, musicWrite, musicRead);
	return 1;
}