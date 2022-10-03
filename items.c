#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"
#include "rooms.h"

//function that takes in a itemList and free the space in the list
void free_itemList(Item* itemList){
	Item* item = itemList;
    while(item != NULL){
        Item* nextItem = item->next;
        free(item);
        item = nextItem;
    }
    itemList = NULL;
}

//function that inserts a new item to the beginning of linkedList
void add_item_to_list(Item** pitemList, Item* item){
    //insert new item at beginning
    item->next = *pitemList;
    *pitemList = item;//updating list pointer to new item
}

//Function that takes in an itemName, searches for the corresponding item
//removes item from list and returns that item
Item* remove_item_from_list(Item** pitemList, char* itemName){
    Item* foundItem = NULL;

	//If itemList is empty, return NULL
    if(*pitemList == NULL){
        return NULL;
    }
	//if target item is first elem in linkedList, then remove
    if(strcasecmp((*pitemList)->name, itemName) == 0){
        foundItem = *pitemList;
        *pitemList = (*pitemList)->next;
        foundItem->next = NULL;
    }
	//item is not the first elem, and therefore to remove we must keep track 
	//of curr and curr->next in order to remove item from list
    else{
        Item* current = *pitemList;
        while(current->next != NULL){
            if(strcasecmp(current->next->name, itemName) == 0){
                foundItem = current->next;
                current->next = current->next->next;
                foundItem->next = NULL;
                break;
            }
            current = current->next;
        }
    }
    return foundItem;
}

//prints items in an itemList
void print_itemList(Item* itemList){
	Item* myItem = itemList;
	//if itemList empty, print corresponding message
    if(myItem == NULL){
        printf("NO ITEM FOUND");
    }
    while(myItem != NULL){
        printf("%s ", myItem->name);
        myItem = myItem->next;
    }
    printf("\n");
}

//items_names arr
char item_names[6][20] = {"Item1", "Item2", "Item3", "Item4", "Item5", "Item6"};
//size of items_names arr
int max_items = sizeof(item_names)/sizeof(item_names[0]);

//randomly assigning items to rooms
void assign_items(){
    //going through all the items
    for(int i = 0; i < max_items; i++){
        //creating a new item, and setting its name, and setting its next value to NULL
        Item * myItem = (Item *) malloc(sizeof(Item));
        myItem->name = item_names[i];
        myItem->next = NULL;
        assign_item_to_random_room(myItem);
    }
}
