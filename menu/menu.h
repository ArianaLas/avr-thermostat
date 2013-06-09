#ifndef _menue_h_
#define _menue_h_

#include <stdio.h>
#include <avr/pgmspace.h> 
#include <stdlib.h>

/// STRINGS TABLE

const prog_char txt1[] = "Change Temperature";
const prog_char txt2[] = "Change Huminidity";
const prog_char txt3[] = "Channel 0";
const prog_char txt4[] = "Channel 1";
const prog_char txt5[] = "Channel 2";
const prog_char txt6[] = "Channel 3";
const prog_char txt7[] = "C. OD";
const prog_char txt8[] = "C. DO";
const prog_char txt9[] = "H. OD";
const prog_char txt10[] = "H DO";

// END STRINGS TABLE

//FUNCTION TO SET MENU
	void Menu_Show();
	void Menu_SelectNext();
	void Menu_SelectPrev();
	void MenuClick();
	void MenuBack();
	void change_tmpUP();
	void change_tmpDown();
	void change_hUP();
	void change_hDown();
// END FUNCTION



typedef void (*menuitemfuncptr)(); //

struct PROGMEM menu_item
{
	prog_char *text; //wskaznik na tekst w FLASHU! NAZWA MENU
	in8_t war;
	menuitemfuncptr menuitemfunc; // WSKAZNIK DO Wywolywanej funkcji po wybraniu danej pozycji menu
	const struct menu_item *parent; //rodzic
	const struct menu_item *submenu; //syn menu submenu
	const struct menu_item *prev; //poprzednik ziaaa
	const struct menu_item *next; //nastepny
};

extern struct menu_item menu;

struct menu_item menu;
struct menu_item channels;
struct config_channel config;


struct menu_item config PROGMEM = {txt7,change_tmpUP,&channels0,0,0,config1};
struct menu_item config1 PROGMEM = {txt8,change_tmpDown,&channels1,0,config,config2};
struct menu_item config2 PROGMEM = {txt9,change_hUP,&channels2,0,config1,config3};
struct menu_item config3 PROGMEM = {txt10,change_hDown,&channels3,0,config2,0};


#endif