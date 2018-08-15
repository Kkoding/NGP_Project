#pragma comment(lib, "ws2_32")
#pragma comment(lib, "winmm.lib")

#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "protocol.h"

using namespace std;

#define SERVERPORT 9000
#define BUFSIZE    512

sc_packet g_Client;
CRITICAL_SECTION cs;

static float g_itemTime;
static float g_NowTime = 0;
static bool g_ready = false;


void Bullet_Initialize(int ci);

// 소켓 함수 오류 출력 후 종료
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int  left = len;

	while (left > 0)
	{
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
	return (len - left);
}

void collision()
{
	for (int i = 0; i < MAX_USER; ++i) {
		if (false == g_Client.player[i].connect)
			continue;
		else if (State_None != g_Client.player[i].state)
			continue;

		int cx = g_Client.player[i].x;
		int cy = g_Client.player[i].y;

		for (int j = 0; j < MAX_BULLET; ++j)
		{
			if (cx + OBJ_SIZE >= g_Client.bullet[j].x && cy + OBJ_SIZE >= g_Client.bullet[j].y &&
				cx <= g_Client.bullet[j].x + BULLET_SIZE && cy <= g_Client.bullet[j].y + BULLET_SIZE)
			{

				if (g_Client.player[i].is_protect)
					g_Client.player[i].is_protect = false;
				//	else
				//		g_Client.player[i].connect = false;

				EnterCriticalSection(&cs);
				Bullet_Initialize(j);
				LeaveCriticalSection(&cs);
			}
		}
		for (int k = 0; k < OBSTACLE_NUM; ++k)
		{
			if (cx + OBSTACLE_SIZE >= g_Client.obstacle[k].x && cy + OBSTACLE_SIZE >= g_Client.obstacle[k].y &&
				cx <= g_Client.obstacle[k].x + BULLET_SIZE && cy <= g_Client.obstacle[k].y + BULLET_SIZE)
			{
				g_Client.player[i].is_protect = false;
				g_Client.player[i].connect = false;
			}
		}

		if (g_Client.item.state)
		{
			if (cx + OBJ_SIZE >= g_Client.item.x && cy + OBJ_SIZE >= g_Client.item.y &&
				cx <= g_Client.item.x + OBJ_SIZE && cy <= g_Client.item.y + OBJ_SIZE)
			{
				g_Client.item.state = false;
				g_Client.player[i].is_protect = true;
				g_itemTime = g_NowTime;
			}
		}
	}
}

void Bullet_Initialize(int ci)
{
	switch (g_Client.bullet[ci].dir)
	{
	case Bullet_LEFT:
		g_Client.bullet[ci].x = WIN_WIDTH + rand() % WIN_WIDTH;
		g_Client.bullet[ci].y = WINCY + (rand() % WCYSIZE);
		break;
	case Bullet_RIGHT:
		g_Client.bullet[ci].x = 0 - (rand() % WIN_WIDTH);
		g_Client.bullet[ci].y = WINCY + (rand() % WCYSIZE);
		break;
	case Bullet_UP:
		g_Client.bullet[ci].x = WINCX + rand() % WCXSIZE;
		g_Client.bullet[ci].y = WIN_HEIGHT + rand() % WIN_HEIGHT;

		break;
	case Bullet_DOWN:
		g_Client.bullet[ci].x = WINCX + rand() % WCXSIZE;
		g_Client.bullet[ci].y = 0 - rand() % WIN_HEIGHT;
		break;
	}
	g_Client.bullet[ci].speed = 5 + rand() % BULLET_SPEED;
	g_Client.bullet[ci].die = false;
}

