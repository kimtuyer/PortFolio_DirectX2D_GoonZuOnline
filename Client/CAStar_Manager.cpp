#include "stdafx.h"
#include "CAStar_Manager.h"
#include "Terrain.h"

IMPLEMENT_SINGLETON(CAStar_Manager)

CAStar_Manager::CAStar_Manager()
{
}
CAStar_Manager::~CAStar_Manager()
{
}

void CAStar_Manager::StartAStar_Manager(const D3DXVECTOR3 & vStartPos, const D3DXVECTOR3 & vGoalPos)
{
	
	m_OpenList.clear();
	m_CloseList.clear();

	m_BestList.clear();

	m_iStartIndex = Get_TileIndex(vStartPos);
	int iGoalIndex = Get_TileIndex(vGoalPos);

	if (-1 == m_iStartIndex || -1 == iGoalIndex)
		return;
	if (m_iStartIndex == iGoalIndex)
		return;

	CTerrain*  pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	auto& vecTile = pTerrain->Get_VecTile();

	if (0 != vecTile[iGoalIndex]->byOption)
		return;

	if (PathFinding_AStar_Manager(m_iStartIndex, iGoalIndex))
		Make_Route(iGoalIndex);
}

bool CAStar_Manager::Check_OpenList(int iIndex)
{
	auto& iter_find = find(m_OpenList.begin(), m_OpenList.end(), iIndex);
	if (iter_find == m_OpenList.end())
		return false;

	return true;
}

bool CAStar_Manager::Check_CloseList(int iIndex)
{
	auto& iter_find = find(m_CloseList.begin(), m_CloseList.end(), iIndex);
	if (iter_find == m_CloseList.end())
		return false;

	return true;
}

bool CAStar_Manager::PathFinding_AStar_Manager(int iStartIndex, int iGoalIndex)
{
	if (!m_OpenList.empty())
		m_OpenList.pop_front();

	m_CloseList.emplace_back(iStartIndex);
	CTerrain*  pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	auto& vecTile = pTerrain->Get_VecTile();
	auto& vecGraph = pTerrain->Get_Graph();
	for (auto& pTile : vecGraph[iStartIndex])
	{
		if (iGoalIndex == pTile->iIndex)
		{
			pTile->iParentIndex = iStartIndex;
			return true;
		}

		if (Check_CloseList(pTile->iIndex) || Check_OpenList(pTile->iIndex))
			continue;
		pTile->iParentIndex = iStartIndex;
		m_OpenList.emplace_back(pTile->iIndex);
	}
	// �̰�쿡 �ɸ���?? �׷� ��� Ÿ���� ���δ� ��ȸ�ߴٶ�� ��. 
	if (m_OpenList.empty())
		return false;

	//greater<int>();
	m_OpenList.sort([&](int iPreIndex, int iNextIndex)
	{
		D3DXVECTOR3 vPreToStart = vecTile[m_iStartIndex]->vPos - vecTile[iPreIndex]->vPos;
		D3DXVECTOR3 vPreToGoal = vecTile[iGoalIndex]->vPos - vecTile[iPreIndex]->vPos;
		float fDist1 = D3DXVec3Length(&vPreToGoal) + D3DXVec3Length(&vPreToStart);

		D3DXVECTOR3 vNextToStart = vecTile[m_iStartIndex]->vPos - vecTile[iNextIndex]->vPos;
		D3DXVECTOR3 vNextToGoal = vecTile[iGoalIndex]->vPos - vecTile[iNextIndex]->vPos;
		float fDist2 = D3DXVec3Length(&vNextToStart) + D3DXVec3Length(&vNextToGoal);

		return fDist1 < fDist2;
	});

	return PathFinding_AStar_Manager(m_OpenList.front(), iGoalIndex);
}

void CAStar_Manager::Make_Route(int iGoalIndex)
{
	CTerrain*  pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	auto& vecTile = pTerrain->Get_VecTile();
	auto& vecGraph = pTerrain->Get_Graph();

	int iParentIndex = vecTile[iGoalIndex]->iParentIndex;
	m_BestList.emplace_back(vecTile[iGoalIndex]);
	while (true)
	{
		if (iParentIndex == m_iStartIndex)
			break;

		m_BestList.emplace_front(vecTile[iParentIndex]);
		iParentIndex = vecTile[iParentIndex]->iParentIndex;
	}

}

int CAStar_Manager::Get_TileIndex(const D3DXVECTOR3 & vPos)
{
	CTerrain*  pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	auto& vecTile = pTerrain->Get_VecTile();
	int iSize = vecTile.size();
	for (int i = 0; i < iSize; ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}

	return -1;
}

bool CAStar_Manager::IsPicking(const D3DXVECTOR3 & vPos, const int iIndex)
{
	CTerrain*  pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	auto& vecTile = pTerrain->Get_VecTile();
	D3DXVECTOR3 vVertex[4] =
	{
		{ vecTile[iIndex]->vPos.x ,vecTile[iIndex]->vPos.y + (TILECY >> 1), 0.f },
		{ vecTile[iIndex]->vPos.x + (TILECX >> 1),vecTile[iIndex]->vPos.y , 0.f },
		{ vecTile[iIndex]->vPos.x ,vecTile[iIndex]->vPos.y - (TILECY >> 1), 0.f },
		{ vecTile[iIndex]->vPos.x - (TILECX >> 1) ,vecTile[iIndex]->vPos.y , 0.f }
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
		{ -vVertexDir[0].y, vVertexDir[0].x, 0.f },
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
