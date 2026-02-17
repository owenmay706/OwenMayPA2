#include "header.h"

Node* createNode(Record newRecord) {
	Node* newNode = malloc(sizeof(Node));

	if (newNode != NULL) {
		newNode->data = newRecord;
		newNode->next = NULL;
		newNode->prev = NULL;
	}

	return newNode;
}

int insertFront(Node** pList, Record newRecord) {

	Node* newNode = createNode(newRecord);
	int success = 0;

	if (newNode != NULL) {
		success = 1;

		if (*pList == NULL) {
			//empty list 
			*pList = newNode;
		}
		else 
		{
			newNode->next = *pList;
			(*pList)->prev = newNode;
			*pList = newNode;
		}
	}
	return success;
}

int readFILE(FILE* input, Record* newRecord) {
    char buffer[200];
    if (!fgets(buffer, sizeof(buffer), input)) {
        return 0;
    }

    // Remove newline
    buffer[strcspn(buffer, "\n")] = '\0';

    char* ptr = buffer;
    char* end;

    // get artist
    if (*ptr == '"') {
        ptr++;  // skip opening quote
        end = strchr(ptr, '"');
        if (!end) return 0;
        strncpy(newRecord->artist, ptr, end - ptr);
        newRecord->artist[end - ptr] = '\0';
        ptr = end + 2;  // skip closing quote and comma
    }
    else {
        end = strchr(ptr, ',');
        if (!end) return 0;
        strncpy(newRecord->artist, ptr, end - ptr);
        newRecord->artist[end - ptr] = '\0';
        ptr = end + 1;
    }

    // get album
    end = strchr(ptr, ',');
    if (!end) return 0;
    strncpy(newRecord->album, ptr, end - ptr);
    newRecord->album[end - ptr] = '\0';
    ptr = end + 1;

    // get title
    end = strchr(ptr, ',');
    if (!end) return 0;
    strncpy(newRecord->title, ptr, end - ptr);
    newRecord->title[end - ptr] = '\0';
    ptr = end + 1;

    // get genre
    end = strchr(ptr, ',');
    if (!end) return 0;
    strncpy(newRecord->genre, ptr, end - ptr);
    newRecord->genre[end - ptr] = '\0';
    ptr = end + 1;

    // get time 
    int minutes, seconds;
    if (sscanf(ptr, "%d:%d", &minutes, &seconds) != 2) return 0;
    newRecord->length.minutes = minutes;
    newRecord->length.seconds = seconds;
    ptr = strchr(ptr, ',');
    if (!ptr) return 0;
    ptr++;

    // get times_played
    newRecord->times_played = atoi(ptr);
    ptr = strchr(ptr, ',');
    if (!ptr) return 0;
    ptr++;

    // get rating
    newRecord->rating = atoi(ptr);

    return 1;
}

int loadData(Node** pList, FILE* input) {
	int success = 1;
	Record newRecord;

	while (readFILE(input, &newRecord)) {
		if (!insertFront(pList, newRecord)) {
			success = 0;
		}
	}

	return success;
}

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
    char* artist;


    if (pList == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Enter artist name: ");
    fgets(artist, sizeof(artist), stdin);

    printf("=========================================\n");
    printf("         MUSIC LIBRARY\n");
    printf("=========================================\n\n");

    while (current != NULL) {
        while (strcmp(current->data.artist, artist) == 0) {


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


int storeData(Node* pList, FILE* output)
{
    Node* current = pList;

    if (output == NULL) {
        return 0;
    }

    while (current != NULL) {

        // Artist: quote if it contains a comma
        if (strchr(current->data.artist, ',') != NULL) {
            fprintf(output, "\"%s\",", current->data.artist);
        }
        else {
            fprintf(output, "%s,", current->data.artist);
        }

        fprintf(output, "%s,", current->data.album);
        fprintf(output, "%s,", current->data.title);
        fprintf(output, "%s,", current->data.genre);

        fprintf(output, "%d:%02d,",
            current->data.length.minutes,
            current->data.length.seconds);

        fprintf(output, "%d,", current->data.times_played);
        fprintf(output, "%d\n", current->data.rating);

        current = current->next;
    }

    return 1;
}

void exitProgram(Node* pList, FILE* output, FILE* input) {
    storeData(pList, output);
    fclose(output);
    fclose(input);
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