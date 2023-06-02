#pragma warning(disable:4996)
#include "struct.h"
#include "function.h"
#include <stdio.h>
#include <direct.h>
#include "Windows.h"
#include <stdlib.h>
#pragma once
struct DASHBOARD DASHBOARD;//全局记分板
int initvalue[] = { 0,0,0,12,0,0,20,20,10 };//BUFFNUM,DAY,HOURS,MINUTES,*SECOND,HEALTH,HUNGER全局初始化常量
int dailyeventsvalue[] = { 5 , 5 };//HUNGER,THIRSTY

//函数声明
int random(int size, int low, int high);
void SHOW();
int HEALTH_CHANGER(int mode, int value,int DAMAGEFROM);//DAMAGERFROM 1 = HUNGER,2 = THIRSTY
int HUNGER_CHANGER(int mode, int value);
int THIRSTY_CHANGER(int mode, int value);
FILE* LOADER(char PATH[], int mode);
int READLEVEL(char FILENAME[]);
void init();


int main(void) {
	READLEVEL("pack_01.level");
}

/*char filename[10];
printf("请输入所用的文件名：");
scanf_s("%s", filename, 10);
LOADER(filename, 1);*/

