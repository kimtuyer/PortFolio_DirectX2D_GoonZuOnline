#pragma once
class CScene; 
class CScene_Manager
{
	DECLARE_SINGLETON(CScene_Manager)
public:
	enum ID {LOADING, Start,HanYang,KwangHwa,STAGE, KwangHwa2, DAEMA,END};
private:
	CScene_Manager();
	~CScene_Manager();
public:
	HRESULT Change_Scene_Manager(ID eNextScene); 
	void	Update_Scene_Manager();
	void	Render_Scene_Manager();
	void	Release_Scene_Manager();
private:
	ID m_eCurScene; 
	ID m_eNextScene; 
	CScene* m_pScene; 
};

