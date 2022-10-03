#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rooms.h"
#include "items.h"

//calling variables that have been defined in either
//rooms.c or items.c
extern char room_names[9][10];
extern char item_names[6][20];
extern char charc_names[5][20];

extern int max_rooms;
extern int max_items;
extern int max_charc;

//creating Avatar struct that has name, currRoom, and itemList property 
typedef struct Avatar{
    char* name;
	Room* currRoom;
    struct Item* itemList;
} Avatar;

//Initializing an Avatar called player
Avatar player;

//function that prints the inventory of the player
void inventory(){
    printf("Player inventory: ");
    print_itemList(player.itemList);
}

//function that adds an item to an avatar
//by invoking the function that adds an item to a list
void add_item_to_avatar(Item* item){
    add_item_to_list(&player.itemList, item);
}

//function that adds an item to Avatar itemList, and also removes it from room itemList
//return a boolean, representing if action was sucessful or not
bool take_item(Room* room, char* itemName){
    Item* removedItem = remove_item_from_room(room, itemName);
    if(removedItem == NULL){
        printf("Item not found in room\n");
        return false;
    }
    add_item_to_avatar(removedItem);
    return true;
}

//function that removes item from avatar
Item* remove_item_from_avatar(char* itemName){
    return remove_item_from_list(&player.itemList, itemName);
}

//function that drop an item from Avatar itemList, and also adds it to room itemList
//returns a boolean, representing if action was sucessful or not
bool drop_item(Room* room, char* itemName){
    Item* removedItem = remove_item_from_avatar(itemName);
    if(removedItem == NULL){
        printf("Item not found with Avatar\n");
        return false;
    }
    add_item_to_room(room, removedItem);
    return true;
}

//function that free space for both the players itemList
//and all the rooms and any itemLists in the room
void free_space(){
    free_itemList(player.itemList);
    player.itemList = NULL;
	free_roomSpace();
}


int main(){
	//randomly pick a room, item, and charac for the solution
	int r = rand() % max_rooms;
	char* room_sol = room_names[r];

	int i = rand() % max_items;
	char* item_sol = item_names[i];

	int c = rand() % max_charc;
	char* charc_sol = charc_names[c];

	//clueCounter tracks how many times clue was called
	int clueCounter = 0;
	//3 bools to see in winning conditon has been met
	bool roomMatch;
	bool charcMatch;
	bool itemMatch; 
	printf("SPOILER: it was %s, with the %s in %s\n", charc_sol, item_sol, room_sol);

	//initialize everything, and assign room, items and characters
	initialize_Rooms();
	assign_rooms();
	assign_items();
    assign_charc();
	//pick a random room for where the character starts
	player.currRoom = randomRoom();
  	char str[20];
	char dir[10];
	char itemName[20];
	char charcName[20];
  	printf("Welcome to Ashna's Clue Game!\n");
  
  	while(true){
		//set all 3 bools to false at start of each command
		roomMatch = false;
		charcMatch = false;
		itemMatch = false;

    	printf(">>>> ");
    	scanf("%s", str);
    	
		//if input = help
		//print commands
		if(strcasecmp(str, "help") == 0){
      		printf("list, look, go <direction>, take <item>, drop <item>, inventory, clue, exit\n");
    	}
		//if input = list
		//print names of all characters, items and rooms
		else if(strcasecmp(str, "list") == 0){
			printf("Characters: ");
			for(int i = 0; i < max_charc; i++){
				printf("%s ", charc_names[i]);
			}
			printf("\n");
			printf("Items: ");
            for(int i = 0; i < max_items; i++){
                printf("%s ", item_names[i]);
            }
            printf("\n");
			printf("Rooms: ");
            for(int i = 0; i < max_rooms; i++){
                printf("%s ", room_names[i]);
            }
            printf("\n");
		}
		//if input = look
		//invoke look_into_room function for whichever room the player is in 
		else if(strcasecmp(str, "look") == 0){
			look_into_room(player.currRoom);
		}

		//if input = go
		//allow the user to type a direction
		//if dir is west, north, east, or south, then pass dir into go_to_next_room() func
		else if(strcasecmp(str, "go") == 0){
			printf("Type a direction: north, south, east, or west\n");
			printf(">>>> ");
			scanf("%s", dir);
			if((strcasecmp(dir, "north") == 0) ||
				(strcasecmp(dir, "south") == 0)||
				(strcasecmp(dir, "east") == 0)||
				(strcasecmp(dir, "west") == 0)){
				player.currRoom = go_to_next_room(player.currRoom, dir);
				look_into_room(player.currRoom);
			}
			else{printf("Not a valid direction. Retype\n");}
        }
		//if input = take
		//allow the user to type input
		//if item exists in room, take item, otherwise print message
		else if(strcasecmp(str, "take") == 0){
			printf("Type a item: \n");
			printf(">>>> ");
            scanf("%s", itemName);
			if(take_item(player.currRoom, itemName) == false){
				printf("Not a valid item. Retype Entry\n");
            }
			else{printf("%s successfully taken\n", itemName);}
		}
		//if input = drop
		//allow user to type input
		//if item exits in player inventory, drop it, and print message
		else if(strcasecmp(str, "drop") == 0){
			inventory();
            printf("Type a item: \n");
			printf(">>>> ");
            scanf("%s", itemName);
            if(drop_item(player.currRoom, itemName) == false){
                printf("Not a valid. Retype Entry\n");
            }
			else{printf("%s successfully dropped\n", itemName);}
        }
		//if input = inventory
		//print inventory
		else if(strcasecmp(str, "inventory") == 0){
			inventory();
    	}
		//if input = clue
		//increment the clueCounter
		//allow user to type in character
		//reveal any matches for room, character or item
		else if(strcasecmp(str, "clue") == 0){
			clueCounter++;
			printf("type a character: \n");
			printf(">>>> ");
            scanf("%s", charcName);
			if(strcasecmp(player.currRoom->name, room_sol) == 0){
				roomMatch = true;
				printf("Room match.\n");
			}
			char* charcGuess = find_remove_charc(charcName);
			add_charc_to_room(player.currRoom, charcGuess);

			for(int i = 0; i < max_charc; i++){
				if(player.currRoom->character[i] == NULL){
					break;
				}
				else if(strcasecmp(player.currRoom->character[i], charc_sol) == 0){
					charcMatch = true;
					printf("Character match.\n");
					break;
				}
			}

			while(player.currRoom->itemList != NULL){
				if(strcasecmp(player.currRoom->itemList->name, item_sol) == 0){
					itemMatch = true;
					printf("Item match.\n");
					break;
				}
				player.currRoom->itemList = player.currRoom->itemList->next;
			}

			while(player.itemList != NULL){
				if(strcasecmp(player.itemList->name, item_sol) == 0){
					itemMatch = true;
					printf("Item match.\n");
                    break;
				}
				player.itemList = player.itemList->next;
			}
			//break if all 3 matches are met
			if(roomMatch & charcMatch & itemMatch){
				printf("CONGRATULATIONS! YOU WON :)\n");
				break;
			}
			//break if clue called 10+ times without winning
			if(clueCounter >= 10){
				printf("SORRY. YOU LOST :(\n");
				break;
			}

		}
		else if(strcasecmp(str, "exit") == 0){
			break;
		}
    	else{
      		printf("Dont recognize entry\n");
      		printf("Retype entry\n");
    	}
  	}
	//once game exits, free all the allocate space
	free_space();
	return 0;  
}
