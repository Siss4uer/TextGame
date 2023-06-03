#pragma warning(disable:4996)
#include "struct.h"
#include "function.h"
#include <stdio.h>
#include <direct.h>
#include "Windows.h"
#include <stdlib.h>
#include "cJSON.h"
#include "color.h"
#define MAXACTION 4
#pragma once
struct DASHBOARD DASHBOARD;//全局记分板
struct BACKPACK backpack;//全局背包
int initvalue[] = { 0,0,0,12,0,0,20,20,10 };//BUFFNUM,DAY,HOURS,MINUTES,*SECOND,HEALTH,HUNGER全局初始化常量
int dailyeventsvalue[] = { 5 , 5 };//HUNGER,THIRSTY
int main(void) {
	int flag = 1;
	char input[32];
	int report= 0;
	struct ACTION action = { {3},{{"开始游戏"},{"关于"},{"开发人员测试"}}};
	init();
	printf("\033[2J\033[1;1H");
	show_DASHBOARD();
	help();
	common_command_Trans(action);
}

/*char filename[10];
printf("请输入所用的文件名：");
scanf_s("%s", filename, 10);
LOADER(filename, 1);*/

