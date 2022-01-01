#pragma once
#include "GameObject.h"
class CHPBar_Player :
	public CGameObject
{
public:
	explicit CHPBar_Player();
	virtual ~CHPBar_Player();
public:
	int FrameMove(float fSpeed = 1.f);
	//void Move();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

	void Set_TopHP(float damage) { HP.right -= damage; }
	void Set_TopHP_Plus(float damage) { HP.right += damage; }


	float Get_TopHP() {
		return HP.right
			;
	}

private:
	FRAME m_tFrame;
	CGameObject* pPlayer;
	RECT HP = { 0,0, 172, 9 };

};

