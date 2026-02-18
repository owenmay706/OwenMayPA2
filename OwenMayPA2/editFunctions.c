#include "header.h"

int rateSong(Node** pList) {

    Node* current = FindSongTitle(*pList);

    if (current == NULL) {
        printf("Song not found.\n");
        return 0;
    }

    // get valid rating
    do {
        printf("Enter rating (1-5): ");
        if (scanf("%d", &current->data.rating) != 1) {
            printf("Please enter a number.\n");
            current->data.rating = 0;
        }

        while (getchar() != '\n');

    } while (current->data.rating < 1 || current->data.rating > 5);

    return 1;
}

int deleteSong(Node** pList) {
    Node* current = FindSongTitle(*pList);

    if (current == NULL) {
        printf("Song not found.\n");
        return 0;
    }

    //removing song 
    if (current->prev == NULL) {
        *pList = current->next;

        if (current->next != NULL) {
            current->next->prev = NULL;
        }
    }
    else {
        current->prev->next = current->next;

        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
    }

    free(current);
    return 1;
}

void editSong(Node** pList) {
    Node* current = FindSongTitle(*pList);

    if (current == NULL) {
        printf("Song not found.\n");
        return;
    }

    int minutes, seconds;
    int valid = 0;

    // artist
    printf("Enter artist name: ");
    fgets(current->data.artist, sizeof(current->data.artist), stdin);
    current->data.artist[strcspn(current->data.artist, "\n")] = '\0';

    // album
    printf("Enter album name: ");
    fgets(current->data.album, sizeof(current->data.album), stdin);
    current->data.album[strcspn(current->data.album, "\n")] = '\0';

    // title
    printf("Enter song title: ");
    fgets(current->data.title, sizeof(current->data.title), stdin);
    current->data.title[strcspn(current->data.title, "\n")] = '\0';

    // genre
    printf("Enter genre: ");
    fgets(current->data.genre, sizeof(current->data.genre), stdin);
    current->data.genre[strcspn(current->data.genre, "\n")] = '\0';

    // song length (mm:ss)
    do {
        printf("Enter song length (mm:ss): ");
        if (scanf("%d:%d", &minutes, &seconds) != 2) {
            printf("Invalid format. Use mm:ss\n");
        }
        else if (minutes < 0 || seconds < 0 || seconds > 59) {
            printf("Invalid time value.\n");
        }
        else {
            valid = 1;
            current->data.length.minutes = minutes;
            current->data.length.seconds = seconds;
        }
        while (getchar() != '\n');  // clear input buffer
    } while (!valid);

    // times played
    valid = 0;
    do {
        printf("Enter times played: ");
        if (scanf("%d", &current->data.times_played) != 1) {
            printf("Please enter a valid integer.\n");
        }
        else if (current->data.times_played < 0) {
            printf("Times played cannot be negative.\n");
        }
        else {
            valid = 1;
        }
        while (getchar() != '\n');
    } while (!valid);

    // rating (1–5)
    do {
        printf("Enter rating (1-5): ");
        if (scanf("%d", &current->data.rating) != 1) {
            printf("Please enter a number.\n");
            current->data.rating = 0;
        }
        while (getchar() != '\n');
    } while (current->data.rating < 1 || current->data.rating > 5);

}

//functions for sorting and swapping
void swapRecords(Record* a, Record* b) {
    Record temp = *a;
    *a = *b;
    *b = temp;
}

void sortByTitle(Node* pList) {
    if (pList == NULL) {
        printf("List is empty.\n");
        return;
    }

    int swapped;
    Node* current;
    Node* lastSorted = NULL;

    do {
        swapped = 0;
        current = pList;

        while (current->next != lastSorted) {
            if (strcmp(current->data.title, current->next->data.title) > 0) {
                swapRecords(&current->data, &current->next->data);
                swapped = 1;
            }
            current = current->next;
        }

        lastSorted = current;

    } while (swapped);

    printf("List sorted alphabetically by title.\n");
}

