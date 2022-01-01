#pragma once
#include "GameObject.h"
class CQuest :
	public CGameObject
{
public:
	explicit CQuest();
	virtual ~CQuest();
public:
	int FrameMove(float fSpeed = 1.f);
	//void Move();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;
	
	void QuestChange() {

		if (L"Quest1" == StateKey  || L"Quest3" == StateKey)
		{

			m_ColliderInfo[0] = { m_tInfo.vPos.x - 373  ,m_tInfo.vPos.y - 111 };
			m_ColliderInfo[1] = { m_ColliderInfo[0].x + 746,m_tInfo.vPos.y - 111 };
			m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 223 };
			m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
			m_ColliderInfo[4] = { m_tInfo.vPos.x - 373 ,m_tInfo.vPos.y - 111 };
		}
		else if (L"Quest2" == StateKey || L"Quest4" == StateKey)
		{
			m_ColliderInfo[0] = { m_tInfo.vPos.x - 283  ,m_tInfo.vPos.y - 109 };
			m_ColliderInfo[1] = { m_ColliderInfo[0].x + 567,m_tInfo.vPos.y - 109 };
			m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 218 };
			m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
			m_ColliderInfo[4] = { m_tInfo.vPos.x - 283 ,m_tInfo.vPos.y - 109 };
		}

	}

private:
	FRAME m_tFrame;
	int m_quest = 0;
};

