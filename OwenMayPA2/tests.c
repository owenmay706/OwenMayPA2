#include "tests.h"
// insert test
void insertTest(void) {
	//creating node
	Record r;
	strcpy(r.artist, "Perry, Katy");
	strcpy(r.album, "Witness");
	strcpy(r.title, "Chained to the Rhythm");
	strcpy(r.genre, "pop");
	r.length.minutes = 4; r.length.seconds = 36;
	r.times_played = -1;
	r.rating = 6;
	createNode(r);


	//inserting into list
	Node* list = NULL;
	insertFront(&list, r);

	if (list != NULL) {
		printf("Contents added to list\n");
	}
	else {
		printf("Contents not added to list\n");
		return 0;
	}

	printList(list);

}

//delete test
void deleteTest(void) {
	//creating node
	Record r;
	strcpy(r.artist, "Perry, Katy");
	strcpy(r.album, "Witness");
	strcpy(r.title, "Chained to the Rhythm");
	strcpy(r.genre, "pop");
	r.length.minutes = 4; r.length.seconds = 36;
	r.times_played = 3;
	r.rating = 5;
	createNode(r);

	//inserting into list
	Node* list = NULL;
	insertFront(&list, r);

	deleteSong(&list);

	if (list == NULL) {
		printf("head pointer is null\n");
	}
	else {
		printf("head pointer is not null\n");
	}

	printList(list);

}

//shuffle test
void shuffleTest(void) {
	//was not sure how to do this one, I did not know how I could make my shuffle function always go in the order 3, 2, 1
}
