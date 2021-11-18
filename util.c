#include "util.h"

void init() {
	system("mode con cols=58 lines=20 | title music tok tok");
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int foreground, int background) {
	foreground &= 0xf;
	background &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background << 4) | foreground);
}

void noteSound(int note) {
	switch (note) {
	case 0:		//mute
		break;
	case 1:		//Do
		Beep(262, 100);
		break;
	case 2:		//Re
		Beep(293, 100);
		break;
	case 3:		//Mi
		Beep(330, 100);
		break;
	case 4:		//Fa
		Beep(349, 100);
		break;
	case 5:		//Sol
		Beep(392, 100);
		break;
	case 6:		//Ra
		Beep(440, 100);
		break;
	case 7:		//Si
		Beep(494, 100);
		break;
	case 8:		//Do
		Beep(513, 100);
		break;
	case 9:		//Re
		Beep(587, 100);
		break;
	case 10:	//Mi
		Beep(659, 100);
		break;
	case 11:	//Fa
		Beep(698, 100);
		break;
	case 12:	//Fa#
		Beep(367, 100);
		break;
	case 13:	//Si#
		Beep(587, 100);
		break;
	case 14:	//do#
		Beep(554, 100);
		break;
	case 15:	//fa#
		Beep(740, 100);
		break;
	case 16:	//sol#
		Beep(415, 100);
		break;
	case 17:	//re#
		Beep(622, 100);
		break;
	case 18:	//sol
		Beep(784, 100);
		break;
	case 19:	//sol#
		Beep(830, 100);
		break;
	case 20:	//ra#
		Beep(880, 100);
		break;
	case 30:	//error
		Beep(138, 100);
	}
}