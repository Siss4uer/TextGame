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


int main(void) {
	int flag = 1;
	struct ORDER input;
	init();
	input = GETINPUT(1);

}

/*char filename[10];
printf("请输入所用的文件名：");
scanf_s("%s", filename, 10);
LOADER(filename, 1);*/

