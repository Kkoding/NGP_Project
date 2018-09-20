#include "stdafx.h"
#include "MainGame.h"
#include "resource.h"

void CMainGame::Initi()
{
	CNetwork::GetInstance()->Initi();

}

void CMainGame::Render()
{
	g_hdc = GetDC(g_hWnd);

	HDC mem0dc, mem1dc;
	HBITMAP hBit, PlayerBit, BulletBit;
	RECT rt;
	static BITMAP bmp;
	GetClientRect(g_hWnd, &rt);

	mem0dc = CreateCompatibleDC(g_hdc);
	hBit = CreateCompatibleBitmap(g_hdc, rt.right, rt.bottom);
	SelectObject(mem0dc, hBit);
	mem1dc = CreateCompatibleDC(g_hdc);
	FillRect(mem0dc, &rt, RGB(0, 0, 0));


	/////	더블버퍼링 시작
	//////////////////////////

	PlayerBit = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	SelectObject(mem1dc, PlayerBit);

	CNetwork::GetInstance()->Render(mem0dc, mem1dc);

	//////////////////////////
	//////	더블버퍼링 끝
	BitBlt(g_hdc, 0, 0, rt.right, rt.bottom, mem0dc, 0, 0, SRCCOPY);
	DeleteObject(hBit);
	DeleteObject(PlayerBit);
	DeleteDC(mem0dc);
	DeleteDC(mem1dc);
	ReleaseDC(g_hWnd, g_hdc);
}

void CMainGame::Update()
{
	cs_packet cs_key;
	
	cs_key.keyboard = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		cs_key.keyboard = CS_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		cs_key.keyboard = CS_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		cs_key.keyboard = CS_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		cs_key.keyboard = CS_DOWN;


	cs_key.id = CNetwork::GetInstance()->m_Clientid;
	send(CNetwork::GetInstance()->m_sock,
		(char*)&cs_key, sizeof(cs_packet), 0);

	CNetwork::GetInstance()->recvn(CNetwork::GetInstance()->m_sock,
		(char*)&CNetwork::GetInstance()->m_client, sizeof(sc_packet), 0);


}

CMainGame::CMainGame()
{

}


CMainGame::~CMainGame()
{
}
