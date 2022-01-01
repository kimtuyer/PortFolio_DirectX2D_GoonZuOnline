#pragma once
#include "Scene.h"
class CGameObject_Manager;
class KwangHwa_Scene2 :
	public CScene
{
public:
	explicit KwangHwa_Scene2();
	virtual ~KwangHwa_Scene2();
public:
	HRESULT LoadData_MAPObject(const wstring& wstrFilePath);
	HRESULT LoadData_TILEObject(const wstring& wstrFilePath);

	HRESULT LoadData_Object(const wstring& wstrFilePath);

	// CScene을(를) 통해 상속됨
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
private:
	CGameObject_Manager* m_pGameObject_Manager;
};

