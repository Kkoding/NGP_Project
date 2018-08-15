#pragma once
#include <Windows.h>

//Ä³¸¯ÅÍ
#define PLAYER_SIZE 30
#define PLAYER_SPEED 20



extern HDC			g_hdc;
extern HWND			g_hWnd;
extern HINSTANCE	g_hInst;
extern SOCKET		g_socket;
extern int			g_myid;


enum eObj {
	OBJ_PLAYER,
	OBJ_BULLET,
	OBJ_END
};

enum eBulletDir {
	DIR_LEFT,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_UP,
	DIR_END
};


struct Bullet_Info
{
	POINT pos;
	eBulletDir BulletDir;
	BYTE Bullet_speed;
};