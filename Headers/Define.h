#pragma once

#define °Ë 0x01
#define È° 0x02
#define ºÀ 0x04
#define OBJ_DEAD	1 
#define OBJ_NOEVENT 0
#define DECLARE_SINGLETON(ClassName)							\
public:															\
	static ClassName* Get_Instance()							\
	{															\
		if (nullptr == m_pInstance)								\
			m_pInstance = new ClassName;						\
			return m_pInstance;									\
	}															\
	static void Destroy_Instance()								\
	{															\
		if (m_pInstance)										\
		{														\
			delete m_pInstance;									\
			m_pInstance = nullptr;								\
		}														\
	}															\
private:														\
		static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)							\
ClassName* ClassName::m_pInstance = nullptr; 

#ifdef _AFX
#define ERR_MSG(msg) AfxMessageBox(msg)
#else 
#define ERR_MSG(msg) MessageBox(nullptr, msg, L"System Error", MB_OK)
#endif // _AFX
