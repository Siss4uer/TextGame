#ifndef __FUNCTION_
#define __FUNCTION_
#include <time.h>
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cJSON.h"
#include "Windows.h"
#include "struct.h"
#include "json_function.h"

#define MAXACTION 4
#define MAX_LINES 100
#define MAX_LINE_LENGTH 100

extern struct DASHBOARD DASHBOARD;
extern struct BACKPACK backpack;
extern struct ITEM_USED_LIST USED_LIST;
extern int initvalue[];
extern int dailyeventsvalue[];


//���ߺ���
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
ITEM create_ITEM(int ItemID, char* ItemName, int hP, int hUNGER, int dESIRED, int sAN) {
	ITEM item;
	item.ITEMID = ItemID;
	strcpy(item.ITEMNAME, ItemName);
	strcpy(item.DESCRIPTION, "");
	item.OPERATE[0] = hP;
	item.OPERATE[1] = hUNGER;
	item.OPERATE[2] = dESIRED;
	item.OPERATE[3] = sAN;
	item.NBT[0] = 0;
	item.NBT[1] = 0;
	item.NBT[2] = 0;
	return item;
}
//��ֵ�޸ĺ���
int HEALTH_CHANGER(int value, int DAMAGEFROM) {
	void GAMEOVER(int DAMAGEFROM);
	if ((value>0)&&(value < 100)) {
		DASHBOARD.SELF.HEALTH += value;
		if (DASHBOARD.SELF.HEALTH > initvalue[6]) {
			DASHBOARD.SELF.HEALTH = initvalue[6];
		}
		printf("HP ADD - > %d | %d/%d", value, DASHBOARD.SELF.HEALTH, initvalue[6]);
		printf("\n");
	}
	else if (value < 0)
	{
		DASHBOARD.SELF.HEALTH += value;
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
	}
	else if (value >100)
	{
		value -= 100;
		initvalue[6] += value;
		DASHBOARD.SELF.HEALTH += value;
		printf("HP ADD - > %d | %d/%d(+%d)", value, DASHBOARD.SELF.HEALTH, initvalue[6],value);
		printf("\n");
	}
	else {
		return 0;
	}
	
}//VALUEС��0��Ѫ������0��Ѫ������100��Ϊ��������
int HUNGER_CHANGER(int value) {
	int HUNGER = DASHBOARD.SELF.HUNGER;
	int HEALTH_CHANGER(int mode, int value);
	if (value<0) {
		if (HUNGER > 0) {
			if ((HUNGER - value) >= 0) {
				printf("HUNGER MINUS - > %d | %d/%d", -value, HUNGER - value, initvalue[7]);
				printf("\n");
				DASHBOARD.SELF.HUNGER = HUNGER + value;
			}
			else {
				printf("HUNGER MINUS - > %d | %d/%d", value, 0, initvalue[7]);
				printf("\n");
				DASHBOARD.SELF.HUNGER = 0;
				value += HUNGER;
				
				HEALTH_CHANGER(-value,1);
			}
		}
		else
		{
			printf("HUNGER MINUS - > %d | %d/%d", value, 0, initvalue[7]);
			printf("\n");
			HEALTH_CHANGER(-value, 1);
		}
	}
	else if(value >0){
		HUNGER += value;
		if (HUNGER > initvalue[7]) {
			printf("HUNGER ADD - > %d | %d/%d", value, HUNGER, initvalue[7]);
			printf("\n");
			printf("HP ADD BECAUSE OF HUNGER\n");
			HEALTH_CHANGER(HUNGER - initvalue[7], 1);
			HUNGER = initvalue[7];
			DASHBOARD.SELF.HUNGER = HUNGER;
		}
		else {
			DASHBOARD.SELF.HUNGER = HUNGER;
			printf("HUNGER ADD - > %d | %d/%d", value, HUNGER, initvalue[7]);
			printf("\n");
		}


	}
	return 1;
}//MODE = 1 ʱ�Ӽ���ֵ��MODE = 0ʱ������ֵ,�������޿۳�Ѫ�����������޻ظ�Ѫ����
int DESIRED_CHANGER(int value) {
	int DESIRED = DASHBOARD.SELF.DESIRED;
	if (value<0) {
		DESIRED += value;
		if (DESIRED >= 0) {

			printf("DESIRED MINUS - > %d | %d/%d", value, DESIRED, initvalue[8]);
			printf("\n");
			DASHBOARD.SELF.DESIRED = DESIRED;
			return 1;
		}
		else {
			return 0;
		}
		
	}
	else if ((value>0)&&(value<100)){
		DESIRED += value;
		if (DESIRED > initvalue[8]) {
			DESIRED = initvalue[8];
		}
		DASHBOARD.SELF.DESIRED = DESIRED;
		printf("DESIRED ADD - > %d | %d/%d", value, DESIRED, initvalue[8]);
		printf("\n");
		return 1;
	}
	else if (value > 100){
		value -= 100;
		DESIRED += value;
		initvalue[8] += value;
		DASHBOARD.SELF.DESIRED = DESIRED;
		printf("DESIRED ADD - > %d | %d/%d(+%d)", value, DESIRED, initvalue[8], value);
		printf("\n");
		return 1;
	}
	return 1;
}//VALUEС��0�ۣ�����0�ӣ�����100��Ϊ��������
int SAN_CHANGER(int value) {
	int SAN = DASHBOARD.SELF.SAN;

	if (value<0) {
		SAN += value;
		if (SAN <= 0) {
			DASHBOARD.SELF.SAN = 0;
			printf("DESIRED MINUS - > %d | %d/%d", value, DASHBOARD.SELF.SAN, initvalue[9]);
			printf("\n");
			return SAN;
		}
		else {
			DASHBOARD.SELF.SAN = SAN;
			printf("DESIRED MINUS - > %d | %d/%d", value, DASHBOARD.SELF.SAN, initvalue[9]);
			printf("\n");
			return SAN;
		}
	}
	else if (value > 0) {
		SAN += value;
		if (SAN >= initvalue[9]) {
			DASHBOARD.SELF.SAN = initvalue[9];
		}
		else {
			DASHBOARD.SELF.SAN = SAN;
		}
		printf("DESIRED ADD - > %d | %d/%d", value, DASHBOARD.SELF.SAN, initvalue[9]);
		printf("\n");
		return SAN;
	}
}
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
	return 1;
}


