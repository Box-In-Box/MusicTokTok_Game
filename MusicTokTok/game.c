#define _CRT_SECURE_NO_WARNINGS //fscanf 오류 경고 메세지 제거를 위한 정의

#include "game.h"
#include "util.h"
#include "map.h"

bool isPlay = false;
bool developerMode = false;			// <<< default = false >>>	// true : 체력이 줄지 않음, 다른 키를 눌러도 맞은 판정, 타이머 over 없음
bool developerMode_Text = false;	//현재 스테이지의 남은 개수, 현재 체력
bool isFirst = true;				//프로그램을 처음 켜서 시작 시
bool getHealth = false;
bool isEnding = false;
bool endingcreditplaying = false;

int moveIndex = 0;			//position value		//스테이지가 시작되고 움직인 횟수
int stageLevel = 1;			//current level			//현재 스테이지 레벨_스테이지 관리
int score = 0;				//current score			//나의 score
int stageLen = 0;			//current stage length	//스테이지 끝을 알기위함
int soundIndex = 0;			//current sound			//현재 나와야될 소리 관리
int currentKey = 5;			//current inputKey		//현재 눌려지고 있는 키

int bestScore = 0;			//현재 최고기록

int health = 3;				//기본 추가체력
int healthPos[5][2];		//max health is 5	//추가체력 최대 개수 5개

double leftTime = 9.5;
double leftTimes[10] = { 9.5, 10.5, 13, 14, 14.8, 16.5, 19.6, 22.7, 24, 27 }; //1stage => 0.5sec -- 0.025sec

//Player Position
int xpos = 0;		//처음 위치 조정때만 사용됨
int ypos = 0;

//Current Stage, Sound
int stage[100][3];		//현재 스테이지
int sound[100];			//현재 사운드
int menuSound[32];		//for 오징어게임 ost 이스터에그

//if added a stage, Need edit it
void stageControl() {	//현재 스테이지, 노래를 가져오는 함수, 초기위치 세팅

	switch (stageLevel) {
	case 1:
		memcpy(stage, stage_1, sizeof(stage_1));
		memcpy(sound, sound_1, sizeof(sound_1));
		stageLen = sizeof(stage_1) / sizeof(stage_1[0]);
		xpos = stage[moveIndex][1] - 2;	// - 2 = left Start, + 2 = right Start
		ypos = stage[moveIndex][0];
		//start health position setting
		for (int i = 0; i < health; i++) {		//처음 스테이지를 시작 할 때는 체력의 위치를 정해줘야 함
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
	case 8:
		memcpy(stage, stage_8, sizeof(stage_8));
		memcpy(sound, sound_8, sizeof(sound_8));
		stageLen = sizeof(stage_8) / sizeof(stage_8[0]);
		xpos = stage[moveIndex][1] + 2;
		ypos = stage[moveIndex][0];
		break;
	case 9:
		memcpy(stage, stage_9, sizeof(stage_9));
		memcpy(sound, sound_9, sizeof(sound_9));
		stageLen = sizeof(stage_9) / sizeof(stage_9[0]);
		xpos = stage[moveIndex][1] + 2;
		ypos = stage[moveIndex][0] - 1;
		break;
	case 10:
		memcpy(stage, stage_10, sizeof(stage_10));
		memcpy(sound, sound_10, sizeof(sound_10));
		stageLen = sizeof(stage_10) / sizeof(stage_10[0]);
		xpos = stage[moveIndex][1];
		ypos = stage[moveIndex][0] + 1;
		break;
	}
}

//GetKey
void keyControl() {		//키 입력 컨트롤러
	currentKey = NOTHING;
	if (GetAsyncKeyState(VK_UP) & 0x0001 || GetAsyncKeyState(0x57) & 0x0001) {		//0x57 == w    //for 왼손잡이
		currentKey = UP;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x0001 || GetAsyncKeyState(0x41) & 0x0001) {	//0x57 == a
		currentKey = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001 || GetAsyncKeyState(0x44) & 0x0001) {	//0x57 == d
		currentKey = RIGHT;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001 || GetAsyncKeyState(0x53) & 0x0001) {	//0x57 == s
		currentKey = DOWN;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x0001 || GetAsyncKeyState(VK_RETURN) & 0x0001) {
		currentKey = ENTER;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
		currentKey = ESCAPE;
	}
}

//Draw Title
void drawTitle() {	//메인 화면 타이틀 그림
	printf("\n\n\n\n");
	setColor(Light_Red, Black); printf("       ##     ##   "); setColor(Light_Yellow, Black); printf("#    #   "); setColor(Light_Green, Black); printf(" #####   ");  setColor(Light_Blue, Black); printf("#####   "); setColor(Light_Purple, Black); printf(" ###       \n");
	setColor(Light_Red, Black); printf("        # # # #    "); setColor(Light_Yellow, Black); printf("#    #   "); setColor(Light_Green, Black); printf("#        ");  setColor(Light_Blue, Black); printf("  #     "); setColor(Light_Purple, Black); printf("#   #      \n");
	setColor(Light_Red, Black); printf("        #  #  #    "); setColor(Light_Yellow, Black); printf("#    #   "); setColor(Light_Green, Black); printf(" ####    ");  setColor(Light_Blue, Black); printf("  #     "); setColor(Light_Purple, Black); printf("#          \n");
	setColor(Light_Red, Black); printf("        #     #    "); setColor(Light_Yellow, Black); printf("#    #   "); setColor(Light_Green, Black); printf("     #   ");  setColor(Light_Blue, Black); printf("  #     "); setColor(Light_Purple, Black); printf("#   #      \n");
	setColor(Light_Red, Black); printf("       ###   ###   "); setColor(Light_Yellow, Black); printf(" ####    "); setColor(Light_Green, Black); printf("#####    ");  setColor(Light_Blue, Black); printf("#####   "); setColor(Light_Purple, Black); printf(" ###       \n");
	setColor(Bright_White, Black);
}
//Draw Menu
int drawMenu() {	//메인 화면 키 조작 

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

	while (1) {		//키 입력 시 '>'이동과 다른 글자들을 음영 처리를 위한 설정
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
			return menuYos - 12;	//초기값이 12이기 때문에 현재 선택된 값에서 12를 빼주면 게임시작 = 0, 게임정보 = 1, 종료 = 2가 됨
		}
	}
}

