#pragma warning(disable:4996)
#include "struct.h"
#include "function.h"
#include "cJSON.h"
#include "Windows.h"
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include "json_function.h"
#include <string.h>

#define MAXACTION 4
#pragma once
struct DASHBOARD DASHBOARD;//ȫ�ּǷְ�
struct BACKPACK backpack;//ȫ�ֱ���
struct ITEM_USED_LIST USED_LIST;//ȫ��ʹ�ù�����Ʒ
int initvalue[] = { 0,0,0,12,0,0,5,20,6,10 };//BUFFNUM,DAY,HOURS,MINUTES,*SECOND,HEALTH,HUNGER,DESIRED,SANȫ�ֳ�ʼ������
int dailyeventsvalue[] = { 5 , 5 };//HUNGER,DESIRED
int main(void) {
	FILE* fp;
	int flag = 1;
	int report= 0;
	struct ACTION action = { {3},{{"��ʼ��Ϸ"},{"����"},{"������Ա����"}}};
	init();
	printf("\033[2J\033[1;1H");
	show_DASHBOARD();
	help();
	give_ITEM(1);
	give_ITEM(4);
	give_ITEM(2);
	give_ITEM(3);
	/*give_ITEM(3);
	give_ITEM(4);*/
	common_command_Trans(action);
}

/*char filename[10];
printf("���������õ��ļ�����");
scanf_s("%s", filename, 10);
LOADER(filename, 1);*/

