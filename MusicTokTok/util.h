#include "main.h"

enum COLOR_LIST {
	Black,
	Blue,
	Green,
	Cyan,
	Red,
	Purple,
	Yellow,
	White,
	Gray,
	Light_Blue,
	Light_Green,
	Light_Cyan,
	Light_Red,
	Light_Purple,
	Light_Yellow,
	Bright_White
};

void init();
void gotoxy(int, int);
void setColor(int, int);
void noteSound(int);