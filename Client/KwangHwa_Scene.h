#pragma once
#include "Scene.h"
class CGameObject_Manager;

class KwangHwa_Scene :
	public CScene
{
public:
	explicit KwangHwa_Scene();
	virtual ~KwangHwa_Scene();
public:
	HRESULT LoadData_MAPObject(const wstring& wstrFilePath);
	HRESULT LoadData_TILEObject(const wstring& wstrFilePath);

	HRESULT LoadData_Object(const wstring& wstrFilePath);

	// CSceneÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
private:
	CGameObject_Manager* m_pGameObject_Manager;
	//int callnumber = 0; //ÀÌ ¾À »ý¼ºÇÑ È½¼ö!
};

