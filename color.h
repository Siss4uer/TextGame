#pragma once
#include <windows.h>
#include <winnt.h>
#include <stdio.h>
//定义颜色 
#define BLACK 0	//黑色 
#define BLUE 1	//蓝色 
#define GREEN 2	//绿色 
#define LAKEBLUE 3	//湖蓝色 
#define RED 4	//红色 
#define PURPLE 5	//紫色 
#define YELLOW 6	//黄色 
#define WHITE 7		//白色 
#define GREY 8	//灰色 
#define LIGHTBLUE 9 //淡蓝色 
#define LIGHTGREEN 10	//淡绿色 
#define LIGHTRED 11	//淡红色 
#define LIGHTPURPLE 12	//淡紫色 
#define LIGHTYELLOW 13	//淡黄色 
#define BRIGHTWHITE 14	//亮白色
void setcolor(int color)
{
	HANDLE hConsoleWnd; hConsoleWnd = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsoleWnd, color);
}