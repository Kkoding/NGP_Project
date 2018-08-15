#pragma once
class CScene
{
private:
	int x, y;
public:
	void Update();
	void Render(HDC);
	void Initi();
public:
	CScene();
	~CScene();
};

