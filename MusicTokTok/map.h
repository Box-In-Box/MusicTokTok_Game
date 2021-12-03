#include "main.h"

char ui[4][58];		//UI창 크기	- 글자를 출력해야 되기대문에 1칸씩
char field[16][29];	//플레이창 크기	- 특수문자를 출력해야 되기대문에 2칸씩

int maxLevel;		//스테이지 크기

//스테이지 배열들
int stage_1[19][3];
int stage_2[22][3];
int stage_3[29][3];
int stage_4[33][3];
int stage_5[37][3];
int stage_6[44][3];
int stage_7[56][3];
int stage_8[70][3];
int stage_9[80][3];
int stage_10[99][3];

//메뉴 이스터에그 사운드
int menuSound_1[32];

//실패엔딩 사운드
int failedSound_0[16];
int failedSound_1[16];
int failedSound_2[16];
int failedSound_3[16];
int failedSound_4[16];

//엔딩 사운드
int endingSound[288];

//사운들 배열들
int sound_1[19];
int sound_2[22];
int sound_3[29];
int sound_4[33];
int sound_5[37];
int sound_6[44];
int sound_7[56];
int sound_8[70];
int sound_9[80];
int sound_10[99];