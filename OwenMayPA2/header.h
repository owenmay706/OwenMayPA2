#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//structs
typedef struct duration {
	int minutes;
	int seconds;
}Duration;

typedef struct record {
	char artist[50];
	char album[50];
	char title[50];
	char genre[50];
	Duration length;
	int times_played;
	int rating; //1-5
}Record;

typedef struct node {
	Record data;
	Node* Next;
	Node* previous;
}Node;

//load, gets data from file into list

//store, this takes from list  file and stores into file overwritting data

//display, prints all records, or all records that match an artist

//insert, adds new node from user input, probably at front

//delete, removes node

//edit, the user finds a record by artist (if multiple they pick one of them) and they can edit any fields

//sort, sort nodes by some metric, maybe song title alphabetically

//rate, assign a value 1-5 to a song overwritting previous

//play, displays current record for some time, then playing the next until all are done

//shuffle, shuffle the list

//exit, saves list into file, overwritting data

#endif
