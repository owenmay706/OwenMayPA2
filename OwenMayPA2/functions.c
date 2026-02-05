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