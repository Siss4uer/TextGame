#ifndef __STRUCT_
#define __STRUCT_
#define MAXACTION 4
extern struct DASHBOARD DASHBOARD;
typedef struct SELF{
	char NAME[10];
	int HEALTH;
	int HUNGER;
	int DESIRED;
	int SAN;
}SELF;

typedef struct TIME {
	int DAY;
	int HOURS;
	int MINUTES;
}TIME;

typedef struct BUFF {
	int BUFFID;
	char BUFFNAME[10];
	char DESCRIPTION[1024];
}BUFF;

typedef struct BUFFLIST {
	int NUM;
	struct BUFF BUFF[6];
}BUFFLIST;

typedef struct DASHBOARD{
	int SCORE;
	struct SELF SELF;
	struct TIME TIME;
	struct BUFFLIST BUFFLIST;
};

typedef struct ITEM {
	int ITEMID;
	char ITEMNAME[64];
	char DESCRIPTION[1024];
	int NBT[3];
	int OPERATE[4];
}ITEM;
typedef struct ITEM_USED {
	int ITEMID;
	int NBT[3];
}ITEM_USED;
typedef struct ITEM_USED_LIST {
	int NUM;
	struct ITEM_USED ITEM_USED[8];
}ITEM_USED_LIST;
//OPERATE
//��һ��ֵ�����Ѫ������ ����ֵ����100ʱ��Ϊ����Ѫ��������
//�ڶ���ֵ����Լ���ֵ����
//������ֵ�����ϣ��ֵ���� ����ֵ����100ʱ��Ϊ����ϣ��������
//���ĸ�ֵ���������ֵ����

typedef struct BACKPACK {
	struct ITEM ITEMINPACK[8];
}BACKPACK;
typedef struct ACTION {
	int actionNum;
	char action[MAXACTION][32];
}ACTION;

typedef struct Selection {
	int operate[4];
	char next_node[50];
} Selection;

typedef struct Node{
	char command[50];
	int action;
	Selection selections[4];
} Node;

typedef struct PLOT_STORAGE {
	struct Node file_node[32];
}PLOT_STORAGE;
#endif