#include "header.h"

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
