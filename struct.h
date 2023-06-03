#ifndef __STRUCT_
#define __STRUCT_
#define MAXACTION 4
extern struct DASHBOARD DASHBOARD;
typedef struct SELF{
	char NAME[10];
	int HEALTH;
	int HUNGER;
	int THIRSTY;
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
}ITEM;

typedef struct BACKPACK {
	struct ITEM ITEMINPACK[8];
}BACKPACK;
typedef struct ACTION {
	int actionNum;
	char action[MAXACTION][32];
}ACTION;
#endif