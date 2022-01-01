#pragma once
#pragma once
//0000	0001
#define KEY_LBUTTON 0x0001
//0000	0010
#define KEY_RBUTTON 0x0002
//0000	0100
#define KEY_LEFT	0x0004
//0000	1000
#define KEY_RIGHT	0x0008
//0001	0000
#define KEY_UP		0x0010
//0010	0000
#define KEY_DOWN	0x0020
#define KEY_RETURN	0x0040

#define KEY_F1	0x00008000
#define KEY_F2	0x00002000
#define KEY_F3	0x00004000
//#define KEY_	0x0400



class CKey_Manager
{
public:
	static CKey_Manager* Get_Instance()
	{
		static CKey_Manager* pInstance = nullptr;
		if (nullptr == pInstance)
			pInstance = new CKey_Manager;
		return pInstance;
	}
	static void Destroy_Instance()
	{
		CKey_Manager* pInstance = Get_Instance();
		if (pInstance)
		{
			delete pInstance;
		}
	}
private:
	explicit CKey_Manager();
	~CKey_Manager();
public:
	void Update_Key_Manager();
	bool  Key_Up(DWORD dwKey);
	bool Key_Down(DWORD dwKey);
	bool Key_Pressing(DWORD dwKey);

private:
	DWORD m_dwKey;
	DWORD m_dwKeyDown;
	DWORD m_dwKeyUP;
};

