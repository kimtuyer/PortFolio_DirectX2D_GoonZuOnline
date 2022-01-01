#pragma once
#include "GameObject.h"

class CTerrain;


class FireArrowSkill :
	public CGameObject
{
public:
	explicit FireArrowSkill();
	virtual ~FireArrowSkill();
public:
	int FrameMove(float fSpeed = 1.f);
	void Move();

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject()			override;
	virtual int		Update_GameObject()			override;
	virtual void	Late_Update_GameObject()	override;
	virtual void	Render_GameObject()	override;
	virtual void	Release_GameObject()		override;


	void Set_Dir();
	void Set_target(D3DXVECTOR3 tGoal)
	{
		m_tInfo.vPos = tGoal;

	}
	void Set_targetPos(D3DXVECTOR3 tPlayerPos, D3DXVECTOR3 tGoal) {
		m_tInfo.vPos = tPlayerPos;
		m_vGoalPos = tGoal;

	}
	void Set_Life(int a) { m_life = a; }

	bool Get_FrameEnd() { return m_bFrameEnd; }


	void Set_Dir(int i) { m_eDir = i; }

	//void Shot()
private:
	int m_life = 0;
	D3DXVECTOR3 m_vGoalPos{};
	FRAME m_tFrame;
	float m_fSpeed;
	bool m_bFrameEnd = false;

	CTerrain* pTerrain;
	int m_eDir = 0;
};

