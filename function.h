#ifndef __FUNCTION_
#define __FUNCTION_
#include <time.h>
#include <stdio.h>
#include <direct.h>
#include "Windows.h"
#include <stdlib.h>
#include "struct.h"
#include <string.h>
#include <math.h>

extern struct DASHBOARD DASHBOARD;
extern int initvalue[];
extern int dailyeventsvalue[];

int random(int mode, int low, int high) {
	int randomer;
	if (mode) {
		srand((unsigned int)time(NULL));
		randomer = rand() % 10 + 1;
		if (randomer > 6) {
			return low;
		}
		else {
			return high;
		}
	}
	else {
		srand((unsigned int)time(NULL));
		randomer = rand() % (high - low + 1) + low;
		return randomer;
	}
}//Mode = 1，在low和high中随机返回一个值，Mode = 2，在Low和High给定的范围内随机一个数

struct ORDER GETINPUT(int mode) {
	struct ORDER ORDER = {0,0,""};

	if (mode) {//Mode = 1 定义为无文本输入
		ORDER.MODE = 1;
		scanf("%d", &ORDER.ORDERNUM);
		return ORDER;
	}
	else {//Mode = 0 定义为有文本输入
		ORDER.MODE = 0;
		scanf("%s", ORDER.TEXT);
		return ORDER;
	}
}//获取输入

void GAMEOVER(int DAMAGEFROM) {
	printf("-----GAMEOVER-----");
	printf("\n");
	switch (DAMAGEFROM)
	{
	case 1:printf("You dead beacause of Hunger"); printf("\n"); exit(0); break;
	case 2:printf("You dead beacause of Thirsty"); printf("\n"); exit(0); break;
	default:printf("You dead beacause of Nothing"); printf("\n"); exit(0); break;
	}
}


int HEALTH_CHANGER(int mode, int value, int DAMAGEFROM) {
	void GAMEOVER(int DAMAGEFROM);
	if (mode) {
		DASHBOARD.SELF.HEALTH += value;
		if (DASHBOARD.SELF.HEALTH > initvalue[6]) {
			DASHBOARD.SELF.HEALTH = initvalue[6];
		}
		printf("HP ADD - > %d | %d/%d", value, DASHBOARD.SELF.HEALTH, initvalue[6]);
		printf("\n");
	}
	else
	{
		DASHBOARD.SELF.HEALTH -= value;
	}
	if (DASHBOARD.SELF.HEALTH <= 0) {
		DASHBOARD.SELF.HEALTH = 0;
		printf("HP MINUS - > %d | %d/%d", value, DASHBOARD.SELF.HEALTH, initvalue[6]);
		printf("\n");
		GAMEOVER(DAMAGEFROM);
		return 0;
	}
	else {
		printf("HP MINUS - > %d | %d/%d", value, DASHBOARD.SELF.HEALTH, initvalue[6]);
		printf("\n");
		return 1;
	}
}//MODE = 1 时加血，MODE = 0时扣血,返回1时执行成功，返回0时游戏结束

int HUNGER_CHANGER(int mode, int value) {
	int HUNGER = DASHBOARD.SELF.HUNGER;
	int HEALTH_CHANGER(int mode, int value, int DAMAGEFROM);
	if (!mode) {
		if (HUNGER >= 0) {
			if ((HUNGER - value) >= 0) {
				printf("HUNGER MINUS - > %d | %d/%d", value, HUNGER - value, initvalue[7]);
				printf("\n");
				DASHBOARD.SELF.HUNGER = HUNGER - value;
			}
			else {
				printf("HUNGER MINUS - > %d | %d/%d", value, 0, initvalue[7]);
				printf("\n");
				value -= HUNGER;
				HEALTH_CHANGER(0, value, 1);
			}
		}
		else
		{
			printf("HUNGER MINUS - > %d | %d/%d", value, 0, initvalue[7]);
			printf("\n");
			HEALTH_CHANGER(0, value, 1);
		}
	}
	else {
		HUNGER += value;
		if (HUNGER > initvalue[7]) {
			HEALTH_CHANGER(1, HUNGER - initvalue[7], 1);
			HUNGER = initvalue[7];
		}
		DASHBOARD.SELF.HUNGER = HUNGER;
		printf("HUNGER ADD - > %d | %d/%d", value, HUNGER, initvalue[7]);
		printf("\n");
	}
}//MODE = 1 时加饥饿值，MODE = 0时减饥饿值,超出下限扣除血量，超出上限回复血量。

