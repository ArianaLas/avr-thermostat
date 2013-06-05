#include "menu.h"

void menu_init(){
	/*Init main menu*/
	zero = malloc(sizeof(struct diods)); // create a menu for diods
	/*Create a submenu of temp and frequency*/
	glowne = malloc(sizeof(struct menu));
	menu* frequency = malloc(sizeof(struct menu));
	frequency = malloc(sizeof(diods));
	/*Init menu*/
	glowne -> name = "Change temperature";
	glowne -> head = 1;
	glowne -> right = frequency;
	glowne -> left = frequency;
	glowne -> child = zero;

	frequency -> name = "Change frequency";
	frequency -> head = 0;
	frequency -> left = glowne;
	frequency -> right = glowne;
	frequency -> child = zero;

	/*Create a diods choice menu*/
	diods* one = malloc(sizeof(struct diods));
	diods* two = malloc(sizeof(struct diods));
	diods* three = malloc(sizeof(struct diods));
	/*Init diods menu*/
	zero -> nr_diod = 0;
	zero -> right = one;
	zero -> left = three;

	one -> nr_diod = 1;
	one -> right = two;
	one -> left = zero;

	two -> nr_diod = 2;
	two -> right = three;
	two -> left = one;

	three -> nr_diod = 3;
	three -> right = zero;
	three -> left = two;

	/* End init diods*/
	zero -> parent = one -> parent =  two -> parent = three -> parent = glowne;
	// parent is for all diods is Zero temperature ! it's logic beliewe me!
	// Init diods menu
	
}
