#define _CRT_SECURE_NO_WARNINGS

#include "game.h"
#include "util.h"
#include "map.h"

bool isPlay = false;
bool developerMode = false;	// <<< default = false >>>
bool isFirst = true;
bool getHealth = false;
bool isEnding = false;
bool endingcreditplaying = false;

int moveIndex = 0;			//position value
int stageLevel = 1;			//current level
int score = 0;				//current score
int stageLen = 0;			//current stage length	
int soundIndex = 0;			//current sound
int currentKey = 5;			//current inputKey

int bestScore = 0;

int health = 3;
int healthPos[5][2];		//max health is 5

double leftTime = 10;
double leftTimes[6] = { 10, 11, 12, 13, 14, 15 };

//Player Position
int xpos = 0;
int ypos = 0;

//Current Stage, Sound
int stage[100][3];
int sound[100];
int menuSound[32];

//if added a stage, Need edit it
void stageControl() {

	switch (stageLevel) {
	case 1:
		memcpy(stage, stage_1, sizeof(stage_1));
		memcpy(sound, sound_1, sizeof(sound_1));
		stageLen = sizeof(stage_1) / sizeof(stage_1[0]);
		xpos = stage[moveIndex][1] - 2;	// - 2 = left Start, + 2 = right Start
		ypos = stage[moveIndex][0];
		//start health position setting
		for (int i = 0; i < health; i++) {
			healthPos[i][0] = xpos - (2 * (i + 1));
			healthPos[i][1] = ypos;
		}
		break;
	case 2:
		memcpy(stage, stage_2, sizeof(stage_2));
		memcpy(sound, sound_2, sizeof(sound_2));
		stageLen = sizeof(stage_2) / sizeof(stage_2[0]);
		xpos = stage[moveIndex][1] + 2;
		ypos = stage[moveIndex][0];
		break;
	case 3:
		memcpy(stage, stage_3, sizeof(stage_3));
		memcpy(sound, sound_3, sizeof(sound_3));
		stageLen = sizeof(stage_3) / sizeof(stage_3[0]);
		xpos = stage[moveIndex][1] + 2;
		ypos = stage[moveIndex][0];
		break;
	case 4:
		memcpy(stage, stage_4, sizeof(stage_4));
		memcpy(sound, sound_4, sizeof(sound_4));
		stageLen = sizeof(stage_4) / sizeof(stage_4[0]);
		xpos = stage[moveIndex][1] - 2;
		ypos = stage[moveIndex][0];
		break;
	case 5:
		memcpy(stage, stage_5, sizeof(stage_5));
		memcpy(sound, sound_5, sizeof(sound_5));
		stageLen = sizeof(stage_5) / sizeof(stage_5[0]);
		xpos = stage[moveIndex][1] + 2;
		ypos = stage[moveIndex][0] - 1;
		break;
	case 6:
		memcpy(stage, stage_6, sizeof(stage_6));
		memcpy(sound, sound_6, sizeof(sound_6));
		stageLen = sizeof(stage_6) / sizeof(stage_6[0]);
		xpos = stage[moveIndex][1];
		ypos = stage[moveIndex][0] + 1;
		break;
	case 7:
		memcpy(stage, stage_7, sizeof(stage_7));
		memcpy(sound, sound_7, sizeof(sound_7));
		stageLen = sizeof(stage_7) / sizeof(stage_7[0]);
		xpos = stage[moveIndex][1] - 2;
		ypos = stage[moveIndex][0];
		break;
	}
}

//GetKey
void keyControl() {
	currentKey = NOTHING;
	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		currentKey = UP;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		currentKey = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		currentKey = RIGHT;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		currentKey = DOWN;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
		currentKey = ENTER;
	}
}

