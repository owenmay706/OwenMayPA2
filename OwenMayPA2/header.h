#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

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
	struct node* next;
	struct node* prev;
}Node;

//create node
Node* createNode(Record newRecord);

//insert at front
int insertFront(Node** pList, Record newRecord);

//read file, 1 line
int readFILE(FILE* input, Record* newRecord);

//load, gets data from file into list
int loadData(Node** pList, FILE* input);

//store, this takes from list  file and stores into file overwritting data
int storeData(Node* pList, FILE* output);

//display, prints all records, or all records that match an artist
void printList(Node* pList); // need to add option to print all or just 1

void printAsk(Node* pList);

void print_current(Node* pList);

//finds node based on song title
Node* FindSongTitle(Node* pList);

//insert, adds new node from user input, probably at front
void promptForRecord(Node** pList);
//delete, removes node
int deleteSong(Node** pList);

//edit, the user finds a record by artist (if multiple they pick one of them) and they can edit any fields
void editSong(Node** pList);

//sort, sort nodes by some metric, maybe song title alphabetically
void swapRecords(Record* a, Record* b);
void sortByTitle(Node* pList);

//rate, assign a value 1-5 to a song overwritting previous
int rateSong(Node** pList);

//play, displays current record for some time, then playing the next until all are done
void play1_song(Node* pList);
void playAllSong(Node* pList);

//shuffle, plays songs in random order, does not change the list
void shuffle(Node* pList);

//exit, saves list into file, overwritting data
void exitProgram(Node** pList, FILE* output, FILE* input);
void destroyList(Node** pList);

//menu, allows access to load, store, display, insert, delete, edit, sort, rate, play, shuffle, and exit
void menu(void);
#endif
