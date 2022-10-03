# Clue-Text-Adventure-Game

Hello! Welcome to Ashna's Text Adventure Game!

How to compile the code:
	1. enter the command gcc -o game rooms.c items.c adventure.c into terminal
	2. enter the command ./game
	*the code should now be compiled, and the game should be running"

Description of overall structure of game board with pointers:
	-The game board is represented by a 2D array. Each index of the array first allocated with the space of a Room. 
	-Room are connected to one another via pointers during the room initialization process.
 
How my game meets all of the listed requirements:
a. 9 rooms are made by the initialize_rooms() function in rooms.c. Creates a 3x3 array allocates space at each index for a room. Set all direction pointers to NULL, and then connects the corresponding rooms together.

b. initialize_rooms() function in rooms.c randomizes the room locations

c. item_names array in items.c, and charc_names array in rooms.c sets 6 items and 5 characters. assign_items() and assign_charc() function in rooms.c randomized the locations of items and characters.

d. In adventure.c 3 different numbers are chosen randomly between 0 and the length of either the items, rooms or character names array. Based on the random number, a value is index, and set as the random solution

e. In struct Room declaration in rooms.h, there is a pointer to itemList, that will contain all the items that are in a room in a linkedList type data structure.

f. In struct Avatar declaration in adventure.c, there is a pointer to itemList that will contain all the items that are with the avatar.

g. Commands functionality located in adventure.c
	- For algorithmic design of each command, please refer to adventure.c 
	comments. :)