//Draw Title
void drawTitle() {
	printf("\n\n\n\n");
	setColor(Light_Red, Black); printf("       ##     ##   "); setColor(Light_Yellow, Black); printf("#    #   "); setColor(Light_Green, Black); printf(" #####   ");  setColor(Light_Blue, Black); printf("#####   "); setColor(Light_Purple, Black); printf(" ###       \n");
	setColor(Light_Red, Black); printf("        # # # #    "); setColor(Light_Yellow, Black); printf("#    #   "); setColor(Light_Green, Black); printf("#        ");  setColor(Light_Blue, Black); printf("  #     "); setColor(Light_Purple, Black); printf("#   #      \n");
	setColor(Light_Red, Black); printf("        #  #  #    "); setColor(Light_Yellow, Black); printf("#    #   "); setColor(Light_Green, Black); printf(" ####    ");  setColor(Light_Blue, Black); printf("  #     "); setColor(Light_Purple, Black); printf("#          \n");
	setColor(Light_Red, Black); printf("        #     #    "); setColor(Light_Yellow, Black); printf("#    #   "); setColor(Light_Green, Black); printf("     #   ");  setColor(Light_Blue, Black); printf("  #     "); setColor(Light_Purple, Black); printf("#   #      \n");
	setColor(Light_Red, Black); printf("       ###   ###   "); setColor(Light_Yellow, Black); printf(" ####    "); setColor(Light_Green, Black); printf("#####    ");  setColor(Light_Blue, Black); printf("#####   "); setColor(Light_Purple, Black); printf(" ###       \n");
	setColor(Bright_White, Black);
}
//Draw Menu
int drawMenu() {

	int menuXos = 25;
	int menuYos = 12;
	int menuSoundIndex = 0;

	memcpy(menuSound, menuSound_1, sizeof(menuSound_1));

	gotoxy(menuXos - 2, menuYos);
	setColor(Bright_White, Black);
	printf("> 게임시작");
	gotoxy(menuXos, menuYos + 1);
	setColor(Gray, Black);
	printf("게임정보");
	gotoxy(menuXos, menuYos + 2);
	printf("  종료  ");

	while (1) {
		keyControl();
		switch (currentKey) {
		case UP:
			if (menuYos > 12) {
				gotoxy(menuXos - 2, menuYos);
				printf("  ");
				gotoxy(menuXos - 2, --menuYos);
				setColor(Bright_White, Black);
				printf("> ");

				if (menuYos == 13) {
					gotoxy(menuXos, ++menuYos);
					setColor(Gray, Black);
					printf("  종료  ");
					gotoxy(menuXos, --menuYos);
					setColor(Bright_White, Black);
					printf("게임정보");
				}
				else if (menuYos == 12) {
					gotoxy(menuXos, ++menuYos);
					setColor(Gray, Black);
					printf("게임정보");
					gotoxy(menuXos, --menuYos);
					setColor(Bright_White, Black);
					printf("게임시작");
				}
			}
			if (menuSoundIndex == sizeof(menuSound_1) / sizeof(int))
				menuSoundIndex = 0;
			_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)menuSound[menuSoundIndex], 0, NULL);
			menuSoundIndex++;
			currentKey = NOTHING;
			break;

		case DOWN:
			if (menuYos < 14) {
				gotoxy(menuXos - 2, menuYos);
				printf("  ");
				gotoxy(menuXos - 2, ++menuYos);
				setColor(Bright_White, Black);
				printf("> ");

				if (menuYos == 13) {
					gotoxy(menuXos, --menuYos);
					setColor(Gray, Black);
					printf("게임시작");
					gotoxy(menuXos, ++menuYos);
					setColor(Bright_White, Black);
					printf("게임정보");
				}
				else if (menuYos == 14) {
					gotoxy(menuXos, --menuYos);
					setColor(Gray, Black);
					printf("게임정보");
					gotoxy(menuXos, ++menuYos);
					setColor(Bright_White, Black);
					printf("  종료  ");
				}
			}
			if (menuSoundIndex == sizeof(menuSound_1) / sizeof(int))
				menuSoundIndex = 0;
			_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)menuSound[menuSoundIndex], 0, NULL);
			menuSoundIndex++;
			currentKey = NOTHING;
			break;

		case LEFT:
		case RIGHT:
			if (menuSoundIndex == sizeof(menuSound_1) / sizeof(int))
				menuSoundIndex = 0;
			_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)menuSound[menuSoundIndex], 0, NULL);
			menuSoundIndex++;
			currentKey = NOTHING;
			break;

		case ENTER:
			noteSound(12);
			noteSound(15);
			currentKey = NOTHING;
			return menuYos - 12;
		}
	}
}

