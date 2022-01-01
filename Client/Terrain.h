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
		// ������ �̿��ؼ� Ÿ�� ��ŷ ����. 
		// �ϴ� ������� Ÿ���� �� �������� ������. 

		D3DXVECTOR3 vVertex[4] =
		{
			{ m_vecTile[iIndex]->vPos.x ,m_vecTile[iIndex]->vPos.y + (TILECY >> 1), 0.f },
			{ m_vecTile[iIndex]->vPos.x + (TILECX >> 1),m_vecTile[iIndex]->vPos.y , 0.f },
			{ m_vecTile[iIndex]->vPos.x ,m_vecTile[iIndex]->vPos.y - (TILECY >> 1), 0.f },
			{ m_vecTile[iIndex]->vPos.x - (TILECX >> 1) ,m_vecTile[iIndex]->vPos.y , 0.f }
		};

		// é�� 2. �� ���������� ���⺤�͸� ������! 0 ->1 1 ->2 ...
		D3DXVECTOR3 vVertexDir[4] =
		{
			vVertex[1] - vVertex[0],
			vVertex[2] - vVertex[1],
			vVertex[3] - vVertex[2],
			vVertex[0] - vVertex[3]
		};
		// é��3. �������͸� �̾Ƴ���!!! 
		D3DXVECTOR3 vNormal[4] =
		{
			{-vVertexDir[0].y, vVertexDir[0].x, 0.f },
			{ -vVertexDir[1].y, vVertexDir[1].x, 0.f },
			{ -vVertexDir[2].y, vVertexDir[2].x, 0.f },
			{ -vVertexDir[3].y, vVertexDir[3].x, 0.f },
		};

		//é�� 4. �� ���������� ���콺�� �ٶ󺸴� ���⺤�͸� ���ض�!!!! 
		D3DXVECTOR3 vMouseDir[4] =
		{
			// ���콺 - ������ ����° 
			vPos - vVertex[0],
			vPos - vVertex[1],
			vPos - vVertex[2],
			vPos - vVertex[3],
		};

		// ���� �� �� ���ߴ�!!! 

		for (int i = 0; i < 4; ++i)
		{
			if (0 < D3DXVec3Dot(&vMouseDir[i], &vNormal[i]))
				return false;
		}
		return true;
	}

public:
	// CGameObject��(��) ���� ��ӵ�
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




