#pragma warning(disable:4996)
#include "struct.h"
#include "function.h"
#include <stdio.h>
#include <direct.h>
#include "Windows.h"
#include <stdlib.h>
#include "cJSON.h"
#include "color.h"
#pragma once
#define MAXACTION 4
struct DASHBOARD DASHBOARD;//ȫ�ּǷְ�
int initvalue[] = { 0,0,0,12,0,0,20,20,10 };//BUFFNUM,DAY,HOURS,MINUTES,*SECOND,HEALTH,HUNGERȫ�ֳ�ʼ������
int dailyeventsvalue[] = { 5 , 5 };//HUNGER,THIRSTY
char actionlist[MAXACTION][32];
int main(void) {
	int flag = 1;
	char input[32];
	init();
	printf("\033[2J\033[1;1H");
	SHOW();
	printf("------------------------Ŀ¼�׶�-----------------------\n");
	help();
	while (1) {
		printf(">");
		scanf("%s", input);
		if (common_command_Trans(input)) {
			printf("��������δ֪����\n");
		}
	}
}

/*char filename[10];
printf("���������õ��ļ�����");
scanf_s("%s", filename, 10);
LOADER(filename, 1);*/

