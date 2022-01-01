#pragma once
class CMFCToolView;

class MapUnit
{
public:
	MapUnit();
	~MapUnit();
public:
	const vector<MAPOBJECT*>& Get_VecTile() { return m_vecMapObject; }
public:
	void Set_Tile(MAPOBJECT* pTile) { m_vecMapObject.emplace_back(pTile); }
public:
	void Set_View(CMFCToolView* pView) { m_pView = pView; }
public:
	HRESULT Ready_MapUnit();
	void Update_MapUnit(D3DXVECTOR3 vMouse);
	void Render_MapUnit();
	void MiniRender_MapUnit();

	void Release_MapUnit();
	BYTE m_byDrawID=0;
	vector<MAPOBJECT*> m_vecMapObject;
public:
	void Change_MapUnit(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const BYTE& byOption = 0);
private:
	int Get_Index(const D3DXVECTOR3& vPos);
	bool IsPicking(const D3DXVECTOR3& vPos, const int iIndex);
private:	

	CMFCToolView* m_pView;
};

