#pragma once

class CObj;

class CObjMgr
{
private:
	list<CObj*> m_lObj[OBJ_END];

public:
	void Update();
	void Render(HDC);
	void Initi();
	void ChangePlayerPos(eObj, int, int);



////////////////////////////////////
private:
	static CObjMgr* m_hInstance;
public:
	static CObjMgr* GetInstance()
	{
		if (m_hInstance == NULL)
			m_hInstance = new CObjMgr();
		return m_hInstance;
	}

	void Destroy() 
	{
		if (m_hInstance != NULL)
		{
			delete m_hInstance;
			m_hInstance = NULL;	
		}
	}
private:
	CObjMgr();
public:
	~CObjMgr();



};