//Draw Map
void drawMap() {
	system("cls");
	int h, w;
	//UI
	for (h = 0; h < sizeof(ui) / sizeof(ui[0]); h++) {
		for (w = 0; w < sizeof(ui[1]) / sizeof(char); w++) {
			char uiCode = ui[h][w];
			switch (uiCode) {
			case '0': setColor(Bright_White, Black); printf(" "); break;
			case '1': setColor(Bright_White, Bright_White); printf("#"); break;
			}
		}
		printf("\n");
	}
	//MAP
	for (h = 0; h < sizeof(field) / sizeof(field[0]); h++) {
		for (w = 0; w < sizeof(field[1]) / sizeof(char); w++) {
			char mapCode = field[h][w];
			switch (mapCode) {
			case '0': setColor(Bright_White, Black); printf("　"); break;
			case '1': setColor(Bright_White, Bright_White); printf("■"); break;
			}
		}
		if (h != 15) {
			printf("\n");
		}
	}
}
//Draw Stage
void drawStage() {
	srand(time(NULL));

	//Sgtage Setting - get current stage
	stageControl();

	//Draw Player 
	gotoxy(xpos, ypos);
	setColor(Light_Yellow, Black);
	printf("◎");

	//Draw KeySet
	for (int index = 0; index < stageLen; index++) {
		int random = rand() % 5;
		switch (random) {
		case 0:
			gotoxy(stage[index][1], stage[index][0]);
			stage[index][2] = UP;
			setColor(Light_Purple, Black);
			printf("↑");
			break;
		case 1:
			gotoxy(stage[index][1], stage[index][0]);
			stage[index][2] = DOWN;
			setColor(Light_Red, Black);
			printf("↓");
			break;
		case 2:
			gotoxy(stage[index][1], stage[index][0]);
			stage[index][2] = LEFT;
			setColor(Light_Green, Black);
			printf("←");
			break;
		case 3:
			gotoxy(stage[index][1], stage[index][0]);
			stage[index][2] = RIGHT;
			setColor(Light_Yellow, Black);
			printf("→");
			break;
		case 4:
			random = rand() % 8;
			gotoxy(stage[index][1], stage[index][0]);
			if (random == 0) {
				setColor(Light_Yellow, Black);
				stage[index][2] = ENTER_GOLD;
			}
			else {
				setColor(Light_Blue, Black);
				stage[index][2] = ENTER;
			}
			printf("♬");
			break;
		}
	}
}

