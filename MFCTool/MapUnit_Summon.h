#pragma once
class CMFCToolView;

class MapUnit_Summon
{
public:
	MapUnit_Summon();
	~MapUnit_Summon();
public:
	const vector<INFO*>& Get_VecTile() { return m_vecMapObject; }
public:
	void Set_Tile(INFO* pTile) { m_vecMapObject.emplace_back(pTile); }
public:
	void Set_View(CMFCToolView* pView) { m_pView = pView; }
public:
	HRESULT Ready_MapUnit_Summon();
	void Update_MapUnit_Summon(D3DXVECTOR3 vMouse);
	void Render_MapUnit_Summon();
	void MiniRender_MapUnit_Summon();

	void Release_MapUnit_Summon();
	BYTE m_byDrawID = 0;
	vector<INFO*> m_vecMapObject;
public:
	void Change_MapUnit_Summon(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const BYTE& byOption = 0);
private:
	int Get_Index(const D3DXVECTOR3& vPos);
	bool IsPicking(const D3DXVECTOR3& vPos, const int iIndex);
private:

	CMFCToolView* m_pView;
};

