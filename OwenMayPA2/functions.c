#include "header.h"

void printList(Node* pList) {
    Node* current = pList;
    int count = 1;

    if (pList == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("=========================================\n");
    printf("         MUSIC LIBRARY\n");
    printf("=========================================\n\n");

    while (current != NULL) {
        print_current(current);
        current = current->next;
        count++;
    }

    printf("\nTotal records: %d\n", count - 1);
}

void printAsk(Node* pList) {
    Node* current = pList;
    int count = 1;
    char artist[100];


    if (pList == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Enter artist name: ");
    fgets(artist, sizeof(artist), stdin);
    artist[strcspn(artist, "\n")] = '\0';

    printf("=========================================\n");
    printf("         MUSIC LIBRARY\n");
    printf("=========================================\n\n");

    while (current != NULL) {
        if (strcmp(current->data.artist, artist) == 0) {
            print_current(current);
        }
        current = current->next;
        count++;
    }

    printf("\nTotal records: %d\n", count - 1);
}

void exitProgram(Node** pList, FILE* output) {
    storeData(*pList, output);
    if (output != NULL) {
        fclose(output);
    }
  
    destroyList(pList);
}

void promptForRecord(Node** pList)
{
    Record r;
    int minutes, seconds;
    int valid = 0;

    // artist
    printf("Enter artist name: ");
    fgets(r.artist, sizeof(r.artist), stdin);
    r.artist[strcspn(r.artist, "\n")] = '\0';

    // album
    printf("Enter album name: ");
    fgets(r.album, sizeof(r.album), stdin);
    r.album[strcspn(r.album, "\n")] = '\0';

    // title
    printf("Enter song title: ");
    fgets(r.title, sizeof(r.title), stdin);
    r.title[strcspn(r.title, "\n")] = '\0';

    // genre
    printf("Enter genre: ");
    fgets(r.genre, sizeof(r.genre), stdin);
    r.genre[strcspn(r.genre, "\n")] = '\0';

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
            r.length.minutes = minutes;
            r.length.seconds = seconds;
        }
        while (getchar() != '\n');  // clear input buffer
    } while (!valid);

    // times played
    valid = 0;
    do {
        printf("Enter times played: ");
        if (scanf("%d", &r.times_played) != 1) {
            printf("Please enter a valid integer.\n");
        }
        else if (r.times_played < 0) {
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
        if (scanf("%d", &r.rating) != 1) {
            printf("Please enter a number.\n");
            r.rating = 0;
        }
        while (getchar() != '\n');
    } while (r.rating < 1 || r.rating > 5);

    if (!insertFront(pList, r)) {
        printf("Failed to insert record.\n");
    }
}

void print_current(Node* node) {
    Node* current = node;
    
      printf("  Artist: %s\n", current->data.artist);
      printf("  Album: %s\n", current->data.album);
      printf("  Title: %s\n", current->data.title);
      printf("  Genre: %s\n", current->data.genre);
      printf("  Length: %d:%02d\n", current->data.length.minutes,
            current->data.length.seconds);
      printf("  Times Played: %d\n", current->data.times_played);
      printf("  Rating: %d/5\n", current->data.rating);
      printf("-----------------------------------------\n");
    
}
