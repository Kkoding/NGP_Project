#include "stdafx.h"
#include "Player.h"


int CPlayer::Update()
{
////	int x = 0, y = 0;
//	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
//	//	x -= 1;
//	SetPos(-PLAYER_SPEED, 0);
//	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
//	//	x += 1;
//	SetPos(PLAYER_SPEED, 0);
//	if (GetAsyncKeyState(VK_UP) & 0x8000)
//	//	y -= 1;
//	SetPos(0, -PLAYER_SPEED);
//	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
//	//	y += 1;
//	SetPos(0, PLAYER_SPEED);
//
	return S_OK;
}

void CPlayer::Render(HDC hdc)
{
	Rectangle(hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
}

void CPlayer::Initi()
{

}

CPlayer::CPlayer()
{
	m_Rect.left = 500;
	m_Rect.top = 500;
	m_Rect.right = m_Rect.left + PLAYER_SIZE;
	m_Rect.bottom = m_Rect.top + PLAYER_SIZE;
}


CPlayer::~CPlayer()
{
}