//Draw Map
void drawMap() {	//문자를 그림으로 바꿔주는 함수
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
void drawStage() {	//화면에 해당 스테이지를 그리는 함수
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
			random = rand() % 8;		//추가체력 확률
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
void update() {	//main에서 게임 시작 시 이 함수로 넘어오며 이 루프를 반복하게 됨
	isPlay = true;
	drawMap();			//맵을 그림
	drawStage();		//스테이지를 그림
	drawHealth();		//체력들을 그림
	againTimerSet();	//타이머 설정
	if (isFirst) {
		_beginthreadex(NULL, 0, (_beginthreadex_proc_type)timer, NULL, 0, NULL);
		isFirst = false;
	}
	while (isPlay) {
		keyControl();
		switch (currentKey) {
		case UP:
			if (stage[moveIndex][2] == UP || developerMode) {	//알맞은 방향키를 입력 시
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)sound[soundIndex], 0, NULL);
				score++;
			}
			else {												//잘못된 방향키를 입력 시
				_beginthreadex(NULL, 0, (_beginthreadex_proc_type)noteSound, (int*)30, 0, NULL);	//note sound 30 = 틀렸을 때 소리
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
		case ESCAPE:		//esc를 누를 시 게임 탈출
			isPlay = false;
			currentKey = NOTHING;
			break;
		case NOTHING:
			break;
		}
		drawUi();
		if (moveIndex == stageLen) {		//현재 스테이지가 끝났을 때
			score += (int)(leftTime * 10);	//스코어 += 남은시간 * 10
			nextStage();					//다음 스테이지로 이동
		}
		if (health < 0 && !developerMode || leftTime <= 0 && !isEnding && !developerMode) {	//실패엔딩
			failed();
		}
	}
	reset();
}

//Remove Player Character
void removePlayer() {	//방향키 입력시 캐릭터 있던 자리를 비우는 함수
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
void removeHealth() {	//추가체력 있던 곳의 자리를 비우는 함수
	if (getHealth) {	//체력을 먹었다면 플레이어가 이동하면서 자리가 비기 때문에 체력을 지울 필요 없음
		getHealth = false;
		return;
	}
	gotoxy(healthPos[health - 1][0], healthPos[health - 1][1]);
	printf("  ");
}
//Remove all health
void removeAllHealth() {	//스테이지 클리어 시 SPACE  TO  NEXT을 출력해주어야 하므로 체력들을 전부 지워주는 함수
	for (int i = 0; i < health; i++) {
		gotoxy(healthPos[i][0], healthPos[i][1]);
		printf("  ");
	}
}

//Setting Health Position
void setLeftHealth() {		//체력들의 위치를 재조정 하는 함수
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
void move() {		//방향키 입력을 받을 시 실행되는 함수
	if (health == 0)
		removePlayer();	//움직이기 전 플레이어의 위치에 체력을 그려야 하기 때문에 플레이어를 안지워도 무방
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
void nextStage() {	//스테이지 클리어시 실행된는 함수
	//ending
	if (stageLevel == maxLevel)	//마지막 스테이지 클리어시 엔딩으로 넘어감
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
			else if (currentKey == ESCAPE) {
				isPlay = false;
				break;
			}

		}
	}
}

void timer() {	//쉬운 구성을 위해 타이머는 Sleep으로 구현, 쓰레드로 이 함수를 호출
	while (1) {
		Sleep(100);
		leftTime -= 0.1;
	}
}

//Ui Draw
void drawUi() {	//화면 위쪽에 제공되는 현재 스테이지, 남은시간, 현재 스코어가 제공됨
	setColor(Light_Red, Black);
	gotoxy(6, 2);
	printf("STAGE : %d", stageLevel);
	setColor(Light_Blue, Black);
	gotoxy(23, 2);
	printf("Timer : %0.1lf", leftTime);
	setColor(Light_Yellow, Black);
	gotoxy(44, 2);
	printf("SCORE : %d", score);

	//[Test] Show Health, Left To Text
	if (developerMode_Text) {
		setColor(Light_Green, Black);
		gotoxy(32, 18);
		printf("Left : %2d", stageLen - moveIndex);
		gotoxy(45, 18);
		printf("Health : %d", health);
	}
}

//Health Draw
void drawHealth() {		//체력들을 그려주는 함수
	for (int i = 0; i < health; i++) {
		setColor(Light_Red, Black);
		gotoxy(healthPos[i][0], healthPos[i][1]);
		printf("♥");
	}
}

//Values initialization
void reset() {	//게임이 끝날 시 변수들을 리셋 해주는 함수
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


void againTimerSet() {	//스테이지 별로 타이머를 조정해주는 함수
	leftTime = leftTimes[stageLevel - 1];
}

//Game Failed
void failed() {	//게임 실패시 실행되는 함수
	system("cls");

	reset();
	int count = 0;
	int failedSoundCount[16] = { 0, 1, 0, 1, 2, 1, 0, 1, 3, 4, 3, 4, 3, 4, 3, 4 };	//같은 음이 많아 배열로 관리

	gotoxy(24, 9);
	setColor(Bright_White, Black); printf("[ "); setColor(White, Black); printf("Failed"); setColor(Bright_White, Black); printf(" ]");
	gotoxy(23, 14);
	setColor(Gray, Black);
	printf("Space to Menu");

	while (1) {
		keyControl();
		if (currentKey == ENTER || currentKey == ESCAPE) {
			noteSound(15);
			noteSound(12);
			Sleep(50);
			break;
		}
		Sleep(120);	//노래박자
		if (count == sizeof(failedSoundCount) / sizeof(int))		//노래 무한반복
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
void ending() {	//모든 스테이지 클리어시 실행되는 함수
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
		if (!endingcreditplaying && currentKey == ENTER || currentKey == ESCAPE) {
			leftTime = 10;		//엔딩이 끝나고 스페이스바 누르자마자 실패되는것 방지
			isEnding = false;
			Sleep(50);
			break;
		}

		Sleep(140);	//노래박자
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

		if (sleepCount % 8 == 0 && line < 43) {	//노래의 음과 크레딧이 같이 올라가기 위해 구현한 장치
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
				setColor(Light_Yellow, Black); printf("1스테이지"); setColor(Bright_White, Black); printf(" : 옹달샘");
			}
			if (line >= 11 && creditsYpos > -13) {
				gotoxy(creditsXpos - 6, creditsYpos + 17);
				setColor(Light_Yellow, Black); printf("2스테이지"); setColor(Bright_White, Black); printf(" : 똑같아요");
			}
			if (line >= 13 && creditsYpos > -15) {
				gotoxy(creditsXpos - 5, creditsYpos + 19);
				setColor(Light_Yellow, Black); printf("3스테이지"); setColor(Bright_White, Black); printf(" : 작은별");
			}
			if (line >= 15 && creditsYpos > -17) {
				gotoxy(creditsXpos - 6, creditsYpos + 21);
				setColor(Light_Yellow, Black); printf("4스테이지"); setColor(Bright_White, Black); printf(" : 아기상어");
			}
			if (line >= 17 && creditsYpos > -19) {
				gotoxy(creditsXpos - 14, creditsYpos + 23);
				setColor(Light_Yellow, Black); printf("5스테이지"); setColor(Bright_White, Black); printf(" : 달빛천사 - 나의 마음을 담아");
			}
			if (line >= 19 && creditsYpos > -21) {
				gotoxy(creditsXpos - 11, creditsYpos + 25);
				setColor(Light_Yellow, Black); printf("6스테이지"); setColor(Bright_White, Black); printf(" : 검정고무신 - 검정고무신");
			}
			if (line >= 21 && creditsYpos > -23) {
				gotoxy(creditsXpos - 18, creditsYpos + 27);
				setColor(Light_Yellow, Black); printf("7스테이지"); setColor(Bright_White, Black); printf(" : 카트캡터 체리 - Catch You Catch Me");
			}
			if (line >= 23 && creditsYpos > -25) {
				gotoxy(creditsXpos - 10, creditsYpos + 29);
				setColor(Light_Yellow, Black); printf("8스테이지"); setColor(Bright_White, Black); printf(" : 이누야샤 - I am");
			}
			if (line >= 25 && creditsYpos > -27) {
				gotoxy(creditsXpos - 17, creditsYpos + 31);
				setColor(Light_Yellow, Black); printf("9스테이지"); setColor(Bright_White, Black); printf(" : 꽃보다 남자 - 내 머리가 나빠서");
			}
			if (line >= 27 && creditsYpos > -29) {
				gotoxy(creditsXpos - 16, creditsYpos + 33);
				setColor(Light_Yellow, Black); printf("10스테이지"); setColor(Bright_White, Black); printf(" : 비긴어게인 - A Higher Place");
			}
			if (line >= 29 && creditsYpos > -31) {
				gotoxy(creditsXpos - 13, creditsYpos + 35);
				setColor(Light_Yellow, Black); printf("실패곡"); setColor(Bright_White, Black); printf(" : 오징어게임 - Pink Soldiers");
			}
			if (line >= 31 && creditsYpos > -33) {
				gotoxy(creditsXpos - 8, creditsYpos + 37);
				setColor(Light_Yellow, Black); printf("엔딩곡"); setColor(Bright_White, Black); printf(" : 밋치리네코 행진");
			}
			if (line >= 37 && line < 42) {
				gotoxy(creditsXpos - 5, creditsYpos + 43);
				printf("Thank you for play");
			}
			if (line == 42) {
				gotoxy(creditsXpos - 5, creditsYpos + 44);
				printf("Thank you for play"); setColor(Light_Red, Black); printf("!");
				gotoxy(23, 14);
				setColor(Gray, Black);
				printf("Space to Menu");
				endingcreditplaying = false; //Finish Endingcredit from this line	//스페이스, 엔터키 입력 가능
			}
			creditsYpos--;
			line++;
		}
	}
}

void newBestScore(int totalScore) {	//신기록을 세울 때 엔딩함수에서 불리는 함수
	static totalscoreCount = 0;	//엔딩 함수에서 계속 부르면 static 변수를 선언하였기 때문에 newscore의 색깔이 계속 바뀜
	if (totalscoreCount == 8)
		totalscoreCount = 0;
	switch (totalscoreCount) {	//색깔이 바뀌어야 되기 때문에 글자의 색깔이 swicth문으로 계속 바뀜
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

void saveScore(const int _totalScore) {	//엔딩시 스코어 저장
	FILE* file;
	file = fopen("TokTokScore.txt", "w");
	if (file == NULL) {
		bestScore = 0;
	}
	else {
		fprintf(file, "%d", _totalScore);
		fclose(file);
	}
}

void getScore() {	//bextScore 가져오기
	FILE* file;
	file = fopen("TokTokScore.txt", "r");
	if (file == NULL) {
		bestScore = 0;
	}
	else {
		fscanf(file, "%d", &bestScore);
		fclose(file);
	}
}

//Infomation
void drawInfo() {	//게임 정보에를 누를 시 제공되는 함수
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
		if (currentKey == ENTER || currentKey == ESCAPE) {
			noteSound(15);
			noteSound(12);
			Sleep(50);
			break;
		}
	}
}