#pragma once
class CMFCToolView; 
class CTerrain final 
{
public:
	CTerrain();
	~CTerrain();
public:
	const vector<TILE*>& Get_VecTile() { return m_vecTile; }
public:
	void Set_Tile(TILE* pTile) { m_vecTile.emplace_back(pTile); }
public:
	void Set_View(CMFCToolView* pView) { m_pView = pView; }
public:
	HRESULT Ready_Terrain(); 
	void Update_Terrain(); 
	void Render_Terrain(); 
	void MiniRender_Terrain(); 

	void Release_Terrain(); 
public:
	void Tile_Change_Terrain(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const BYTE& byOption =0); 
private:
	int Get_TileIndex(const D3DXVECTOR3& vPos);
	bool IsPicking(const D3DXVECTOR3& vPos, const int iIndex); 
private:
	vector<TILE*> m_vecTile; 
	CMFCToolView* m_pView; 
};

