#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>
#include "items.h"

#define MAX_CHARACTER 5
#define ROOM_DIMX 3
#define ROOM_DIMY 3

//struct Room that has pointers to diff rooms in North, South, East, West
//struct Room also contains itemList and character array
typedef struct Room{
	char* name;
	struct Room *north;
	struct Room *south;
	struct Room *east;
	struct Room *west;
	struct Item *itemList;
	char *character[MAX_CHARACTER];
} Room;

//declarations of functions in rooms.c that are used in adventure.c
void initialize_Rooms();
void free_roomSpace();
void assign_rooms();
void assign_item_to_random_room(Item* item);
void assign_charc();
Room* randomRoom();
void look_into_room(Room * room);
Room* go_to_next_room(Room * currRoom, char * dir);
void add_charc_to_room(Room* room, char* charcName);
char* find_remove_charc(char* charcName);
Item* remove_item_from_room(Room* room, char* itemName);
void add_item_to_room(Room* room, Item* item);
#endif
