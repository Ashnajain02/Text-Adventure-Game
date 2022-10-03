#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "rooms.h"
#include "items.h"


//arrays representing the names of the rooms and characters
char room_names[9][10] ={"Room1", "Room2", "Room3", "Room4", "Room5", "Room6", "Room7", "Room8", "Room9"};
char charc_names[5][20] = {"Charc1", "Charc2", "Charc3", "Charc4", "Charc5"};
//int values representing the lengths of room and character arrays
int max_rooms = sizeof(room_names)/sizeof(room_names[0]);
int max_charc = sizeof(charc_names)/sizeof(charc_names[0]);

Room *rooms[ROOM_DIMX][ROOM_DIMX];//creates a array of pointer to data of type Room

//function that initializes rooms
void initialize_Rooms(){
	for(int x = 0; x < ROOM_DIMX; x++){
		for(int y = 0; y < ROOM_DIMY; y++){
			rooms[x][y] =  (Room *) malloc(sizeof( Room)); //allocating space of for each room
			rooms[x][y]->name = NULL; // room_names[x*ROOM_DIMX + y];//turing 2D indexes into 1D representation
			//setting pointers from each room to NULL
			rooms[x][y]->west = NULL;
			rooms[x][y]->east = NULL;
			rooms[x][y]->north = NULL;
			rooms[x][y]->south = NULL;
			//setting all the values in character array in each room to NULL
			for(int i = 0; i < max_charc; i++){
				rooms[x][y]->character[i] = NULL;
			}
		} 
	}
	//going through and appropiately setting pointers for neighboring rooms
	for(int x = 0; x < ROOM_DIMX; x++){
       for(int y = 0; y < ROOM_DIMY; y++){
			if(x > 0){
				rooms[x][y]->west = rooms[x-1][y];
			}
			if(x < ROOM_DIMX - 1){  
				rooms[x][y]->east = rooms[x+1][y];
			}
			if(y > 0){  
				rooms[x][y]->north = rooms[x][y-1];
			}
			if(y < ROOM_DIMY - 1){  
				rooms[x][y]->south = rooms[x][y+1];
			}
		} 
	}
}

//function that iterates through all rooms, and free any malloced space
void free_roomSpace(){
	for(int x = 0; x < ROOM_DIMX; x++){
        for(int y = 0; y < ROOM_DIMY; y++){
            free_itemList(rooms[x][y]->itemList);
            rooms[x][y]->itemList = NULL;
            free(rooms[x][y]);
            rooms[x][y] = NULL;
        }
    }
}

//function that randomly assigns names to the rooms
void assign_rooms(){
	for(int i = 0; i < max_rooms; i++){
		char* roomName = room_names[i];
		bool bAssigned = false;
        while(!bAssigned){
            //choose a random num between 0-max_rooms-1
            int num = rand() % max_rooms;
            int x = num/ROOM_DIMX;
            int y = num%ROOM_DIMX;
            //if name is NULL, the assign the name to the room
            if(rooms[x][y]->name == NULL){
                rooms[x][y]->name = roomName;
                //exit the loop, and move to the next item
                bAssigned = true;
            }
        }
	}
}

//function that returns a random room
Room* randomRoom(){
	int num = rand() % max_rooms;
	int x = num/ROOM_DIMX;
    int y = num%ROOM_DIMX;
	return rooms[x][y];
}

//function that randomly assigns items to rooms
void assign_item_to_random_room(Item* item){
	bool bAssigned = false;
	while(!bAssigned){
		//choose a random num between 0-max_rooms-1
		int num = rand() % max_rooms;
		int x = num/ROOM_DIMX;
		int y = num%ROOM_DIMX;
		//if the first elm of itemList is NULL, the assign the item to the room
	
		if(rooms[x][y]->itemList == NULL){
			rooms[x][y]->itemList = item;
			//exit the loop, and move to the next item
			bAssigned = true;
		}
	}
}

//function that randomly assigns characters to rooms
void assign_charc(){
	//iterates through character array
	for(int i = 0; i < max_charc; i++){
		char* myCharc = charc_names[i];
		bool bAssigned = false;
        while(!bAssigned){
			//picks a random room
            int num = rand() % max_rooms;
            int x = num/ROOM_DIMX;
            int y = num%ROOM_DIMX;
			//if there are no characters in this room then
			//assign the current character to this room 
            if(rooms[x][y]->character[0] == NULL){ //array is empty
                rooms[x][y]->character[0] = myCharc;
				rooms[x][y]->character[1] = NULL;
                bAssigned = true;
            }
        }
	}
}

