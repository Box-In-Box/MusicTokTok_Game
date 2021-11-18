#include "main.h"
#include "game.h" 

int main() {
	init();
	while (1) {
		getScore();
		drawTitle();
		int select = drawMenu();
		switch (select) {
		case 0:
			update();
			break;
		case 1:
			drawInfo();
			break;
		case 2:
			return 0;
		}
		system("cls");
	}
}