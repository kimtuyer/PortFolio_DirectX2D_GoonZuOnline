#pragma once
#include "GameObject.h"
class CTerrain final : public CGameObject
{
public:
	CTerrain();
	~CTerrain();
public:
	const vector<TILE*>& Get_VecTile() { return m_vecTile; }
	vector<list<TILE*>>& Get_Graph() { return m_vecGraph; }
	vector<list<TILE*>>& Get_MonsterGraph() { return m_vecMonsterGraph; }


public:
	HRESULT Create_PlayerGraph_Terrain();
	HRESULT Create_MonsterGraph_Terrain();

	HRESULT LoadTileData_Terrain(const wstring& wstrFilePath); 
	HRESULT LoadTileData_MapObject(const wstring& wstrFilePath);
	int CTerrain::Get_TileIndex(const D3DXVECTOR3 & vPos)
	{
		int iSize = m_vecTile.size();
		for (int i = 0; i < iSize; ++i)
		{
			if (IsPicking(vPos, i))
				return i;
		}

		return -1;
	}

	bool CTerrain::IsPicking(const D3DXVECTOR3 & vPos, const int iIndex)
	{
		// 내적을 이용해서 타일 픽킹 ㄱㄱ. 
		// 일단 마름모꼴 타일의 각 꼭지점을 구하자. 

		D3DXVECTOR3 vVertex[4] =
		{
			{ m_vecTile[iIndex]->vPos.x ,m_vecTile[iIndex]->vPos.y + (TILECY >> 1), 0.f },
			{ m_vecTile[iIndex]->vPos.x + (TILECX >> 1),m_vecTile[iIndex]->vPos.y , 0.f },
			{ m_vecTile[iIndex]->vPos.x ,m_vecTile[iIndex]->vPos.y - (TILECY >> 1), 0.f },
			{ m_vecTile[iIndex]->vPos.x - (TILECX >> 1) ,m_vecTile[iIndex]->vPos.y , 0.f }
		};

		// 챕터 2. 각 꼭지점에서 방향벡터를 구하자! 0 ->1 1 ->2 ...
		D3DXVECTOR3 vVertexDir[4] =
		{
			vVertex[1] - vVertex[0],
			vVertex[2] - vVertex[1],
			vVertex[3] - vVertex[2],
			vVertex[0] - vVertex[3]
		};
		// 챕터3. 법선백터를 뽑아내자!!! 
		D3DXVECTOR3 vNormal[4] =
		{
			{-vVertexDir[0].y, vVertexDir[0].x, 0.f },
			{ -vVertexDir[1].y, vVertexDir[1].x, 0.f },
			{ -vVertexDir[2].y, vVertexDir[2].x, 0.f },
			{ -vVertexDir[3].y, vVertexDir[3].x, 0.f },
		};

		//챕터 4. 각 꼭지점에서 마우스를 바라보는 방향벡터를 구해라!!!! 
		D3DXVECTOR3 vMouseDir[4] =
		{
			// 마우스 - 꼭지점 영번째 
			vPos - vVertex[0],
			vPos - vVertex[1],
			vPos - vVertex[2],
			vPos - vVertex[3],
		};

		// 이제 나 다 구했다!!! 

		for (int i = 0; i < 4; ++i)
		{
			if (0 < D3DXVec3Dot(&vMouseDir[i], &vNormal[i]))
				return false;
		}
		return true;
	}

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;


	void Set_vecTile(TILE* pTile) { m_vecTile.emplace_back(pTile); }

private:
	vector<TILE*> m_vecTile; 
	vector<MAPOBJECT*>m_vecMap;
	
	vector<list<TILE*>> m_vecGraph; 
	vector<list<TILE*>> m_vecMonsterGraph;



};




