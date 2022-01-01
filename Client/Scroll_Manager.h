#pragma once
class CScroll_Manager
{
	DECLARE_SINGLETON(CScroll_Manager)
public:
	enum ID {eSB_HORZ, eSB_VERT};
private:
	CScroll_Manager();
	~CScroll_Manager();
public:
	D3DXVECTOR3 Get_Scroll(); 
	float Get_Scroll(ID eScrollBar);
	void Set_Scroll(const D3DXVECTOR3& vScroll); 
	void Set_Scroll(ID eScrollBar, const float& fScroll);
private:
	D3DXVECTOR3 m_vScroll; 
};

