
#pragma once

#define SERVERPORT	9000
#define IP			"127.0.0.1"
#define BUFSIZE		512

// 오브젝트 갯수
#define MAX_USER		3
#define ITEM_NUM		4
#define MAX_BULLET		15
#define OBSTACLE_NUM	3

// 총알 스피드
#define BULLET_SPEED	3

#define WINCX		350
#define WINCY		250
#define WCXSIZE		550
#define WCYSIZE		450

#define CS_UP		1
#define CS_DOWN		2
#define CS_LEFT		3
#define CS_RIGHT	4


#define OBJ_SIZE		50
#define OBSTACLE_SIZE   40
#define BULLET_SIZE		20

#define WIN_WIDTH		 1280
#define WIN_HEIGHT		 960

enum BulltDir {
	Bullet_LEFT,
	Bullet_RIGHT,
	Bullet_UP,
	Bullet_DOWN,
};

enum PLAYER_STATE {
	State_None,
	State_Win,
	State_Lose
};


#pragma pack (push,1)

struct Bullet {
	int x;
	int y;
	bool die;
	BulltDir dir;
	BYTE speed;
};

struct Item {
	int x;
	int y;
	BYTE state;
};

struct Object
{
	int x;
	int y;
	int id;
	bool is_protect;
	bool connect;
	PLAYER_STATE state;
};

struct Obstacle
{
	int x;
	int y;
};

struct sc_packet
{
	Object player[MAX_USER];
	Bullet bullet[MAX_BULLET];
	Item item;
	Obstacle obstacle[OBSTACLE_NUM];
	bool start;
	int id;
	
};

struct cs_packet
{
	int keyboard;
	int id;
};

#pragma pack (pop)