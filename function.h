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
extern struct BACKPACK backpack;
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
}//Mode = 1����low��high���������һ��ֵ��Mode = 2����Low��High�����ķ�Χ�����һ����


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
}//MODE = 1 ʱ��Ѫ��MODE = 0ʱ��Ѫ,����1ʱִ�гɹ�������0ʱ��Ϸ����

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
}//MODE = 1 ʱ�Ӽ���ֵ��MODE = 0ʱ������ֵ,�������޿۳�Ѫ�����������޻ظ�Ѫ����

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
}//MODE = 1 ʱ����ˮֵ��MODE = 0ʱ����ˮֵ,�������޿۳�Ѫ��

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
}//ÿ�촥��һ��


int init(void) {
	struct ITEM guider = { {1},{"guider"},{"����һ�������ֲᣬ���ڲ��Ա���ϵͳ"},{0,0,0} };
	for (int i = 0; i < 8; i++) {
		backpack.ITEMINPACK[i].ITEMID = 0;
		strcpy(backpack.ITEMINPACK[i].DESCRIPTION, "");
		strcpy(backpack.ITEMINPACK[i].ITEMNAME, "");
		strcpy(backpack.ITEMINPACK[i].NBT, "");
	}
	give_ITEM(guider);
	DASHBOARD.BUFFLIST.NUM = initvalue[0];
	DASHBOARD.SCORE = initvalue[1];
	DASHBOARD.TIME.DAY = initvalue[2];
	DASHBOARD.TIME.HOURS = initvalue[3];
	DASHBOARD.TIME.MINUTES = initvalue[4];
	DASHBOARD.SELF.HEALTH = initvalue[6];
	DASHBOARD.SELF.HUNGER = initvalue[7];
	DASHBOARD.SELF.THIRSTY = initvalue[8];
	rename:
	printf("Input your name - >");
	scanf("%[^\n]", DASHBOARD.SELF.NAME);
	printf("\n");
	
}
void help(void) {
	printf("------------------------����չʾ------------------------\n");
	printf("���κ���������£����������help��ȡ����\n");
	printf("����status���Ի�ȡ��ǰ������Ϣ\n");
	printf("����action���Խ����ж��������\n");
	printf("����backpack���Ի�ȡ��������Ϣ\n");
	printf("����use + id ����ʹ�ñ����ڵ���Ʒ\n");
	printf("����save���Խ��д浵����\n");
	printf("����goto���Բ�ѯ��ǰ�����õĵص�\n");
	printf("����charactor���Դ���NPC����\n");
	printf("����cls������մ���\n");
	printf("����exit�����˳�����\n");
}
void show_DASHBOARD() {
	int BUFFNUM;
	printf("------------------------��Ϣչʾ------------------------\n");
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
}//MODE = 1,װ��ΪLEVEL�ļ���MODE = 2��װ��Ϊ�����ļ���MODE = 3��װ��Ϊ�����ļ���
int UNLOADER(FILE* fp) {
	errno_t err;
	if ((err = fclose(fp)) != 0) {
		printf("FILE UNLOAD FAIL");
	}
	return err;
}
int GETPLOT() {

}
int give_ITEM(struct ITEM item) {
	for (int i = 0; i < 8; i++) {
		if (backpack.ITEMINPACK[i].ITEMID == 0) {
			backpack.ITEMINPACK[i].ITEMID = item.ITEMID;
			strcpy(backpack.ITEMINPACK[i].DESCRIPTION, item.DESCRIPTION);
			strcpy(backpack.ITEMINPACK[i].ITEMNAME, item.ITEMNAME);
			strcpy(backpack.ITEMINPACK[i].NBT, item.NBT);
			return 1;
		}
	}
	return 0;
}

int show_BACKPACK(int mode){
	if (mode) {
		printf("------------------------����չʾ------------------------\n");
		for (int i = 0; i < 8; i++) {
			if (backpack.ITEMINPACK[i].ITEMID == 0) {
				break;
			}
			printf("<No.%d - %s - %d -{%d,%d,%d}>|", i + 1, backpack.ITEMINPACK[i].ITEMNAME, backpack.ITEMINPACK[i].ITEMID, backpack.ITEMINPACK[i].NBT[0], backpack.ITEMINPACK[i].NBT[1], backpack.ITEMINPACK[i].NBT[2]);
			if (i % 2 == 0) {
				printf("\n");
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			if (backpack.ITEMINPACK[i].ITEMID == 0) {
				return i;
			}
		}
	}
}
int common_command_Trans(struct ACTION action) {
	char input[32];
	int i;
	while (1) {
	main_start:
		printf("------------------------Ŀ¼�׶�------------------------\n");
		printf(">");
		scanf("%s", input);
		if (strcmp(input, "help") == 0) {
			help();
		}
		else if (strcmp(input, "status") == 0) {
			show_DASHBOARD();
		}
		else if (strcmp(input, "action") == 0)
		{
			action_choice:
			printf("-----------------------�����ж��׶�-----------------------\n");
			for (i = 1; i <= action.actionNum; i++) {
				printf("%d - %s\n", i, action.action[i - 1]);
			}
			printf("%d - �˳��ж��׶�\n",action.actionNum + 1);
			printf(">");
			scanf("%s", input);
			for (i = 1; i <= action.actionNum; i++) {
				if ((atoi(input) == i)||((strcmp(input, action.action[i-1]))==0)) {
					return i;
				}
				if ((atoi(input) == action.actionNum +1) || ((strcmp(input,"exit")==0))) {
					goto main_start;
				}
			}
			printf("Error Command\n");
			goto action_choice;
		}
		else if (strcmp(input, "backpack") == 0)
		{
			backpack_start:
			show_BACKPACK(1);
			backpack_choice:
			printf("--------------------ѡ����Ʒ�����˽�--------------------\n");
			printf(">");
			scanf("%s", input);
			for (i = 1; i <= show_BACKPACK(0); i++) {
				if ((atoi(input) == i) || ((strcmp(input,backpack.ITEMINPACK[i-1].ITEMNAME)) == 0)) {
					printf("[No.%d]-[%s]\nNBT = {%d,%d,%d}\n���� [%s]\n", i, backpack.ITEMINPACK[i - 1].ITEMNAME, backpack.ITEMINPACK[i - 1].NBT[0], backpack.ITEMINPACK[i - 1].NBT[1], backpack.ITEMINPACK[i - 1].NBT[2], backpack.ITEMINPACK[i - 1].DESCRIPTION);
					goto backpack_choice;
				}
				if ((atoi(input) == action.actionNum + 1) || ((strcmp(input, "exit") == 0))) {
					goto main_start;
				}
				if (strcmp(input, "show") == 0) {
					goto backpack_start;
				}

			}
			printf("Error Command\n");
			goto backpack_choice;
		}
		else if (strcmp(input, "use") == 0)
		{

		}
		else if (strcmp(input, "save") == 0)
		{
		}
		else if (strcmp(input, "goto") == 0)
		{
		}
		else if (strcmp(input, "charactor") == 0)
		{
		}
		else if (strcmp(input, "cls") == 0)
		{
			printf("\033[2J\033[1;1H");
		}
		else if (strcmp(input, "exit") == 0)
		{
			exit(0);
		}
		else {
			printf("Unknow Command\n");
		}
	}
	

}


#endif
