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
#include "cJSON.h"
#include "color.h"
#define MAXACTION 4
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
void help(void) {
	printf("在任何输入情况下，你均可输入!help获取帮助\n");
	printf("输入!status可以获取当前人物信息\n");
	printf("输入!action可以进行行动步骤决策\n");
	printf("输入!backpack可以获取背包内信息\n");
	printf("输入!use + id 可以使用背包内的物品\n");
	printf("输入!skip可以在允许的情况下进入下一天\n");
	printf("输入!goto可以查询或前往可用的地点\n");
	printf("输入!charactor可以触发NPC交互\n");
	printf("输入!exit可以退出程序\n");
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
int GETPLOT() {

}
int common_command_Trans(int actionNum, char action[MAXACTION][32]) {
	char input[32];
	int i;
	while (1) {
		start:
		printf(">");
		scanf("%s", input);
		if (strcmp(input, "!help") == 0) {
			help();
		}
		else if (strcmp(input, "!status") == 0) {
			SHOW();
		}
		else if (strcmp(input, "!action") == 0)
		{
			choice:
			printf("------------------------进入行动阶段------------------------\n");
			for (i = 1; i <= actionNum; i++) {
				printf("%d - %s\n", i, action[i - 1]);
			}
			printf("%d - 退出行动阶段\n",actionNum + 1);
			printf(">");
			scanf("%s", input);
			printf("%s",input);
			for (i = 1; i <= actionNum; i++) {
				if (input == i) {
					return i;
				}
				else if (input == (actionNum + 1)) {
					goto start;
				}
				else {
					printf("Error Command\n");
					goto choice;
				}
	
			}
			
		}
		else if (strcmp(input, "!backpack") == 0)
		{

		}
		else if (strcmp(input, "!use") == 0)
		{

		}
		else if (strcmp(input, "!skip") == 0)
		{
		}
		else if (strcmp(input, "!goto") == 0)
		{
		}
		else if (strcmp(input, "!charactor") == 0)
		{
		}
		else if (strcmp(input, "!exit") == 0)
		{
			exit(0);
		}
		else {
			printf("Unknow Command\n");
		}
	}
	

}


#endif
