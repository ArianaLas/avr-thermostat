#include "menu.h"

// INICJALIZACJA LISTY !!!

const struct menu_item config3 PROGMEM = {txt10, change_hDown, &channels, 0, &config2, 0};
const struct menu_item config2 PROGMEM = {txt9, change_hUP, &channels, 0, &config1, &config3};
const struct menu_item config1 PROGMEM = {txt8, change_tmpDown, &channels, 0, &config, &config2};
const struct menu_item config PROGMEM = {txt7, change_tmpUP, &channels, 0, 0, &config1};

const struct menu_item channels3 PROGMEM  = {txt6, 0, &menu, &config, &channels2, 0};
const struct menu_item channels2 PROGMEM = {txt5, 0, &menu, &config, &channels1, &channels3};
const struct menu_item channels1 PROGMEM = {txt4, 0, &menu ,&config, &channels, &channels2};
const struct menu_item channels PROGMEM = {txt3, 0, &menu, &config, 0, &channels1};

const struct menu_item menu1 PROGMEM = {txt2, 0, 0, &channels, &menu, 0};
const struct menu_item menu PROGMEM = {txt1, 0, 0, &channels, 0, &menu1};

// KONIEC INICJALIZACJI LISTY

void Menu_Show(){

}

void Menu_SelectNext(){

}

void Menu_SelectPrev(){

}

void MenuClick(){

}

void MenuBack(){

}

void change_tmpUP(){

}

void change_tmpDown(){

}

void change_hUP(){

}

void change_hDown(){

}


int main(int argc, char const *argv[])
{
	
	return 0;
}
