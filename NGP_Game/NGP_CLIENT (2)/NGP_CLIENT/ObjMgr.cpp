#include "stdafx.h"
#include "ObjMgr.h"

CObjMgr* CObjMgr::m_hInstance = NULL;


void CObjMgr::Update()
{
	//for (int i = 0; i < OBJ_END; ++i)
	//{
	//	auto iter = m_obj.begin();
	//	auto iter_end = m_obj.end();
	//	for (; iter != iter_end; ++iter)
	//		(*iter)->Update();
	//}

	

	for (int i = 0; i < OBJ_END; ++i)
	{
		auto begin = m_lObj[i].begin();
		auto end = m_lObj[i].end();
		for (; begin != end;)
			if ((*begin)->Update() == 1)
			{
				delete *begin;
				begin = m_lObj[i].erase(begin);
			}
			else ++begin;
	}
}

void CObjMgr::Render(HDC hdc)
{

	/*for (int i = 0; i < OBJ_END; ++i)
	{
		auto iter = m_obj.begin();
		auto iter_end = m_obj.end();
		for (; iter != iter_end; ++iter)
			(*iter)->Render(hdc);
	}*/
	for (int i = 0; i < OBJ_END; ++i)
	{
		auto begin = m_lObj[i].begin();
		auto end = m_lObj[i].end();
		for (; begin != end; ++begin)
			(*begin)->Render(hdc);
	}
}

void CObjMgr::Initi()
{

	//m_obj.push_back(new CPlayer());
	//m_obj.push_back(new CBullet());

}

void CObjMgr::ChangePlayerPos(eObj type, int x, int y)
{
	auto begin = m_lObj[OBJ_PLAYER].begin();
	auto end = m_lObj[OBJ_PLAYER].end();
	(*begin)->SetPos(x, y);
}

CObjMgr::CObjMgr()
{

}


CObjMgr::~CObjMgr()
{

}