//Game Loop
void update() {
	isPlay = true;
	drawMap();
	drawStage();
	drawHealth();
	againTimerSet();
	if (isFirst) {
		_beginthreadex(NULL, 0, (_beginthreadex_proc_type)timer, NULL, 0, NULL);
		isFirst = false;
	}
	while (isPlay) {
		keyControl();
		//please check the developerMode is false, it is a developer option
		switch (currentKey) {
		case UP:
			if (stage[moveIndex][2] == UP || developerMode) {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)sound[soundIndex], 0, NULL);
				score++;
			}
			else {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)30, 0, NULL);
				removeHealth();
				health--;
			}
			move();
			soundIndex++;
			currentKey = NOTHING;
			break;
		case DOWN:
			if (stage[moveIndex][2] == DOWN || developerMode) {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)sound[soundIndex], 0, NULL);
				score++;
			}
			else {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)30, 0, NULL);
				removeHealth();
				health--;
			}
			move();
			soundIndex++;
			currentKey = NOTHING;
			break;
		case LEFT:
			if (stage[moveIndex][2] == LEFT || developerMode) {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)sound[soundIndex], 0, NULL);
				score++;
			}
			else {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)30, 0, NULL);
				removeHealth();
				health--;
			}
			move();
			soundIndex++;
			currentKey = NOTHING;
			break;
		case RIGHT:
			if (stage[moveIndex][2] == RIGHT || developerMode) {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)sound[soundIndex], 0, NULL);
				score++;
			}
			else {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)30, 0, NULL);
				removeHealth();
				health--;
			}
			move();
			soundIndex++;
			currentKey = NOTHING;
			break;
		case ENTER:
			if (stage[moveIndex][2] == ENTER || developerMode && stage[moveIndex][2] != ENTER_GOLD) {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)sound[soundIndex], 0, NULL);
				score++;
			}
			else if (stage[moveIndex][2] == ENTER_GOLD || developerMode) {
				if (health < 5) {
					getHealth = true;
					health++;
				}
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)sound[soundIndex], 0, NULL);
				score++;
			}
			else {
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)30, 0, NULL);
				removeHealth();
				health--;
			}
			move();
			soundIndex++;
			currentKey = NOTHING;
			break;
		case NOTHING:
			break;
		}
		drawUi();
		if (moveIndex == stageLen) {
			score += (int)(leftTime * 10);
			nextStage();
		}
		if (health < 0 && !developerMode || leftTime <= 0 && !isEnding && !developerMode) {
			failed();
		}
	}
	reset();
}

//Remove Player Character
void removePlayer() {
	//for first move
	if (moveIndex == 0) {
		gotoxy(xpos, ypos);
		printf("  ");
	}
	//after that move
	else {
		gotoxy(stage[moveIndex - 1][1], stage[moveIndex - 1][0]);
		printf("  ");
	}
}
//Remove last health
void removeHealth() {
	if (getHealth) {	//체력을 먹었다면 플레이어가 이동하면서 자리가 비기 때문에 체력을 지울 필요 없음
		getHealth = false;
		return;
	}
	gotoxy(healthPos[health - 1][0], healthPos[health - 1][1]);
	printf("  ");
}
//Remove all health
void removeAllHealth() {	//스테이지 클리어에 필요
	for (int i = 0; i < health; i++) {
		gotoxy(healthPos[i][0], healthPos[i][1]);
		printf("  ");
	}
}

//Setting Health Position
void setLeftHealth() {
	for (int i = health - 1; i > 0; i--) {
		healthPos[i][0] = healthPos[i - 1][0];
		healthPos[i][1] = healthPos[i - 1][1];
	}

	if (moveIndex == 0) {
		healthPos[0][0] = xpos;
		healthPos[0][1] = ypos;
	}
	else {
		healthPos[0][0] = stage[moveIndex - 1][1];
		healthPos[0][1] = stage[moveIndex - 1][0];
	}
}

//Player Move
void move() {
	if (health == 0)
		removePlayer();
	else
		removeHealth();

	setColor(Light_Yellow, Black);
	gotoxy(stage[moveIndex][1], stage[moveIndex][0]);
	printf("◎");
	setLeftHealth();
	drawHealth();
	moveIndex++;
}

//Next - stage Clear
void nextStage() {
	//ending
	if (stageLevel == maxLevel)
		ending();
	//nextStage
	else {
		removePlayer();
		removeAllHealth();
		setColor(Light_Yellow, Black);
		gotoxy(16, 11);
		printf(" S P A C E  T O  N E X T ");
		while (1) {
			keyControl();
			if (currentKey == ENTER) {
				gotoxy(16, 11);
				printf("                         ");
				moveIndex = 0;
				soundIndex = 0;
				stageLevel++;
				leftTime = leftTimes[stageLevel - 1];
				isFirst = false;
				drawStage();
				drawHealth();
				drawUi();
				break;
			}
		}
	}
}

void timer() {
	while (1) {
		Sleep(100);
		leftTime -= 0.1;
	}
}

