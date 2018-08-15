#pragma once
#include <WinSock2.h>

class CNetwork
{
public: 
	SOCKET m_sock;
	sc_packet m_client;
	bool start;
	int m_Clientid;
	CImage m_Image;
	CImage m_ItemImage;
	CImage m_ShiledImage;
	CImage m_ArrowImage;
	CImage m_FireImage;
	CImage m_TileImage;
	CImage m_GrassImage;
	CImage m_WinImage;
	CImage m_FailImage;
public:
	void Initi();
	void ReadPacket(SOCKET);
	void ProcessPacket(char*);

	

	int recvn(SOCKET s, char *buf, int len, int flags);
	void err_display(char* msg);
	void err_quit(char* msg);

	void Render(HDC, HDC);


private:
	static CNetwork* m_Instance;
public:
	static CNetwork* GetInstance()
	{
		if (NULL == m_Instance)
			m_Instance = new CNetwork();
		return m_Instance;
	}

	void Destroy()
	{
		if (NULL != m_Instance)
		{
			delete m_Instance;
			m_Instance = NULL;
		}
	}


private:
	CNetwork();
public:
	~CNetwork();
};

