#include "header.h"

int menu(void) {

	//seeding rand
	srand((unsigned int)time(NULL));

	//opening files
	FILE* musicRead = fopen("musicPlayList.csv", "r");
	if (musicRead == NULL) {
		printf("Failed to open file\n");
		return 1;
	}

	Node* list = NULL;
	if (loadData(&list, musicRead)) {
		printf("Loaded successfully\n");
	}

	fclose(musicRead);	


	int choice = 0;
	do {//this restarts the whole function after a command is made
		do { // this reprints the menu list when input fails 
			choice = 0;
			system("cls");
			printf("Welcome to the Music Manager. To select an option, type the number and press enter\n\n");
			printf("1: Load, loads songs from files, overwrites current list\n");
			printf("2: Store, stores current list into file\n");
			printf("3: Display, prints all songs\n");
			printf("4: Insert, add a song to list\n");
			printf("5: Delete, remove a song from list\n");
			printf("6: Edit, change a song in the list\n");
			printf("7: Sort, sorts the songs in list alphabetically\n");
			printf("8: Rate, change the rating of a song\n");
			printf("9: Play, plays all songs in the list\n");
			printf("10: Shuffle, plays all songs in the list, randomly \n");
			printf("11: Exit, saves list to file, leaves program \n");

			int items_read = scanf("%d", &choice);
			
			while (getchar() != '\n') {
			}

			if (items_read != 1) {
				
				printf("\nError: Please enter a number between 1 and 11.\n");
				printf("Press Enter to continue...");
				getchar();
				continue;
			}

			if (choice < 1 || choice > 11) {
				printf("\nError: %d is not a valid option (must be from 1 to 11).\n", choice);
				printf("Press Enter to continue...");
				getchar();
				continue;
			}

			break;

		} while (1); // placeholder, this will be while the input isn't good

		switch (choice) {
		case 1: //load
		{
			destroyList(&list);
			list = NULL;
			musicRead = fopen("musicPlayList.csv", "r");
			if (musicRead == NULL) {
				printf("Cannot open file to reload playlist\n");
				break;
			}
			if (loadData(&list, musicRead)) {
				printf("Reloaded successfully\n");
			}
			fclose(musicRead);
		}
			break;
		case 2: //store
		{
			FILE* musicWrite = fopen("musicPlayList.csv", "w");
			if (musicWrite == NULL) {
				printf("Error: Cannot open file for writing\n");
				break;
			}
			storeData(list, musicWrite);
			fclose(musicWrite);
			break;
		}
		case 3: //display
			//need some function to determine if they wish to display from a certain artist, or all songs
			printList(list);
			printAsk(list); 
			break;
		case 4: //insert
			promptForRecord(&list);
			break;
		case 5: //delete
			deleteSong(&list);
			break;
		case 6: // edit
			editSong(&list);
			break;
		case 7: //sort
			sortByTitle(list);
			break;
		case 8: //rate
			rateSong(&list);
			break;
		case 9: //play
			playAllSong(list);
			break;
		case 10://shuffle
			shuffle(list);
			break;
		case 11://exit
		{
			FILE* musicWrite = fopen("musicPlayList.csv", "w");
			if (musicWrite == NULL) {
				printf("Error: Cannot open file for writing!\n");
				destroyList(&list);
				return(1);
			}
			exitProgram(&list, musicWrite);
			return(0);
			break;
		}
		default:
		{
			FILE* musicWrite = fopen("musicPlayList.csv", "w");
			exitProgram(&list, musicWrite);
			return(0);
			break;
		}
		}

		if (choice != 11) {
			printf("\nPress Enter to return to menu...");
			getchar();
		};

	} while (1); //exit function ends the program, so infinite loop to allow multiple menu selections
}