//Ui Draw
void drawUi() {
	setColor(Light_Red, Black);
	gotoxy(6, 2);
	printf("STAGE : %d", stageLevel);
	setColor(Light_Blue, Black);
	gotoxy(23, 2);
	printf("Timer : %0.1lf", leftTime);
	setColor(Light_Yellow, Black);
	gotoxy(44, 2);
	printf("SCORE : %d", score);

	//[Test] Show Health To Text
	/*
	setColor(Light_Green, Black);
	gotoxy(46, 18);
	printf("Health : %d", health);
	*/
}

//Health Draw
void drawHealth() {
	for (int i = 0; i < health; i++) {
		setColor(Light_Red, Black);
		gotoxy(healthPos[i][0], healthPos[i][1]);
		printf("♥");
	}
}

//Values initialization
void reset() {
	isPlay = false;
	moveIndex = 0;
	stageLevel = 1;
	score = 0;
	stageLen = 0;
	soundIndex = 0;
	health = 3;
	leftTime = leftTimes[stageLevel - 1];
	xpos = 0;
	ypos = 0;
}


void againTimerSet() {
	leftTime = leftTimes[stageLevel - 1];
}

//Game Failed
void failed() {
	system("cls");

	reset();
	int count = 0;
	int failedSoundCount[16] = { 0, 1, 0, 1, 2, 1, 0, 1, 3, 4, 3, 4, 3, 4, 3, 4 };

	gotoxy(23, 9);
	setColor(Bright_White, Black); printf("[ "); setColor(White, Black); printf("Failed"); setColor(Gray, Black); printf("..."); setColor(Bright_White, Black); printf(" ]");

	while (1) {
		keyControl();
		if (currentKey == ENTER) {
			Sleep(50);
			noteSound(15);
			noteSound(12);
			break;
		}
		Sleep(120);
		if (count == sizeof(failedSoundCount) / sizeof(int))
			count = 0;
		if (soundIndex == 0) {
			switch (failedSoundCount[count++]) {
			case 0:
				memcpy(sound, failedSound_0, sizeof(failedSound_0));
				break;
			case 1:
				memcpy(sound, failedSound_1, sizeof(failedSound_1));
				break;
			case 2:
				memcpy(sound, failedSound_2, sizeof(failedSound_2));
				break;
			case 3:
				memcpy(sound, failedSound_3, sizeof(failedSound_3));
				break;
			case 4:
				memcpy(sound, failedSound_4, sizeof(failedSound_4));
				break;
			}
		}
		_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)sound[soundIndex], 0, NULL);
		soundIndex++;
		if (soundIndex == sizeof(failedSound_0) / sizeof(int))
			soundIndex = 0;
	}
}

