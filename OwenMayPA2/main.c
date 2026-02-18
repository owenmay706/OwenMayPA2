#include "header.h"

int main(void) {
    //seeding rand
    srand((unsigned int)time(NULL));
	
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

    // menu goes here


   
    exitProgram(list, musicWrite, musicRead);
	return 1;
}