void Initialize()
{
	int value;
	g_Client.start = false;

	for (int i = 0; i < MAX_USER; ++i) {
		g_Client.player[i].connect = false;
		g_Client.player[i].is_protect = false;
		g_Client.player[i].state = State_None;
	}

	for (int j = 0; j < 100; ++j) {
		Sleep(0.5);
		value = rand() % 4;
		g_Client.bullet[j].x = WINCX + WCXSIZE + (rand() % WCXSIZE);
		g_Client.bullet[j].die = false;
		g_Client.bullet[j].speed = 5 + rand() % BULLET_SPEED;
		switch (value)
		{
		case Bullet_LEFT:
			g_Client.bullet[j].dir = Bullet_LEFT;
			g_Client.bullet[j].x = WIN_WIDTH + rand() % WIN_WIDTH;
			g_Client.bullet[j].y = WINCY + (rand() % WCYSIZE);
			break;
		case Bullet_RIGHT:
			g_Client.bullet[j].dir = Bullet_RIGHT;
			g_Client.bullet[j].x = 0 - (rand() % WIN_WIDTH);
			g_Client.bullet[j].y = WINCY + (rand() % WCYSIZE);
			break;
		case Bullet_UP:
			g_Client.bullet[j].dir = Bullet_UP;
			g_Client.bullet[j].x = WINCX + rand() % WCXSIZE;
			g_Client.bullet[j].y = WIN_HEIGHT + rand() % WIN_HEIGHT;

			break;
		case Bullet_DOWN:
			g_Client.bullet[j].dir = Bullet_DOWN;
			g_Client.bullet[j].x = WINCX + rand() % WCXSIZE;
			g_Client.bullet[j].y = 0 - rand() % WIN_HEIGHT;
			break;
		}
	}
	g_Client.item.state = false;

	g_Client.obstacle[0].x = 600;
	g_Client.obstacle[0].y = 300;

	g_Client.obstacle[1].x = 450;
	g_Client.obstacle[1].y = 550;

	g_Client.obstacle[2].x = 750;
	g_Client.obstacle[2].y = 550;

	InitializeCriticalSection(&cs);
	g_itemTime = timeGetTime()*0.001;
	std::cout << "Server Initialize Complete !" << std::endl;

}

void Bullet_Update()
{
	// 총알 움직이기.
	for (int j = 0; j < MAX_BULLET; ++j)
	{
		if (g_Client.bullet[j].dir == Bullet_LEFT) {
			g_Client.bullet[j].x -= g_Client.bullet[j].speed;
			if (g_Client.bullet[j].x <= 0)
				Bullet_Initialize(j);
		}
		else if (g_Client.bullet[j].dir == Bullet_RIGHT) {
			g_Client.bullet[j].x += g_Client.bullet[j].speed;
			if (g_Client.bullet[j].x >= WIN_WIDTH)
				Bullet_Initialize(j);
		}
		else if (g_Client.bullet[j].dir == Bullet_DOWN) {
			g_Client.bullet[j].y += g_Client.bullet[j].speed;
			if (g_Client.bullet[j].y >= WIN_HEIGHT)
				Bullet_Initialize(j);
		}
		else if (g_Client.bullet[j].dir == Bullet_UP) {
			g_Client.bullet[j].y -= g_Client.bullet[j].speed;
			if (g_Client.bullet[j].y <= 0)
				Bullet_Initialize(j);
		}
	}
	//아이템 생성
	if (g_NowTime - g_itemTime > 5.f)
	{
		if (!g_Client.item.state) {
			g_Client.item.x = 500 + 100 * (rand() % 2);
			g_Client.item.y = 500 - 50 * (rand() % 3);
			g_Client.item.state = true;
		}
	}

	////승패처리
	//int win = 0;
	//int lose = 0;
	//for (int i = 0; i < MAX_USER; ++i) {
	//	if (!g_Client.player[i].connect)
	//		lose++;
	//	else
	//		win = i;
	//}

	//if (lose == MAX_USER - 1) {
	//	for (int i = 0; i < MAX_USER; ++i) {
	//		if (win == i) g_Client.player[i].state = State_Win;
	//		else g_Client.player[i].state = State_Lose;
	//	}
	//}

}
DWORD WINAPI MainProcessPacket(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;

	while (1) {

		cs_packet packet;
		recvn(client_sock, (char*)&packet, sizeof(cs_packet), 0);
		int ci_id = packet.id;
		g_NowTime = timeGetTime()*0.001;

		if (g_Client.start)
		{
			// 키보드입력값 처리

			if (packet.keyboard != 0)
			{
				if (packet.keyboard == CS_UP) {
					if (g_Client.player[ci_id].y > WINCY)
						g_Client.player[ci_id].y -= 10;
				}
				else if (packet.keyboard == CS_DOWN) {
					if (g_Client.player[ci_id].y + OBJ_SIZE < WINCY + WCYSIZE)
						g_Client.player[ci_id].y += 10;
				}
				if (packet.keyboard == CS_RIGHT) {
					if (g_Client.player[ci_id].x + OBJ_SIZE < WINCX + WCXSIZE)
						g_Client.player[ci_id].x += 10;
				}
				else if (packet.keyboard == CS_LEFT) {
					if (g_Client.player[ci_id].x > WINCX)
						g_Client.player[ci_id].x -= 10;
				}
			}

			Bullet_Update();
			collision();
		}
		send(client_sock, (char*)&g_Client, sizeof(sc_packet), 0);
	}
	return 0;
}