//function that locates the corresponding character and removes it from the
//character array by shifting all the elements over 
//returns pointer to the character that we want
char* find_remove_charc(char* charcName){
	char* myCharcGuess = NULL;
	for(int i = 0; i < max_rooms; i++){
		int x = i/ROOM_DIMX;
        int y = i%ROOM_DIMX;
		Room* currRoom = rooms[x][y];
		for(int j = 0; j < max_charc; j++){
			if(currRoom->character[j] == NULL){break;}
			if(strcasecmp(currRoom->character[j], charcName) == 0){
				myCharcGuess = currRoom->character[j];
				for(int k = j; k < max_charc-1; k++){
					currRoom->character[k] = currRoom->character[k+1];
				}
				break;
			}
		}
		if(myCharcGuess != NULL){
			break;
		}
	}
	if(myCharcGuess == NULL){printf("Not a valid character.\n");}
	return myCharcGuess;
}

//function that add a character to room
void add_charc_to_room(Room* room, char* charcName){
	for(int i = 0; i < max_charc; i++){
		if(room->character[i] == NULL){
			room->character[i] = charcName;
			break;
		}
	}
}

//function that removed an item from a specified room
//return the removed item
Item* remove_item_from_room(Room* room, char* itemName){
	return remove_item_from_list(&room->itemList, itemName);
}

//function that add item to a specified room
void add_item_to_room(Room* room, Item* item){
	add_item_to_list(&room->itemList, item);
}

//function that prints 
//the name of the current room, and the items + characters in the room
//and the relative location of the surrounding rooms
void look_into_room(Room * room){
	printf("I am in %s\n", room->name);

	printf("Items in room: ");
	print_itemList(room->itemList);

	printf("Characters in room: ");
	if(room->character[0] == NULL){
		printf("NO CHARACTER FOUND");
	}
	for(int i = 0; i < MAX_CHARACTER; i++){
		if(room->character[i] == NULL){break;}
		printf("%s ", room->character[i]);
	}
	printf("\n");

	if(room->west != NULL) printf("On the west is %s\n", room->west->name);
	if(room->east != NULL) printf("On the east  is %s\n", room->east->name);
	if(room->north != NULL) printf("On the north is %s\n", room->north->name);
	if(room->south != NULL) printf("On the south is  %s\n", room->south->name);

	printf("\n");
}

//function that takes in a currRoom and a direction that returns
//a new room based on the dir command
Room* go_to_next_room(Room * currRoom, char * dir){
	//if dir is west then currRoom now whatever room was on its west.
	//unless we are unable to go west, in which case the currRoom stays the same
	if(strcasecmp(dir, "west") == 0){
		if(currRoom->west == NULL){
			printf("Unable to go west from room: %s\n", currRoom->name);
		}
		else{
			currRoom = currRoom->west;
		}
	}

	else if(strcasecmp(dir, "east") == 0){
        if(currRoom->east == NULL){
            printf("Unable to go east from room: %s\n", currRoom->name);
        }
        else{
            currRoom = currRoom->east;
        }
    }

	else if(strcasecmp(dir, "north") == 0){
        if(currRoom->north == NULL){
            printf("Unable to go north from room: %s\n", currRoom->name);
        }
        else{
            currRoom = currRoom->north;
        }
    }

	else if(strcasecmp(dir, "south") == 0){
        if(currRoom->south == NULL){
            printf("Unable to go south from room: %s\n", currRoom->name);
        }
        else{
            currRoom = currRoom->south;
        }
    }
	return currRoom;	
}
//Personal testing code. Please Disregard.
int main1(){
//	srand(time(NULL));
	initialize_Rooms();
	assign_items();
	assign_charc();
	for(int x = 0; x < ROOM_DIMX; x++){
		for(int y = 0; y < ROOM_DIMY; y++){
			printf("looking into room[%d][%d]\n", x, y);
			look_into_room(rooms[x][y]);
		} 
	}
}

