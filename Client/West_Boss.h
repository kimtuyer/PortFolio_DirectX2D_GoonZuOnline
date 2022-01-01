#pragma once
#include "GameObject.h"
class CTerrain;
class CGameObject_Manager;
class M_AStar_Manager;

class West_Boss :
	public CGameObject
{
public:
	explicit West_Boss();
	virtual ~West_Boss();
public:
	void FrameMove(float fSpeed = 1.f);
	void Move();

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject()			override;
	virtual int		Update_GameObject()			override;
	virtual void	Late_Update_GameObject()	override;
	virtual void	Render_GameObject()	override;
	virtual void	Release_GameObject()		override;

	void Change_Animation(INFO* pObject, D3DXVECTOR3 vPos);

	//이동할 목표지점 설정
	void Set_GoalTarget();

	//탐색할 적군 설정
	void Set_TargetEnemy()
	{
		m_listGameObject[PLAYER] = m_pGameObject_Manager->Get_ObjectList()[PLAYER];
		m_listGameObject[ChoSun] = m_pGameObject_Manager->Get_ObjectList()[ChoSun];

	}


	//사정거리 내 적 위치 탐색
	void Search_Enemy();
	HRESULT Shot(D3DXVECTOR3 &vPos, D3DXVECTOR3& GoalPos);




	HRESULT LoadData_Object(const wstring& wstrFilePath);

	void Set_ChoSunList()
	{
		m_listGameObject[ChoSun] = m_pGameObject_Manager->Get_ChoSun();
	}
	//void Set_List()
	//{
	//	m_listGameObject = m_pGameObject_Manager->Get_ObjectList();
	//}
private:
	vector<INFO*>m_vecMonster;
	CGameObject_Manager* m_pGameObject_Manager;
	list<CGameObject*> m_listGameObject[END];
	vector<M_AStar_Manager*> m_listRoute;
	float m_fFPSTime;
	float m_fUpdateFPSTime = 0;

	float m_fShotFPSTime;

	FRAME m_tFrame;
	float m_fSpeed;
	float m_fAttack_Range;
	D3DXVECTOR3 m_Dist;
	D3DXVECTOR3 m_ShortDist = { 0,0,0 };
	float m_fDist = 0;
	float m_fShortDist = 0;
	
	TCHAR m_szFPS[32];
	int m_GoalTarget = 0;


	CTerrain* pTerrain;
	CGameObject* pBullet;


};

