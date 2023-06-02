#ifndef __STRUCT_
#define __STRUCT_
extern struct DASHBOARD DASHBOARD;
typedef struct SELF{
	char NAME[10];
	int HEALTH;
	int HUNGER;
	int THIRSTY;
}SELF;

typedef struct ORDER {
	int MODE;
	int ORDERNUM;
	char TEXT[128];
}ORDER;

typedef struct TIME {
	int DAY;
	int HOURS;
	int MINUTES;
}TIME;

typedef struct BUFF {
	int BUFFID;
	char BUFFNAME[64];
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
	int NBT[16];
	char ITEMNAME[64];
	char DESCRIPTION[1024];
}ITEM;

typedef struct BACKPACK {
	struct ITEM ITEMINPACK[128];
}BACKPACK;

typedef struct CONFIG{
	char key[20];
	char value[50];
}CONFIG;
#endif