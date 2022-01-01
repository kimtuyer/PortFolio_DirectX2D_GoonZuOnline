#pragma once
class CAStar_Manager
{
	DECLARE_SINGLETON(CAStar_Manager)
private:
	CAStar_Manager();
	~CAStar_Manager();
public:
	list<TILE*>& Get_BestList() { return m_BestList; }
public:
	void StartAStar_Manager(const D3DXVECTOR3& vStartPos, const D3DXVECTOR3& vGoalPos);

private:
	bool Check_OpenList(int iIndex);
	bool Check_CloseList(int iIndex);
	bool PathFinding_AStar_Manager(int iStartIndex, int iGoalIndex);
	void Make_Route(int iGoalIndex);
	int Get_TileIndex(const D3DXVECTOR3& vPos);
	bool IsPicking(const D3DXVECTOR3& vPos, const int iIndex);
private:
	list<int> m_OpenList;
	list<int> m_CloseList;
	list<TILE*> m_BestList;
	int m_iStartIndex;
};

