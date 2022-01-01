#pragma once
#include "GameObject.h"
class JangGumIName :
	public CGameObject
{
public:
	explicit JangGumIName();
	virtual ~JangGumIName();
public:
	int FrameMove(float fSpeed = 1.f);
	//void Move();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

private:
	FRAME m_tFrame;
	CGameObject* pJangGumi;
};

