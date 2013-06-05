#ifndef _menue_h_
#define _menue_h_

#include <stdio.h>

#include <stdlib.h>

typedef struct diods{
	unsigned int nr_diod : 2;
	/*
		Representation of diods : 
		0 1 2 3 it's enough!
	*/
	struct diods* left;
	struct diods* right;
	struct menu* parent;
}diods;

typedef struct menu{
	char* name;
	struct diods* child;
	struct menu* left;
	struct menu* right;
	int head : 1; //1 bit int :) nice trick

}menu;
/*
menu is cycle list with only HEAD :)!


*/

/*
	Direct Menu and menu of diods!
*/

menu* glowne;
diods* zero;

// Init all menu's
void menu_init();

#endif