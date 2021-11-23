#include "main.h"

#ifndef KEY_CODE
#define KEY_CODE

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ENTER 4
#define ENTER_GOLD 5
#define NOTHING 6
#define ESCAPE 10
#endif

void keyControl();
void drawTitle();
int drawMenu();
void stageControl();
void drawMap();
void drawStage();
void drawInfo();
void update();
void removePlayer();
void removeHealth();
void removeAllHealth();
void setLeftHealth();
void nextStage();
void move();
void timer();
void drawUi();
void drawHealth();
void ending();
void reset();
void againTimerSet();
void failed();
void newBestScore(int);
void saveScore(const int);
void getScore();