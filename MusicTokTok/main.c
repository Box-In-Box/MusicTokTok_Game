#include "main.h"
#include "game.h"
#include "util.h" 

int main() {
	init();	//���α׷� ���� �� �ܼ�â ����
	while (1) {
		getScore();		//score���Ͽ��� bestScore�� ������
		drawTitle();	//Ÿ��Ʋ �׸� ���
		int select = drawMenu();
		switch (select) {
		case 0:			//���� ����
			update();
			break;
		case 1:			//���� ����
			drawInfo();
			break;
		case 2:			//���� ����
			return 0;
		}
		system("cls");
	}
}