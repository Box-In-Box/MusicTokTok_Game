#include "main.h"
#include "game.h"
#include "util.h" 

int main() {
	init();	//프로그램 시작 시 콘솔창 설정
	while (1) {
		getScore();		//score파일에서 bestScore를 가져옴
		drawTitle();	//타이틀 그림 출력
		int select = drawMenu();
		switch (select) {
		case 0:			//게임 시작
			update();
			break;
		case 1:			//게임 정보
			drawInfo();
			break;
		case 2:			//게임 종료
			return 0;
		}
		system("cls");
	}
}