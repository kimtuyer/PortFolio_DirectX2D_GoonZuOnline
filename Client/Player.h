#pragma once
#include "GameObject.h"
//class Bullet_Player;
class CTerrain;
class CPlayer final:
	public CGameObject
{
public:
	explicit CPlayer();
	virtual ~CPlayer();
public:
	void FrameMove(float fSpeed = 1.f ); 
	void MovePlayer();

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject()			override;
	virtual int		Update_GameObject()			override;
	virtual void	Late_Update_GameObject()	override;
	virtual void	Render_GameObject()	override;
	virtual void	Release_GameObject()		override;

	//일반 평타 공격
	HRESULT Shot(D3DXVECTOR3&);

	//Dash 공격
	HRESULT DashShot(D3DXVECTOR3&,CGameObject*,int ArrowNumber);

private:
	CGameObject* pBullet;
	CGameObject* pBullet2;
	CGameObject* pBullet3;

	CGameObject* pSkill;

	CGameObject* pMouse;

	CGameObject_Manager* m_pGameObject_Manager;
	D3DXVECTOR3 vMouse{};
	int m_AttackState=0;
	FRAME m_tFrame; 
	float m_fSpeed;
	float m_fShotFPSTime=0;
	float m_fBulletFPSTime = 0;

	CTerrain* pTerrain;
	int m_ArrowNumber = 0;

	//int m_iAttackState = 0;


};