DWORD WINAPI ProcessPacket(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	int retval;

	while (1) {

		cs_packet packet;
		recvn(client_sock, (char*)&packet, sizeof(cs_packet), 0);
		int ci_id = packet.id;

		if (g_Client.start)
		{
			// 키보드입력값 처리
			if (packet.keyboard != 0)
			{
				if (packet.keyboard == CS_UP) {
					if (g_Client.player[ci_id].y > WINCY)
						g_Client.player[ci_id].y -= 10;
				}
				else if (packet.keyboard == CS_DOWN) {
					if (g_Client.player[ci_id].y + OBJ_SIZE < WINCY + WCYSIZE)
						g_Client.player[ci_id].y += 10;
				}
				if (packet.keyboard == CS_RIGHT) {
					if (g_Client.player[ci_id].x + OBJ_SIZE < WINCX + WCXSIZE)
						g_Client.player[ci_id].x += 10;
				}
				else if (packet.keyboard == CS_LEFT) {
					if (g_Client.player[ci_id].x > WINCX)
						g_Client.player[ci_id].x -= 10;
				}
			}
			//std::cout << g_NowTime - g_itemTime << std::endl;
		}

		send(client_sock, (char*)&g_Client, sizeof(sc_packet), 0);
		//std::cout << packet.keyboard << std::endl;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));


	int retval;
	Initialize();
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	HANDLE hThread[3];
	int addrlen;
	char buf[BUFSIZE + 1];
	int len;
	while (1)
	{
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// 접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		int id = -1;
		for (int i = 0; i < MAX_USER; ++i)
		{
			if (g_Client.player[i].connect == false)
			{
				id = i;
				g_Client.player[i].connect = true;
				break;
			}
		}
		g_Client.player[id].x = 500 + 100 * id;
		g_Client.player[id].y = 450;
		g_Client.id = id;
		g_Client.start = false;
		//send(client_sock, (char*)&len, sizeof(int), 0);
		send(client_sock, (char*)&g_Client, sizeof(sc_packet), 0);


		if (0 == id)
			hThread[id] = CreateThread(NULL, 0, MainProcessPacket, (LPVOID)client_sock, 0, NULL);
		else
			hThread[id] = CreateThread(NULL, 0, ProcessPacket, (LPVOID)client_sock, 0, NULL);

		if (id == MAX_USER - 1) {
			g_Client.start = true;
		}

	}



	if (hThread == NULL) {
		closesocket(client_sock);
	}
	else
		CloseHandle(hThread);


	// closesocket()
	closesocket(listen_sock);

	DeleteCriticalSection(&cs);
	// 윈속 종료
	WSACleanup();
	return 0;
}