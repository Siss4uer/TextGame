#pragma once
#include <windows.h>
#include <winnt.h>
#include <stdio.h>
//������ɫ 
#define BLACK 0	//��ɫ 
#define BLUE 1	//��ɫ 
#define GREEN 2	//��ɫ 
#define LAKEBLUE 3	//����ɫ 
#define RED 4	//��ɫ 
#define PURPLE 5	//��ɫ 
#define YELLOW 6	//��ɫ 
#define WHITE 7		//��ɫ 
#define GREY 8	//��ɫ 
#define LIGHTBLUE 9 //����ɫ 
#define LIGHTGREEN 10	//����ɫ 
#define LIGHTRED 11	//����ɫ 
#define LIGHTPURPLE 12	//����ɫ 
#define LIGHTYELLOW 13	//����ɫ 
#define BRIGHTWHITE 14	//����ɫ
void setcolor(int color)
{
	HANDLE hConsoleWnd; hConsoleWnd = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsoleWnd, color);
}