//�ճ�����
int DAILYEVENTS() {
	HUNGER_CHANGER(0, dailyeventsvalue[0]);
	return 1;
}//ÿ�촥��һ��

//��ʼ������
void init(void) {
	DASHBOARD.BUFFLIST.NUM = initvalue[0];
	DASHBOARD.SCORE = initvalue[1];
	DASHBOARD.TIME.DAY = initvalue[2];
	DASHBOARD.TIME.HOURS = initvalue[3];
	DASHBOARD.TIME.MINUTES = initvalue[4];
	DASHBOARD.SELF.HEALTH = initvalue[6];
	DASHBOARD.SELF.HUNGER = initvalue[7];
	DASHBOARD.SELF.DESIRED = initvalue[8];
	DASHBOARD.SELF.SAN = initvalue[9];
	USED_LIST.NUM = 0;
	rename:
	printf("Input your name - >");
	scanf("%[^\n]", DASHBOARD.SELF.NAME);
	printf("\n");
	
}

//UI����
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
	printf("PROPERTY|---|NAME->%s|HEALTH->%d|HUNGER->%d|DESIRED->%d|SAN->%d\n", DASHBOARD.SELF.NAME, DASHBOARD.SELF.HEALTH, DASHBOARD.SELF.HUNGER, DASHBOARD.SELF.DESIRED,DASHBOARD.SELF.SAN);
	printf("ADDITIVE ATTRIBUTE|---|");
	if (DASHBOARD.BUFFLIST.NUM == 0) {
		printf("NONE");
	}
	for (BUFFNUM = 1; BUFFNUM <= DASHBOARD.BUFFLIST.NUM; BUFFNUM++) {
		printf("%s|", DASHBOARD.BUFFLIST.BUFF->BUFFNAME);
	}
	printf("\n");
	
}
int show_BACKPACK(int mode) {
	if (mode) {
		printf("------------------------����չʾ------------------------\n");
		for (int i = 0; i < 8; i++) {
			if (backpack.ITEMINPACK[i].ITEMID == 0) {
				printf("\n");
				printf("<%d - exit backpack>\n", i + 1);
				break;
			}
			printf("<No.%d - %s - %d -{%d,%d,%d}>|", i + 1, backpack.ITEMINPACK[i].ITEMNAME, backpack.ITEMINPACK[i].ITEMID, backpack.ITEMINPACK[i].NBT[0], backpack.ITEMINPACK[i].NBT[1], backpack.ITEMINPACK[i].NBT[2]);
			printf("\n");
		}
		return 0;

	}
	else {
		for (int i = 0; i < 8; i++) {
			if (backpack.ITEMINPACK[i].ITEMID == 0) {
				return i;
			}
		}
	}
}
void GAMEOVER(int DAMAGEFROM) {
	printf("-----GAMEOVER-----");
	printf("\n");
	switch (DAMAGEFROM)
	{
	case 1:printf("You dead beacause of Hunger"); printf("\n"); exit(0); break;
	case 2:printf("You dead beacause of USING ITEM"); printf("\n"); exit(0); break;
	default:printf("You dead beacause of Nothing"); printf("\n"); exit(0); break;
	}
}

