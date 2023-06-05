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
struct DASHBOARD DASHBOARD;//全局记分板
struct BACKPACK backpack;//全局背包
struct ITEM_USED_LIST USED_LIST;//全局使用过的物品
struct PLOT_STORAGE plot_storage; //全局剧情读取器
int initvalue[] = { 0,0,0,12,0,0,5,20,6,10 };//BUFFNUM,DAY,HOURS,MINUTES,*SECOND,HEALTH,HUNGER,DESIRED,SAN全局初始化常量
int dailyeventsvalue[] = { 5 , 5 };//HUNGER,DESIRED
int main_S(void) {
	FILE* fp;
	int flag = 1;
	int report= 0;
	struct ACTION action = { {3},{{"开始游戏"},{"关于"},{"开发人员测试"}}};
	init();
	printf("\033[2J\033[1;1H");
	show_DASHBOARD();
	help();
	give_ITEM(1);
	if (common_command_Trans(action) == 1) {
		

	}


}
int main() {
	json_plot(&plot_storage,"pack_01.json");

}
/*char filename[10];
printf("请输入所用的文件名：");
scanf_s("%s", filename, 10);
LOADER(filename, 1);*/