//Game Ending
void ending() {
	system("cls");

	isEnding = true;
	endingcreditplaying = true;
	int sleepCount = 6;				//sleep횟수 카운트
	int creditsXpos = 25;			//크레딧 Y위치
	int creditsYpos = 8;			//크레딧 X위치
	int line = 0;					//크레딧 N번째 줄
	int totalScore = score;			//스코어 temp

	int endingCreditSound[288];		//엔딩크레딧은 사운드가 길어 따로 사운드배열 선언 
	int endingSoundCount = 0;		//사운드 반복 카운트	

	memcpy(endingCreditSound, endingSound, sizeof(endingSound));

	if (totalScore >= bestScore)	//스코어 저장
		saveScore(totalScore);

	gotoxy(creditsXpos, creditsYpos);
	setColor(Bright_White, Black);	printf("[ "); setColor(Light_Yellow, Black); printf("Clear"); setColor(Bright_White, Black); printf(" ]");

	reset();
	while (1) {
		keyControl();
		if (!endingcreditplaying && currentKey == ENTER) {
			leftTime = 10;		//스페이스바 누르자마자 실패되는것 방지
			isEnding = false;
			Sleep(50);
			break;
		}

		Sleep(130);
		sleepCount++;

		_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)endingSound[soundIndex], 0, NULL);
		soundIndex++;

		if (soundIndex == sizeof(endingSound) / sizeof(int))
			soundIndex = 0;

		//Show Score
		if (totalScore >= bestScore) {
			gotoxy(41, 18);
			newBestScore(totalScore); //Twinkle Score
		}
		else {
			gotoxy(44, 18);
			setColor(Light_Yellow, Black); printf("Score"); setColor(White, Black);  printf(" : %d", totalScore); //normal Score
		}

		if (sleepCount % 8 == 0 && line < 44) {
			system("cls");

			if (totalScore >= bestScore) {
				gotoxy(41, 18);
				newBestScore(totalScore); //Twinkle Score
			}
			else {
				gotoxy(44, 18);
				setColor(Light_Yellow, Black); printf("Score"); setColor(White, Black);  printf(" : %d", totalScore); //normal Score
			}

			//Show Credit
			if (creditsYpos > 4) {
				gotoxy(creditsXpos, creditsYpos);
				setColor(Bright_White, Black);	printf("[ "); setColor(Light_Yellow, Black); printf("Clear"); setColor(Bright_White, Black); printf(" ]");
			}
			setColor(Bright_White, Black);
			if (line >= 2 && creditsYpos > -4) {
				gotoxy(creditsXpos - 3, creditsYpos + 8);
				setColor(Light_Yellow, Black);  printf("제작자"); setColor(Bright_White, Black); printf(" : 이배원");
			}
			if (line >= 4 && creditsYpos > -6) {
				gotoxy(creditsXpos - 2, creditsYpos + 10);
				setColor(Light_Yellow, Black); printf("기획"); setColor(Bright_White, Black); printf(" : 이배원");
			}
			if (line >= 6 && creditsYpos > -8) {
				gotoxy(creditsXpos - 6, creditsYpos + 12);
				setColor(Light_Yellow, Black); printf("원작 게임"); setColor(Bright_White, Black); printf("  : 뮤직톡톡");
			}
			if (line >= 9 && creditsYpos > -11) {
				gotoxy(creditsXpos - 5, creditsYpos + 15);
				setColor(Light_Yellow, Black); printf("1스테이지"); setColor(Bright_White, Black); printf(" - 옹달샘");
			}
			if (line >= 11 && creditsYpos > -13) {
				gotoxy(creditsXpos - 6, creditsYpos + 17);
				setColor(Light_Yellow, Black); printf("2스테이지"); setColor(Bright_White, Black); printf(" - 똑같아요");
			}
			if (line >= 13 && creditsYpos > -15) {
				gotoxy(creditsXpos - 5, creditsYpos + 19);
				setColor(Light_Yellow, Black); printf("3스테이지"); setColor(Bright_White, Black); printf(" - 작은별");
			}
			if (line >= 15 && creditsYpos > -17) {
				gotoxy(creditsXpos - 6, creditsYpos + 21);
				setColor(Light_Yellow, Black); printf("4스테이지"); setColor(Bright_White, Black); printf(" - 아기상어");
			}
			if (line >= 17 && creditsYpos > -19) {
				gotoxy(creditsXpos - 10, creditsYpos + 23);
				setColor(Light_Yellow, Black); printf("5스테이지"); setColor(Bright_White, Black); printf(" - 나의 마음을 담아");
			}
			if (line >= 19 && creditsYpos > -21) {
				gotoxy(creditsXpos - 7, creditsYpos + 25);
				setColor(Light_Yellow, Black); printf("6스테이지"); setColor(Bright_White, Black); printf(" - 검정고무신");
			}
			if (line >= 21 && creditsYpos > -23) {
				gotoxy(creditsXpos - 7, creditsYpos + 27);
				setColor(Light_Yellow, Black); printf("7스테이지"); setColor(Bright_White, Black); printf(" - ");
			}
			if (line >= 23 && creditsYpos > -25) {
				gotoxy(creditsXpos - 7, creditsYpos + 29);
				setColor(Light_Yellow, Black); printf("8스테이지"); setColor(Bright_White, Black); printf(" - ");
			}
			if (line >= 25 && creditsYpos > -27) {
				gotoxy(creditsXpos - 7, creditsYpos + 31);
				setColor(Light_Yellow, Black); printf("9스테이지"); setColor(Bright_White, Black); printf(" - ");
			}
			if (line >= 27 && creditsYpos > -29) {
				gotoxy(creditsXpos - 7, creditsYpos + 33);
				setColor(Light_Yellow, Black); printf("10스테이지"); setColor(Bright_White, Black); printf(" - ");
			}
			if (line >= 30 && creditsYpos > -32) {
				gotoxy(creditsXpos - 8, creditsYpos + 36);
				setColor(Light_Yellow, Black); printf("실패곡"); setColor(Bright_White, Black); printf(" - Pink Soldiers");
			}
			if (line >= 32 && creditsYpos > -34) {
				gotoxy(creditsXpos - 8, creditsYpos + 38);
				setColor(Light_Yellow, Black); printf("엔딩곡"); setColor(Bright_White, Black); printf(" - 밋치리네코 행진");
			}
			if (line >= 38 && line < 43) {
				gotoxy(creditsXpos - 5, creditsYpos + 44);
				printf("Thank you for play");
			}
			if (line == 43) {
				gotoxy(creditsXpos - 5, creditsYpos + 45);
				printf("Thank you for play"); setColor(Light_Red, Black); printf("!");
				gotoxy(23, 14);
				setColor(Gray, Black);
				printf("Space to Menu");
				endingcreditplaying = false; //Finish Endingcredit from this line //키 입력 가능
			}
			creditsYpos--;
			line++;
		}
	}
}

