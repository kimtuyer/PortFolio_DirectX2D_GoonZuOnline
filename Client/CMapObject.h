#pragma once
#include "GameObject.h"
class CMapObject :
	public CGameObject
{
public:
	CMapObject();
	~CMapObject();
public:
	const vector<MAPOBJECT*>& Get_VecTile() { return m_vecMap; }
	void Set_VecMap(MAPOBJECT* pmap) { m_vecMap.emplace_back(pmap); }
public:
	HRESULT Create_Graph_Terrain();
	HRESULT LoadTileData_Terrain(const wstring& wstrFilePath);
	HRESULT LoadTileData_MapObject(const wstring& wstrFilePath);



public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

	
	D3DXVECTOR2* Get_Collider2() {
		return m_ColliderInfo[MAP_Object::id_2] //한양 건물!
			;
	}


	D3DXVECTOR2* Get_Collider26() {
		return m_ColliderInfo[MAP_Object::id_26] //한양 건물!
			;
	}
	D3DXVECTOR2* Get_Collider31() {
		return m_ColliderInfo[MAP_Object::id_31]
			;
	}

	D3DXVECTOR2* Get_Collider33() {
		return m_ColliderInfo[MAP_Object::id_33]
			;
	}

	D3DXVECTOR2* Get_Collider34() {
		return m_ColliderInfo[MAP_Object::id_34]// 탑
			;
	}

	D3DXVECTOR2* Get_Collider39() {
		return m_ColliderInfo[MAP_Object::id_39]
			;
	}

	D3DXVECTOR2* Get_Collider68() {
		return m_ColliderInfo[MAP_Object::id_68]
			;
	}

	D3DXVECTOR2* Get_Collider66() {
		return m_ColliderInfo[MAP_Object::id_66]
			;
	}


private:
	vector<MAPOBJECT*>m_vecMap;
	D3DXVECTOR2 m_ColliderInfo[MAP_Object::id_END][5];

};