//���ݷ��뺯��
int get_ITEM_CN(ITEM* item) {
	char lines[MAX_LINES][MAX_LINE_LENGTH];  // �洢ÿ���ı�������
	int numLines = 0;  // �����е�Ԫ������
	char buffer[MAX_LINE_LENGTH];
	char strings[3][MAX_LINE_LENGTH];
	char* temp;
	FILE* fp;
	fopen_s(&fp,"Trans_CN.txt", "r+");
	//�ж��ļ��Ƿ�򿪳ɹ�
	if (fp == NULL) {
		printf("Failed to open file.\n");
		return 1;
	}
	// ���ж�ȡ�ı��ļ�����
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		// ȥ�����з�
		buffer[strcspn(buffer, "\n")] = '\0';

		// ����ǰ�и��Ƶ�������
		strcpy(lines[numLines], buffer);
		numLines++;

		// ��������Ƿ�����
		if (numLines >= MAX_LINES) {
			printf("Warning: Maximum number of lines reached.\n");
			break;
		}
	}
	// �ָ������е�����
	for (int i = 0; i < numLines; i++) {
		temp = strtok(lines[i], "#");
		if (atoi(temp) == item->ITEMID) {
			temp = strtok(NULL, "#");
			strcpy(item->ITEMNAME, temp);
			temp = strtok(NULL, "#");
			strcpy(item->DESCRIPTION, temp);	
			return 1;
		}
	}
}
int get_PLOT() {
	return 1;
}

//��Ϸ��Ӧ�ú���
int give_ITEM(int ItemID) {
	ITEM* item = item_GET(ItemID);
	get_ITEM_CN(item);
	for (int i = 0; i < 8; i++) {
		if (backpack.ITEMINPACK[i].ITEMID == 0) {
			backpack.ITEMINPACK[i].ITEMID = item->ITEMID;
			strcpy(backpack.ITEMINPACK[i].ITEMNAME, item->ITEMNAME);
			strcpy(backpack.ITEMINPACK[i].DESCRIPTION, item->DESCRIPTION);
			strcpy(backpack.ITEMINPACK[i].NBT, item->NBT);
			break;
		}
	}
	return 0;
}
int remove_ITEM(int ItemID) {
	for (int i = 0; i < 8; i++) {
		if (backpack.ITEMINPACK[i].ITEMID == ItemID) {
			backpack.ITEMINPACK[i].ITEMID = 0;
			strcpy(backpack.ITEMINPACK[i].ITEMNAME, "");
			strcpy(backpack.ITEMINPACK[i].DESCRIPTION,"");
			backpack.ITEMINPACK[i].NBT[0] = 0;
			backpack.ITEMINPACK[i].NBT[1] = 0;
			backpack.ITEMINPACK[i].NBT[2] = 0;
			return 1;
		}
	}
	return 0;
}//�����Ƴ������е�ָ��ID��Ʒ��ע�����Ƴ���Ʒid�����Ǳ���˳�򣬳ɹ�����1��ʧ�ܷ���0
int use_ITEM(int NumInBackpack) {
	ITEM* item = item_GET(backpack.ITEMINPACK[NumInBackpack-1].ITEMID);;
	HEALTH_CHANGER(item->OPERATE[0], 2);
	HUNGER_CHANGER(item->OPERATE[1]);
	DESIRED_CHANGER(item->OPERATE[2]);
	SAN_CHANGER(item->OPERATE[3]);
	USED_LIST.ITEM_USED[USED_LIST.NUM].ITEMID = item->ITEMID;
	USED_LIST.ITEM_USED[USED_LIST.NUM].NBT[0] = item->NBT[0];
	USED_LIST.ITEM_USED[USED_LIST.NUM].NBT[1] = item->NBT[1];
	USED_LIST.ITEM_USED[USED_LIST.NUM].NBT[2] = item->NBT[2];
	remove_ITEM(item->ITEMID);
}

//�ж��ڵ㺯��
int common_command_Trans(struct ACTION action){
	char input[32];
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
			int i;
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
			if (show_BACKPACK(0) == 0) {
				printf("Nothing In backpack\n");
				goto main_start;
			}
			backpack_start:
			show_BACKPACK(1);
			backpack_choice:
			printf("--------------------ѡ����Ʒ�����˽�--------------------\n");
			printf(">");
			scanf("%s", input);
			for (int i = 0; i <= show_BACKPACK(0); i++) {
				if ((atoi(input) == i) || ((strcmp(input, backpack.ITEMINPACK[i - 1].ITEMNAME)) == 0)) {
					printf("[No.%d]-[%s]\nNBT = {%d,%d,%d}\n���� [%s]\n", i, backpack.ITEMINPACK[i - 1].ITEMNAME, backpack.ITEMINPACK[i - 1].NBT[0], backpack.ITEMINPACK[i - 1].NBT[1], backpack.ITEMINPACK[i - 1].NBT[2], backpack.ITEMINPACK[i - 1].DESCRIPTION);
					goto backpack_choice;
				}
				if ((atoi(input) == show_BACKPACK(0) + 1) || ((strcmp(input, "exit") == 0))) {
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
			int i;
			use_start:
			printf("Number In backpack >");
			scanf("%d",&i);
			if ((i < 0) || (i > 8)) {
				printf("Unknow Number\n");
				goto use_start;
			}
			use_ITEM(i);
			goto main_start;
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
