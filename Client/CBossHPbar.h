#pragma once
#include "GameObject.h"
class CBossHPbar :
	public CGameObject
{
public:
	explicit CBossHPbar();
	virtual ~CBossHPbar();
public:
	int FrameMove(float fSpeed = 1.f);
	//void Move();

	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

private:
	FRAME m_tFrame;
	CGameObject* pTop;
};

