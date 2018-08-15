#pragma once
class CMainGame
{
private:
	sc_packet Client;

	
public:
	void Initi();
	void Render();
	void Update();

public:
	CMainGame();
	~CMainGame();
};

