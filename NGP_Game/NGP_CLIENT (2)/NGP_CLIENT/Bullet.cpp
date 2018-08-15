#include "stdafx.h"
#include "Bullet.h"


void CBullet::AutoMovePos(eBulletDir type, Bullet_Info& tp)
{
	switch (type)
	{
	case (DIR_LEFT):
		AddPos(-tp.Bullet_speed, 0, tp);
		break;
	case (DIR_RIGHT):
		AddPos(tp.Bullet_speed, 0, tp);
		break;
	case (DIR_DOWN):
		AddPos(0, tp.Bullet_speed, tp);
		break;
	case (DIR_UP):
		AddPos(0, -tp.Bullet_speed, tp);
		break;
	}

}

void CBullet::AddPos(int x, int y, Bullet_Info& Info)
{
	Info.pos.x += x;
	Info.pos.y += y;
	if (DIR_LEFT == Info.BulletDir) {

		if (Info.pos.x < 0)
			Info.BulletDir = DIR_END;
	}
	else if (DIR_RIGHT == Info.BulletDir) {

		if (Info.pos.x > 750)
			Info.BulletDir = DIR_END;
	}

	else if (DIR_DOWN == Info.BulletDir) {
		if (Info.pos.y > 800)
			Info.BulletDir = DIR_END;
	}

	else if (DIR_UP == Info.BulletDir) {
		if (Info.pos.y < 0)
			Info.BulletDir = DIR_END;
	}
}

void CBullet::MakeBullet()
{
	//	default_random_engine dre;
	//	uniform_int_distribution<> ui;

	Bullet_Info temp_Info;
	temp_Info.BulletDir = SetDir(rand() % DIR_END);
	SetPos(temp_Info);

	temp_Info.Bullet_speed = 20 + rand() % 10;
	m_BulletInfo.push_back(temp_Info);
	create_timer = GetTickCount();
}

void CBullet::SetPos(Bullet_Info& type)
{
	switch (type.BulletDir)
	{
	case DIR_LEFT:
		type.pos.x = 750;
		type.pos.y = 200 + rand() % 400;
		break;
	case DIR_RIGHT:
		type.pos.x = 0;
		type.pos.y = 200 + rand() % 400;
		break;
	case DIR_DOWN:
		type.pos.x = 200 + rand() % 400;
		type.pos.y = 0;
		break;
	case DIR_UP:
		type.pos.x = 200 + rand() % 400;
		type.pos.y = 800;
		break;
	}

}

eBulletDir CBullet::SetDir(int num)
{
	return (eBulletDir)num;
}

int CBullet::Update()
{

	auto iter = m_BulletInfo.begin();
	auto end_iter = m_BulletInfo.end();
	for (; iter != end_iter; ++iter) {
		AutoMovePos((*iter).BulletDir, (*iter));
			if ((*iter).pos.x > 750)
			{
				iter = m_BulletInfo.erase(iter);
			}
	}
	if (GetTickCount() - create_timer > 350.f)
		MakeBullet();

	return 0;
}

void CBullet::Render(HDC hdc)
{

}

void CBullet::Initi()
{
	create_timer = GetTickCount();
}

//200 600
CBullet::CBullet()
{

	srand(unsigned(time));
	CreateTimer = GetTickCount();
	Bullet_Info tInfo;
	tInfo.BulletDir = DIR_RIGHT;
	tInfo.pos.x = 0;
	tInfo.pos.y = 200;
	tInfo.Bullet_speed = 10;
	m_BulletInfo.push_back(tInfo);


}


CBullet::~CBullet()
{
}
