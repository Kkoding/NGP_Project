#pragma once
class CObj
{
protected:
	RECT m_Rect;	//∞¥√º ¡¬«•
	int m_size;		//∞¥√º ªÁ¿Ã¡Ó

public:
	virtual int Update() = 0;
	virtual void Render(HDC) = 0;
	virtual void Initi() = 0;
	virtual void SetPos(int xPos, int yPos);

public:
	CObj();
	~CObj();
};

