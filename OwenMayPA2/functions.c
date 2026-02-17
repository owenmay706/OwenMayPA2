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
        printf("Record #%d:\n", count);
        printf("  Artist: %s\n", current->data.artist);
        printf("  Album: %s\n", current->data.album);
        printf("  Title: %s\n", current->data.title);
        printf("  Genre: %s\n", current->data.genre);
        printf("  Length: %d:%02d\n", current->data.length.minutes,
            current->data.length.seconds);
        printf("  Times Played: %d\n", current->data.times_played);
        printf("  Rating: %d/5\n", current->data.rating);
        printf("-----------------------------------------\n");

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


            printf("Record #%d:\n", count);
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
        current = current->next;
        count++;
    }

    printf("\nTotal records: %d\n", count - 1);
}



void exitProgram(Node** pList, FILE* output, FILE* input) {
    storeData(*pList, output);
    fclose(output);
    fclose(input);
    destroyList(pList);
    exit(0);
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

void print_current(Node* pList) {
    Node* current = pList;
    
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

void play1_song(Node* pList) {
    print_current(pList);
    Sleep(500);
    printf(".");
    Sleep(500);
    printf("."); 
    Sleep(500);
    printf(".\n");
    Sleep(500);
    printf("Finished Playing");
}

int rateSong(Node** pList) {
    Record target;
    Node* current = *pList;

    //get target
    printf("Enter song title to rate: ");
    fgets(target.title, sizeof(target.title), stdin);
    target.title[strcspn(target.title, "\n")] = '\0';

    // find target 
    while (current != NULL && strcmp(current->data.title, target.title) != 0) {
        current = current->next;
    }

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
    char target[100];
    Node* current = *pList;

    //finding song
    printf("Enter song title to delete: ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = '\0';

    while (current != NULL && strcmp(current->data.title, target) != 0) {
        current = current->next;
    }

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