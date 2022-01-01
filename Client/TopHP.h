#pragma once
#include "GameObject.h"
class TopHP :
	public CGameObject
{
public:
	explicit TopHP();
	virtual ~TopHP();
public:
	int FrameMove(float fSpeed = 1.f);
	//void Move();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;


	void Set_TopHP(float damage) { 
		
		if (HP.right < 1)
		{
			HP.right = 0;
		}
		else
		HP.right -= damage; }


	float Get_TopHP() {
		return HP.right
			;
	}

private:
	FRAME m_tFrame;
	CGameObject* pTophpbar;

	float m_fHP = 196;
	vector<INFO*> m_vecInfo;
	RECT HP = { 0,0, 392, 9 };


};

