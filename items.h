#ifndef ITEM_H
#define ITEM_H
#include <stdbool.h>

//creating a strct Item that acts like a node in a linked list.
//Item has 2 attributes, name and pointer to next Item (node)
typedef struct Item{
    char* name;
    struct Item* next;
} Item;

//declarations of functions that in items.c that will be used in main.c
void free_itemList(Item* itemList);
void add_item_to_list(Item** pitemList, Item* item);
Item* remove_item_from_list(Item** pitemList, char* itemName);
void print_itemList(Item* itemList);
void assign_items();
#endif
