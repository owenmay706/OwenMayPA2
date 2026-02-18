#include "header.h"

void play1_song(Node* pList) {
    print_current(pList);
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".\n");
    Sleep(500);
    printf("Finished Playing\n");
}

void playAllSong(Node* pList) {

    Node* current = pList;
    while (current != NULL) {
        system("cls");
        play1_song(current);
        current = current->next;
    }

    printf("All Songs Played\n");

}

void shuffle(Node* pList) {
    if (pList == NULL) {
        printf("No songs to play.\n");
        return;
    }
    int count = 0;
    Node* temp = pList;
    while (temp) {
        count++;
        temp = temp->next;
    }

    if (count == 0) return;

    Node** songs = malloc(count * sizeof(Node*));
    if (songs == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    int i = 0;
    temp = pList;
    while (temp) {
        songs[i++] = temp;
        temp = temp->next;
    }


    for (int j = count - 1; j > 0; j--) {
        int k = rand() % (j + 1);
        // swap
        Node* temp_ptr = songs[j];
        songs[j] = songs[k];
        songs[k] = temp_ptr;
    }

    system("cls");
    printf("Playing library in shuffled order...\n\n");

    for (int j = 0; j < count; j++) {
        system("cls");
        play1_song(songs[j]);
        Sleep(500);
    }

    free(songs);
    printf("\nFinished shuffled playlist!\n");

    free(songs);
    printf("\nFinished shuffled playlist!\n");
}