#include "main.h"

enum COLOR_LIST {	//컬러 리스트
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

void init();				//콘솔창 제어
void gotoxy(int, int);		//x, y 좌표로 이동
void setColor(int, int);	//글자, 배경 색으로 설정
void noteSound(int);		//해당 비프음 출력