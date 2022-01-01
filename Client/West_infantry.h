#pragma once
#include "GameObject.h"

class CTerrain;
class CGameObject_Manager;
class M_AStar_Manager;

class West_infantry :
	public CGameObject
{
public:
	explicit West_infantry();
	virtual ~West_infantry();
public:
	void FrameMove(float fSpeed = 1.f);
	void Move();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Ready_GameObject()			override;
	virtual int		Update_GameObject()			override;
	virtual void	Late_Update_GameObject()	override;
	virtual void	Render_GameObject()	override;
	virtual void	Release_GameObject()		override;

	void Change_Animation(INFO* pObject, D3DXVECTOR3 vPos);

	//�̵��� ��ǥ���� ����
	void Set_GoalTarget();

	//Ž���� ���� ����
	void Set_TargetEnemy()
	{
		m_listGameObject[PLAYER] = m_pGameObject_Manager->Get_ObjectList()[PLAYER];
		m_listGameObject[ChoSun] = m_pGameObject_Manager->Get_ObjectList()[ChoSun];

	}


	//�����Ÿ� �� �� ��ġ Ž��
	void Search_Enemy();




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

	FRAME m_tFrame;
	float m_fSpeed;
	float m_fAttack_Range;
	D3DXVECTOR3 m_Dist;
	D3DXVECTOR3 m_ShortDist = { 0,0,0 };
	float m_fDist = 0;
	float m_fShortDist = 0;

	CTerrain* pTerrain;
	CGameObject* pBullet;

	float m_fUpdateFPSTime = 0;

	float m_fShotFPSTime;
	TCHAR m_szFPS[32];
	int m_GoalTarget = 0;


};

