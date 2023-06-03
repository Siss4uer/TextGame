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
struct DASHBOARD DASHBOARD;//全局记分板
int initvalue[] = { 0,0,0,12,0,0,20,20,10 };//BUFFNUM,DAY,HOURS,MINUTES,*SECOND,HEALTH,HUNGER全局初始化常量
int dailyeventsvalue[] = { 5 , 5 };//HUNGER,THIRSTY
char actionlist[MAXACTION][32];
int main(void) {
	int flag = 1;
	char input[32];
	init();
	printf("\033[2J\033[1;1H");
	SHOW();
	printf("------------------------目录阶段-----------------------\n");
	help();
	while (1) {
		printf(">");
		scanf("%s", input);
		if (common_command_Trans(input)) {
			printf("你输入了未知命令\n");
		}
	}
}

/*char filename[10];
printf("请输入所用的文件名：");
scanf_s("%s", filename, 10);
LOADER(filename, 1);*/

