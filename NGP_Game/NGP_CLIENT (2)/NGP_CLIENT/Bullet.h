#pragma once

class CObj;

class CBullet : public CObj
{
private:
	float CreateTimer;
	list<Bullet_Info> m_BulletInfo;
	float create_timer;

public:
	void AutoMovePos(eBulletDir, Bullet_Info& );
	void AddPos(int, int, Bullet_Info&);
	void MakeBullet();

	void SetPos(Bullet_Info&);
	eBulletDir SetDir(int);
	
public:
	int Update();
	void Render(HDC);
	void Initi();

public:
	CBullet();
	~CBullet();
};

