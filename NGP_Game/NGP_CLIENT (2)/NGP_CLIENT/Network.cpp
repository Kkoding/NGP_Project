#include "stdafx.h"
#include "Network.h"
#include <windows.h>

#pragma comment(lib,"msimg32.lib")
#pragma comment(lib, "winmm.lib")

CNetwork* CNetwork::m_Instance = NULL;

void CNetwork::Initi()
{
	int retval;

	m_Image.Load("bullet_boss.png");
	m_ItemImage.Load("item.png");
	m_ShiledImage.Load("shield.png");
	m_ArrowImage.Load("arrow.png");
	m_FireImage.Load("fire.png");
	m_TileImage.Load("tile.png");
	m_GrassImage.Load("grass.png");
	m_WinImage.Load("win.png");
	m_FailImage.Load("lose.png");

	WSADATA	wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	// socket()
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET) err_quit("socket()");

	SOCKADDR_IN ServerAddr;
	ZeroMemory(&ServerAddr, sizeof(SOCKADDR_IN));
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(SERVERPORT);
	ServerAddr.sin_addr.s_addr = inet_addr(IP);

	retval = connect(m_sock, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");
	recvn(m_sock, (char*)& m_client, sizeof(sc_packet), 0);

	cs_packet packet;
	int len;
	m_Clientid = m_client.id;



}

void CNetwork::ReadPacket(SOCKET sock)
{



}

void CNetwork::ProcessPacket(char *ptr)
{

}

int CNetwork::recvn(SOCKET s, char * buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
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

void CNetwork::err_display(char * msg)
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

void CNetwork::err_quit(char * msg)
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

void CNetwork::Render(HDC mem0dc, HDC mem1dc)
{

	//잔디 맵 그려줌
	for (int i = 0; i < WIN_WIDTH / m_GrassImage.GetWidth();++i)
	{
		for (int j = 0; j < WIN_HEIGHT / m_GrassImage.GetHeight(); ++j)
		{
			m_GrassImage.TransparentBlt(mem0dc, m_GrassImage.GetWidth()*i, m_GrassImage.GetHeight()*j, m_GrassImage.GetWidth()
				, m_GrassImage.GetHeight(), RGB(255, 255, 255));
		}
	}
	// 울타리 세로
	for (int i = 0; i < 13; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			m_TileImage.TransparentBlt(mem0dc, WINCX - 50 + i * 50, WINCY - 50 + 500 * j, m_TileImage.GetWidth()
				, m_TileImage.GetHeight(), RGB(255, 255, 255));
		}
	}
	// 울타리 가로
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			m_TileImage.TransparentBlt(mem0dc, WINCX - 50 + 600*j, WINCY + 50 * i, m_TileImage.GetWidth()
				, m_TileImage.GetHeight(), RGB(255, 255, 255));
		}
	}

	if (false == m_client.start) {
		TextOut(mem0dc, 100, 100, "잠시만 기다려주세요", 19);
		return;
	}
	else if (m_client.player[m_Clientid].state == State_Win) {
		TextOut(mem0dc, 100, 100, "게임에서 승리했습니다", 21);
		/*m_WinImage..TransparentBlt(mem0dc, 200,200, m_WinImage.GetWidth()
			, m_WinImage.GetHeight(), RGB(255, 255, 255));*/
	}
	else if (m_client.player[m_Clientid].state == State_Lose) {
		TextOut(mem0dc, 100, 100, "게임에서 패배했습니다", 21);
		/*m_FailImage..TransparentBlt(mem0dc, 200, 200, m_FailImage.GetWidth()
			, m_FailImage.GetHeight(), RGB(255, 255, 255));*/
	}
	else TextOut(mem0dc, 100, 100, "게임이 시작되었습니다.", 22);

	for (int i = 0; i < MAX_USER; ++i)
	{
		// 아이템 흭득시 보호막

		// 플레이어 
		if (m_client.player[i].connect)
		{
			TransparentBlt(mem0dc, m_client.player[i].x, m_client.player[i].y, OBJ_SIZE, OBJ_SIZE, mem1dc, 0, 0, 50, 50, RGB(255, 255, 255));
			//플레이어 표시
			if (i == CNetwork::GetInstance()->m_Clientid)
				m_ArrowImage.TransparentBlt(mem0dc, m_client.player[i].x + 13, m_client.player[i].y - 20, m_ArrowImage.GetWidth()
					, m_ArrowImage.GetHeight(), RGB(255, 255, 255));
		}

		if (m_client.player[i].is_protect)
		{
			m_ShiledImage.TransparentBlt(mem0dc, m_client.player[i].x - 25, m_client.player[i].y - 25, m_ShiledImage.GetWidth()
				, m_ShiledImage.GetHeight(), RGB(255, 255, 255));
		}

		//총알
		for (int j = 0; j < MAX_BULLET; ++j)
		{
			if (!m_client.bullet[j].die)
				m_Image.TransparentBlt(mem0dc, m_client.bullet[j].x, m_client.bullet[j].y, m_Image.GetWidth()
					, m_Image.GetHeight(), RGB(255, 255, 255));
		}
	}

	if (TRUE == m_client.item.state)
	{
		m_ItemImage.TransparentBlt(mem0dc, m_client.item.x, m_client.item.y, m_ItemImage.GetWidth() 
			, m_ItemImage.GetHeight(), RGB(255, 255, 255));
	}

	for (int i = 0; i < OBSTACLE_NUM; ++i) {
		/*Rectangle(mem0dc,
			m_client.obstacle[i].x,
			m_client.obstacle[i].y,
			m_client.obstacle[i].x + OBSTACLE_SIZE,
			m_client.obstacle[i].y + OBSTACLE_SIZE);*/
		m_FireImage.TransparentBlt(mem0dc, m_client.obstacle[i].x - 5, m_client.obstacle[i].y - 10, m_FireImage.GetWidth(), m_FireImage.GetHeight(), RGB(255, 255, 255));
	}
}


CNetwork::CNetwork()
{
	start = false;
}


CNetwork::~CNetwork()
{
}
