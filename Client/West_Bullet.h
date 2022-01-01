#pragma once
#include "GameObject.h"

class CTerrain;
class West_Bullet :
	public CGameObject
{
public:
	explicit West_Bullet();
	virtual ~West_Bullet();
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


	void Set_targetPos(D3DXVECTOR3 tPlayerPos, D3DXVECTOR3 tGoal) {
		m_tInfo.vPos = tPlayerPos;
		m_vGoalPos = tGoal;

	}
	void Set_Life(int a) { m_life = a; }
	int Get_Life() { return m_life; }

	float Get_TargetDist() {
		return m_fTargetDist
			;
	}
	//void Shot()  
private:
	int m_life = 0;
	D3DXVECTOR3 m_vGoalPos{};
	float m_fTargetDist = 0;

	FRAME m_tFrame;
	float m_fSpeed;
	CTerrain* pTerrain;
};

