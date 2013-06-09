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
	const prog_char *text; //wskaznik na tekst w FLASHU! NAZWA MENU
	menuitemfuncptr menuitemfunc; // WSKAZNIK DO Wywolywanej funkcji po wybraniu danej pozycji menu
	const struct menu_item *parent; //rodzic
	const struct menu_item *submenu; //syn menu submenu
	const struct menu_item *prev; //poprzednik ziaaa
	const struct menu_item *next; //nastepny
};

const extern struct menu_item menu;

// DEKLARACJE ZAPOWIADAJACE!!!

const struct menu_item menu PROGMEM;
const struct menu_item channels PROGMEM;
const struct menu_item config PROGMEM;
const struct menu_item config3 PROGMEM;
const struct menu_item config2 PROGMEM;
const struct menu_item config1 PROGMEM;
const struct menu_item channels3 PROGMEM;
const struct menu_item channels2 PROGMEM;
const struct menu_item channels1 PROGMEM;

// KONIEC DEKLARACJI ZAPOWIADAJACYCH



#endif