void newBestScore(int totalScore) {
	static totalscoreCount = 0;
	if (totalscoreCount == 8)
		totalscoreCount = 0;
	switch (totalscoreCount) {
		gotoxy(40, 18);
	case 0:
		setColor(Red, Black);			printf("N");
		setColor(Light_Red, Black);		printf("e");
		setColor(Light_Yellow, Black);	printf("w ");
		setColor(Light_Green, Black);	printf("S");
		setColor(Light_Cyan, Black);	printf("c");
		setColor(Light_Blue, Black);	printf("o");
		setColor(Purple, Black);		printf("r");
		setColor(Light_Purple, Black);	printf("e");

		setColor(Gray, Black);			printf(" : %d", totalScore);
		break;
	case 1:
		setColor(Light_Purple, Black);	printf("N");
		setColor(Red, Black);			printf("e");
		setColor(Light_Red, Black);		printf("w ");
		setColor(Light_Yellow, Black);	printf("S");
		setColor(Light_Green, Black);	printf("c");
		setColor(Light_Cyan, Black);	printf("o");
		setColor(Light_Blue, Black);	printf("r");
		setColor(Purple, Black);		printf("e");

		setColor(White, Black);			printf(" : %d", totalScore);
		break;
	case 2:
		setColor(Purple, Black);		printf("N");
		setColor(Light_Purple, Black);	printf("e");
		setColor(Red, Black);			printf("w ");
		setColor(Light_Red, Black);		printf("S");
		setColor(Light_Yellow, Black);	printf("c");
		setColor(Light_Green, Black);	printf("o");
		setColor(Light_Cyan, Black);	printf("r");
		setColor(Light_Blue, Black);	printf("e");

		setColor(Bright_White, Black);  printf(" : %d", totalScore);
		break;
	case 3:
		setColor(Light_Blue, Black);	printf("N");
		setColor(Purple, Black);		printf("e");
		setColor(Light_Purple, Black);	printf("w ");
		setColor(Red, Black);			printf("S");
		setColor(Light_Red, Black);		printf("c");
		setColor(Light_Yellow, Black);	printf("o");
		setColor(Light_Green, Black);	printf("r");
		setColor(Light_Cyan, Black);	printf("e");

		setColor(Bright_White, Black);  printf(" : %d", totalScore);
		break;
	case 4:
		setColor(Light_Cyan, Black);	printf("N");
		setColor(Light_Blue, Black);	printf("e");
		setColor(Purple, Black);		printf("w ");
		setColor(Light_Purple, Black);	printf("S");
		setColor(Red, Black);			printf("c");
		setColor(Light_Red, Black);		printf("o");
		setColor(Light_Yellow, Black);	printf("r");
		setColor(Light_Green, Black);	printf("e");

		setColor(Bright_White, Black);  printf(" : %d", totalScore);
		break;
	case 5:
		setColor(Light_Green, Black);	printf("N");
		setColor(Light_Cyan, Black);	printf("e");
		setColor(Light_Blue, Black);	printf("w ");
		setColor(Purple, Black);		printf("S");
		setColor(Light_Purple, Black);	printf("c");
		setColor(Red, Black);			printf("o");
		setColor(Light_Red, Black);		printf("r");
		setColor(Light_Yellow, Black);	printf("e");

		setColor(Bright_White, Black);  printf(" : %d", totalScore);
		break;
	case 6:
		setColor(Light_Yellow, Black);	printf("N");
		setColor(Light_Green, Black);	printf("e");
		setColor(Light_Cyan, Black);	printf("w ");
		setColor(Light_Blue, Black);	printf("S");
		setColor(Purple, Black);		printf("c");
		setColor(Light_Purple, Black);	printf("o");
		setColor(Red, Black);			printf("r");
		setColor(Light_Red, Black);		printf("e");

		setColor(White, Black);			printf(" : %d", totalScore);
		break;
	case 7:
		setColor(Light_Red, Black);		printf("N");
		setColor(Light_Yellow, Black);	printf("e");
		setColor(Light_Green, Black);	printf("w ");
		setColor(Light_Cyan, Black);	printf("S");
		setColor(Light_Blue, Black);	printf("c");
		setColor(Purple, Black);		printf("o");
		setColor(Light_Purple, Black);	printf("r");
		setColor(Red, Black);			printf("e");

		setColor(Gray, Black);			printf(" : %d", totalScore);
		break;
	}
	totalscoreCount++;
}

