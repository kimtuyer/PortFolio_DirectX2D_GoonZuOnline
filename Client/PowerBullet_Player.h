#pragma once
#include "GameObject.h"
class CSkill1_Player;
class CTerrain;

class PowerBullet_Player :
	public CGameObject
{
public:
	explicit PowerBullet_Player();
	virtual ~PowerBullet_Player();
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


	void Set_Dir();
	void Set_targetPos(D3DXVECTOR3 tPlayerPos, D3DXVECTOR3 tGoal) {
		//D3DXVECTOR3 startpos{50,50,0};
		m_tInfo.vPos = tPlayerPos;
		//m_tInfo.vPos += startpos;
		m_vGoalPos = tGoal;

	}
	void Set_Life(int a) { m_life = a; }
	//void Shot()
private:
	int m_life = 0;
	D3DXVECTOR3 m_vGoalPos{};
	FRAME m_tFrame;
	float m_fSpeed;


	CTerrain* pTerrain;
	CSkill1_Player* pSkill1;

};

