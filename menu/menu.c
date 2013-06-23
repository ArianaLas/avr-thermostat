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

// KONIEC INICJALIZACJI MENU

static const struct menu_item *currMenuPtr = &menu; //wskaznik aktualnego poziomu menu

static int8_t menuindex = 0; //aktualnie wybrany element menu
static int8_t menufirstpos = 0; //nr linii wyswietlanej w pierwszym wiersz LCD

const struct menu_item *GetMenuItem(uint8_t index) { //podajemy pozycje menu ktora chcemy wyszukac
	const struct menu_item *tmp = currMenuPtr; //aktualny pointer
	while ( (tmp) && ( index > 0 ) ){
		tmp = GetAddr( tmp, next ); //przeszukanie
		--index;
	}
	return tmp; //zwracamy wyszukany
}

void Menu_Start(){
	
}

void MenuClick() { // obsluga zdarzenia klikniecia
	const struct menu_item *tmp = GetMenuItem( menuindex ); //tempa dla aktualnie wybranego menu
	const struct menu_item *submenu = GetAddr( tmp, submenu ); //submenu jesli je ma
	menuitemfuncptr mfptr = GetAddr( tmp, menuitemfunc ); // wyluskujemy funkcje dla niego
	if ( mfptr )
		( *mfptr )(); //jesli ma funkcje przypisana to ja wywoluje
	if ( submenu ){
		//jesli ma submenu to je wywolujemy
		currMenuPtr = submenu; //aktualny wskaznik leci na submenu
		menuindex = 0; //aktualnie wybrany element
		menufirstpos = 0; // nr linii od ktorej zapiszemy mu menu
	}
	Menu_Show(); // POKAZ MENU
}

void Menu_Show(){
	const struct menu_item *tmp = GetMenuItem ( menufirstpos );
	uint8_t i;
	for ( i = 0; i < LCD_ROWS; ++i){ // przejezdzamy przez wiersze
		uint8_t charcnt = 1;
		lcdGoto( 0, i ); //idziemy do tej linii na wyswietlaczu
		if ( ( i + menufirstpos )  == menuindex )
			lcdWriteChar('>'); //wybrany element menu
		else 
			lcdWriteChar(' '); //nie wybrany
		if ( GetAddr( tmp, text ) ) {
			lcdWriteString( GetAddr( tmp, text ) );
			charcnt += strlen_P ( GetAddr (tmp,text) );
		}
		if ( GetAddr( tmp, submenu ) ){
			lcdWriteChar( 0x7E );
			charcnt++;
		}
		for ( ; charcnt < LCD_COLUMNS; ++charcnt)
			lcdWriteChar(' ');
		tmp = GetAddr( tmp, next );
	}
}

void Menu_SelectNext(){

}

void Menu_SelectPrev(){

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
