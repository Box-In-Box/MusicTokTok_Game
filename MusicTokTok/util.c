#include "util.h"

void init() {	//콘솔창 제어
	system("mode con cols=58 lines=20 | title music tok tok");
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) {	//x, y 좌표로 이동
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int foreground, int background) {	//글자, 배경 색으로 설정
	foreground &= 0xf;
	background &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background << 4) | foreground);
}

void noteSound(int note) {	//해당 비프음 출력
	switch (note) {
	case 0:		//mute
		break;
	case 1:		//Do
		Beep(262, 100);
		break;
	case 2:		//Do#
		Beep(277, 100);
		break;
	case 3:		//Re
		Beep(293, 100);
		break;
	case 4:		//Re#
		Beep(311, 100);
		break;
	case 5:		//Mi
		Beep(330, 100);
		break;
	case 6:		//Fa
		Beep(349, 100);
		break;
	case 7:		//Fa#
		Beep(370, 100);
		break;
	case 8:		//Sol
		Beep(392, 100);
		break;
	case 9:		//Sol#
		Beep(415, 100);
		break;
	case 10:	//Ra
		Beep(440, 100);
		break;
	case 11:	//Ra#
		Beep(466, 100);
		break;
	case 12:	//Si
		Beep(494, 100);
		break;
	case 13:	//Do
		Beep(523, 100);
		break;
	case 14:	//Do#
		Beep(554, 100);
		break;
	case 15:	//Re
		Beep(587, 100);
		break;
	case 16:	//Re#
		Beep(622, 100);
		break;
	case 17:	//Mi
		Beep(659, 100);
		break;
	case 18:	//Fa
		Beep(698, 100);
		break;
	case 19:	//Fa#
		Beep(740, 100);
		break;
	case 20:	//Sol
		Beep(784, 100);
		break;
	case 21:	//Sol#
		Beep(831, 100);
		break;
	case 22:	//Ra
		Beep(880, 100);
		break;
	case 23:	//Ra#
		Beep(932, 100);
		break;
	case 24:	//Si#
		Beep(988, 100);
		break;
	case 25:	//Do
		Beep(1047, 100);
		break;
	case 30:	//error
		Beep(138, 100);
	}
}