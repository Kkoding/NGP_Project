#pragma once

class CObj;

class CPlayer : public CObj
{
public:
	int Update();
	void Render(HDC);
	void Initi();

public:
	CPlayer();
	~CPlayer();
};

