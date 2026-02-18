#include "header.h"

int readFILE(FILE* input, Record* newRecord) {
    char buffer[200];
    if (!fgets(buffer, sizeof(buffer), input)) {
        return 0;
    }

  
    buffer[strcspn(buffer, "\n")] = '\0';

    char* ptr = buffer;

    // artist might have quotes
    if (*ptr == '"') {
        ptr++;  // skip opening "
        char* end = strchr(ptr, '"');
        if (!end) return 0;
        size_t len = end - ptr;
        if (len >= sizeof(newRecord->artist)) len = sizeof(newRecord->artist) - 1;
        strncpy(newRecord->artist, ptr, len);
        newRecord->artist[len] = '\0';
        ptr = end + 1;  // after closing "
    }
    else {
        char* end = strchr(ptr, ',');
        if (!end) return 0;
        size_t len = end - ptr;
        if (len >= sizeof(newRecord->artist)) len = sizeof(newRecord->artist) - 1;
        strncpy(newRecord->artist, ptr, len);
        newRecord->artist[len] = '\0';
        ptr = end;
    }
    if (*ptr == ',') ptr++;  // skip comma after artist

    //album
    char* end = strchr(ptr, ',');
    if (!end) return 0;
    size_t len = end - ptr;
    if (len >= sizeof(newRecord->album)) len = sizeof(newRecord->album) - 1;
    strncpy(newRecord->album, ptr, len);
    newRecord->album[len] = '\0';
    ptr = end + 1;

   //title
    end = strchr(ptr, ',');
    if (!end) return 0;
    len = end - ptr;
    if (len >= sizeof(newRecord->title)) len = sizeof(newRecord->title) - 1;
    strncpy(newRecord->title, ptr, len);
    newRecord->title[len] = '\0';
    ptr = end + 1;

  //genre
    end = strchr(ptr, ',');
    if (!end) return 0;
    len = end - ptr;
    if (len >= sizeof(newRecord->genre)) len = sizeof(newRecord->genre) - 1;
    strncpy(newRecord->genre, ptr, len);
    newRecord->genre[len] = '\0';
    ptr = end + 1;

    //length
    int minutes, seconds;
    if (sscanf(ptr, "%d:%d", &minutes, &seconds) != 2) return 0;
    newRecord->length.minutes = minutes;
    newRecord->length.seconds = seconds;

   
    ptr = strchr(ptr, ',');
    if (!ptr) return 0;
    ptr++;

    // times played
    newRecord->times_played = atoi(ptr);

    
    ptr = strchr(ptr, ',');
    if (!ptr) return 0;
    ptr++;

    // rating
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
