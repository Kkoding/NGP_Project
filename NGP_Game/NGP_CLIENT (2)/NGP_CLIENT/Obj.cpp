#include "stdafx.h"
#include "Obj.h"


void CObj::SetPos(int xPos, int yPos)
{

	m_Rect.left += xPos, m_Rect.top += yPos;
	m_Rect.right = m_Rect.left + PLAYER_SIZE;
	m_Rect.bottom = m_Rect.top + PLAYER_SIZE;
}

CObj::CObj()
{
}


CObj::~CObj()
{
}
