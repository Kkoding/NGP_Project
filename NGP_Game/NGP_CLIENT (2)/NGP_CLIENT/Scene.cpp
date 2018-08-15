#include "stdafx.h"
#include "Scene.h"


void CScene::Update()
{

}

void CScene::Render(HDC hdc)
{
	HDC mem0dc;
	HBITMAP hBit;
	RECT rt;
	GetClientRect(g_hWnd, &rt);

	mem0dc = CreateCompatibleDC(hdc);
	hBit = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);

	SelectObject(mem0dc, hBit);
	FillRect(mem0dc, &rt, RGB(0, 0, 0));

	//////////////////////////
	Rectangle(mem0dc, 200, 200, 600, 600);
	//Rectangle(mem0dc, 500, 500, 600, 600);
	CObjMgr::GetInstance()->Render(mem0dc);
	
	


	//////////////////////////
	BitBlt(hdc, 0, 0, rt.right, rt.bottom, mem0dc, 0, 0, SRCCOPY);
	DeleteObject(hBit);
	DeleteDC(mem0dc);
}

void CScene::Initi()
{
	CObjMgr::GetInstance()->Initi();
}

CScene::CScene()
{
}


CScene::~CScene()
{
}
