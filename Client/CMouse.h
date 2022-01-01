#pragma once
#include "GameObject.h"
class CTerrain;

class CMouse :
	public CGameObject
{


public:
	explicit CMouse();
	virtual ~CMouse();
public:
	void FrameMove(float fSpeed = 1.f);
	void Move();



	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;

	virtual int Update_GameObject() override;

	virtual void Late_Update_GameObject() override;

	virtual void Render_GameObject() override;

	virtual void Release_GameObject() override;

private:
	FRAME m_tFrame;
	CTerrain* pTerrain;
	D3DXVECTOR3 m_tMove{};


};