void saveScore(const int _totalScore) {
	FILE* file;
	file = fopen("TokTokScore.txt", "w");
	if (file == NULL) {
		bestScore = -1;
	}
	else {
		fprintf(file, "%d", _totalScore);
		fclose(file);
	}
}

void getScore() {
	FILE* file;
	file = fopen("TokTokScore.txt", "r");
	if (file == NULL) {
		bestScore = 0;
	}
	else {
		int test = fscanf(file, "%d", &bestScore);
		fclose(file);
	}
}

//Infomation
void drawInfo() {
	system("cls");
	printf("\n\n\n");
	setColor(Bright_White, Black);	printf("                        ");
	printf("[ "); setColor(Light_Yellow, Black); printf("조작법"); setColor(Bright_White, Black); printf(" ]\n\n");
	printf("                 ");
	setColor(Light_Purple, Black);	printf("↑");
	setColor(Bright_White, Black);	printf(", ");
	setColor(Light_Red, Black);		printf("↓");
	setColor(Bright_White, Black);	printf(", ");
	setColor(Light_Green, Black);	printf("←");
	setColor(Bright_White, Black);	printf(", ");
	setColor(Light_Yellow, Black);	printf("→");
	setColor(Bright_White, Black);	printf(", ");
	setColor(Light_Blue, Black);	printf("♬");
	setColor(Bright_White, Black);	printf("(SPACE)");
	printf("\n\n");
	printf("                       ");
	setColor(Light_Yellow, Black);  printf("♬"); setColor(Bright_White, Black); printf(" = "); setColor(Light_Red, Black); printf("♥"); setColor(Bright_White, Black); printf(" + 1");
	printf("\n\n\n");
	setColor(Bright_White, Black); printf("                    BestScore [ "); setColor(Light_Yellow, Black); printf("%d", bestScore); setColor(Bright_White, Black); printf(" ] \n\n\n");
	setColor(Bright_White, Black);  printf("            제작자 : 이배원 - "); printf("dgf0000"); setColor(Light_Green, Black); printf("@naver.com\n\n\n");
	setColor(Bright_White, Black);  printf("                       >  확   인");

	while (1) {
		keyControl();
		if (currentKey == ENTER) {
			noteSound(15);
			noteSound(12);
			break;
		}
	}
}