int THIRSTY_CHANGER(int mode, int value) {
	int THIRSTY = DASHBOARD.SELF.THIRSTY;
	int HEALTH_CHANGER(int mode, int value, int DAMAGEFROM);
	if (!mode) {
		if (THIRSTY >= 0) {
			if ((THIRSTY - value) >= 0) {
				printf("THIRSTY MINUS - > %d | %d/%d", value, THIRSTY - value, initvalue[8]);
				printf("\n");
				DASHBOARD.SELF.THIRSTY = THIRSTY - value;
			}
			else {
				printf("THIRSTY MINUS - > %d | %d/%d", value, 0, initvalue[8]);
				printf("\n");
				value -= THIRSTY;
				HEALTH_CHANGER(0, value, 2);
			}
		}
		else
		{
			printf("THIRSTY MINUS - > %d | %d/%d", value, 0, initvalue[8]);
			printf("\n");
			HEALTH_CHANGER(0, value, 2);
		}
	}
	else {
		THIRSTY += value;
		if (THIRSTY > initvalue[8]) {
			THIRSTY = initvalue[8];
		}
		DASHBOARD.SELF.THIRSTY = THIRSTY;
		printf("THIRSTY ADD - > %d | %d/%d", value, THIRSTY, initvalue[8]);
		printf("\n");
	}
}//MODE = 1 时加饮水值，MODE = 0时减饮水值,超出下限扣除血量

int TIME_CHANGER(int time) {
	int HOURS = floor(time / 60);
	int MINUTES = time % 60;
	DASHBOARD.TIME.MINUTES += MINUTES;
	if (DASHBOARD.TIME.MINUTES >= 60)
	{
		DASHBOARD.TIME.HOURS += 1;
		DASHBOARD.TIME.MINUTES -= 60;
	}
	DASHBOARD.TIME.HOURS += HOURS;
	if (DASHBOARD.TIME.HOURS >= 24)
	{
		DASHBOARD.TIME.DAY += 1;
		DASHBOARD.TIME.HOURS -= 24;
	}
}

int DAILYEVENTS() {
	HUNGER_CHANGER(0, dailyeventsvalue[0]);
	THIRSTY_CHANGER(0, dailyeventsvalue[1]);
}//每天触发一次

void init(void) {
	DASHBOARD.BUFFLIST.NUM = initvalue[0];
	DASHBOARD.SCORE = initvalue[1];
	DASHBOARD.TIME.DAY = initvalue[2];
	DASHBOARD.TIME.HOURS = initvalue[3];
	DASHBOARD.TIME.MINUTES = initvalue[4];
	DASHBOARD.SELF.HEALTH = initvalue[6];
	DASHBOARD.SELF.HUNGER = initvalue[7];
	DASHBOARD.SELF.THIRSTY = initvalue[8];
	printf("Input your name - >");
	scanf("%[^\n]", DASHBOARD.SELF.NAME);
	printf("\n");
}

void SHOW() {
	int BUFFNUM;
	printf("TIME|---|DAY-%d-HOURS-%d-MINUTES-%d\n", DASHBOARD.TIME.DAY, DASHBOARD.TIME.HOURS, DASHBOARD.TIME.MINUTES);
	printf("PROPERTY|---|NAME->%s|HEALTH->%d|HUNGER->%d\n", DASHBOARD.SELF.NAME, DASHBOARD.SELF.HEALTH, DASHBOARD.SELF.HUNGER);
	printf("ADDITIVE ATTRIBUTE|---|");
	if (DASHBOARD.BUFFLIST.NUM == 0) {
		printf("NONE");
	}
	for (BUFFNUM = 1; BUFFNUM <= DASHBOARD.BUFFLIST.NUM; BUFFNUM++) {
		printf("%s|", DASHBOARD.BUFFLIST.BUFF->BUFFNAME);
	}
	printf("\n");
}
FILE* LOADER(char PATH[], int mode) {
	FILE* fp;
	errno_t err;
	switch (mode)
	{
	case 1:
		if ((err = fopen_s(&fp, PATH, "r+")) != 0)
		{
			printf("FILE LOAD FAIL - |%s\n", PATH);
			return err;
		}
		return fp;
		break;
	case 2:
		if ((err = fopen_s(&fp, PATH, "r")) != 0)
		{
			printf("FILE LOAD FAIL - |%s\n", PATH);
			return err;
		}
		return fp;
		break;
	case 3:
		if ((err = fopen_s(&fp, PATH, "r")) != 0)
		{
			printf("FILE LOAD FAIL - |%s\n", PATH);
			return err;
		}
		return fp;
		break;
	}
}//MODE = 1,装载为LEVEL文件，MODE = 2，装载为人物文件，MODE = 3，装载为剧情文件，
int UNLOADER(FILE* fp) {
	errno_t err;
	if ((err = fclose(fp)) != 0) {
		printf("FILE UNLOAD FAIL");
	}
	return err;
}
int GETPLOT(FILE* fp) {

}
int userinterface() {
	
}
#endif
