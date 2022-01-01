#pragma once
#include "Scene.h"

class CGameObject_Manager;
class DAEMADO_Scene :
	public CScene
{
public:
	explicit DAEMADO_Scene();
	virtual ~DAEMADO_Scene();
public:
	HRESULT LoadData_MAPObject(const wstring& wstrFilePath);
	HRESULT LoadData_TILEObject(const wstring& wstrFilePath);

	HRESULT LoadData_Object(const wstring& wstrFilePath);

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
private:
	CGameObject_Manager* m_pGameObject_Manager;
};

