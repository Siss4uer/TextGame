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
struct PLOT_STORAGE plot_storage; //ȫ�־����ȡ��
int Node_pos = 0;//ȫ�־���ڵ������
char* init_pack = { "pack_01.json" };
int initvalue[] = { 0,0,0,12,0,0,5,20,6,10 };//BUFFNUM,DAY,HOURS,MINUTES,*SECOND,HEALTH,HUNGER,DESIRED,SANȫ�ֳ�ʼ������
int dailyeventsvalue[] = { 5 , 5 };//HUNGER,DESIRED
int main_S(void) {
	FILE* fp;
	int flag = 1;
	int report= 0;
	init(init_pack);
	give_ITEM(1);
}
int convertToInt(const char* str) {
	const char* numStr = strstr(str, "_") + 1;
	int num = atoi(numStr);
	return num;
}
int main() {
	int choice = 0;
	char* next_node;
	init(init_pack);
	while (1) {
		printf("Node_Pos - > %d\n", Node_pos);
		plot_output(Node_pos);
		choice = common_command_Trans(NodeToAction(plot_storage.file_node[Node_pos]));
		switch (choice)
		{
		case 1:
			next_node = plot_storage.file_node[Node_pos].selections[0].next_node;
			Node_pos = convertToInt(next_node) - 1;
			break;
		case 2:
			next_node = plot_storage.file_node[Node_pos].selections[1].next_node;
			Node_pos = convertToInt(next_node) - 1;
			break;
		case 3:
			next_node = plot_storage.file_node[Node_pos].selections[2].next_node;
			Node_pos = convertToInt(next_node) - 1;
			break;
		default:
			break;
		}
	}
}
/*char filename[10];
printf("���������õ��ļ�����");
scanf_s("%s", filename, 10);
LOADER(filename, 1);*/

