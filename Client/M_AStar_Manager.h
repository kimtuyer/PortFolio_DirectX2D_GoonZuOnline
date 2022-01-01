#pragma once
class M_AStar_Manager
{
	//DECLARE_SINGLETON(M_AStar_Manager)
public:
	M_AStar_Manager(D3DXVECTOR3 vStartPos,D3DXVECTOR3 vGoalPos);
	~M_AStar_Manager();
public:
	list<TILE*>& Get_BestList() { return m_BestList; }
public:
	void StartAStar_Manager(const D3DXVECTOR3& vStartPos, const D3DXVECTOR3& vGoalPos);

private:
	bool Check_OpenList(int iIndex);
	bool Check_CloseList(int iIndex);
	bool PathFinding_AStar_Manager(D3DXVECTOR3 vStartPos,int iStartIndex, D3DXVECTOR3 vGoalPos,int iGoalIndex);
	void Make_Route(int iGoalIndex);
	int Get_TileIndex(const D3DXVECTOR3& vPos);
	bool IsPicking(const D3DXVECTOR3& vPos, const int iIndex);
private:
	list<int> m_OpenList;
	list<int> m_CloseList;
	list<TILE*> m_BestList;
	int m_iStartIndex;
};

