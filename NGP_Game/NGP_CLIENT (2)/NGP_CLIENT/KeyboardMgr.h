#pragma once
class CKeyboardMgr
{
public:
	void Update();
	void Render();




////////////////////////////////
private:
	static CKeyboardMgr* m_Instance;
public:
	static CKeyboardMgr* GetInstance()
	{
		if (m_Instance == NULL)
			m_Instance = new CKeyboardMgr();
		return m_Instance;
	}

	void Destroy()
	{
		if (m_Instance != NULL)
			delete m_Instance;
		m_Instance = NULL;
	}

private:
	CKeyboardMgr();
public:
	~CKeyboardMgr();
};

