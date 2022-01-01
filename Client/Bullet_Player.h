#pragma once
#include "GameObject.h"

class CTerrain;
class Bullet_Player :
	public CGameObject
{
public:
	explicit Bullet_Player();
	virtual ~Bullet_Player();
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


	void Set_Dir() ;
	void Set_targetPos(D3DXVECTOR3 tPlayerPos, D3DXVECTOR3 tGoal) {
		m_tInfo.vPos = tPlayerPos;
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
};

