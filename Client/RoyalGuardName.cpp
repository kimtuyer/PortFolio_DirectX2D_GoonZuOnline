#include "stdafx.h"
#include "RoyalGuardName.h"
#include "CCamera.h"
#include "GameObject_Manager.h"
RoyalGuardName::RoyalGuardName() : m_tFrame({})
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	pRoyalguard = CGameObject_Manager::Get_Instance()->Get_NPC().front();


}

RoyalGuardName::~RoyalGuardName()
{
	Release_GameObject();

}

int RoyalGuardName::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
	{
		m_tFrame.fFrameStart = 0.f;
		//m_bFrameEnd = true;
		return OBJ_DEAD;
	}
	else
		return 0;
}

HRESULT RoyalGuardName::Ready_GameObject()
{
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	//m_tInfo.vPos = { 100,30,0 };
	m_tFrame = { 0.f, 1.f };
	//m_fSpeed = 300.f;
	StateKey = L"RoyalGuardName";
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	//pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	//Set_Dir();
	return S_OK;
}

int RoyalGuardName::Update_GameObject()
{
	FrameMove(0.5f);

	return 0;
}

void RoyalGuardName::Late_Update_GameObject()
{
}

void RoyalGuardName::Render_GameObject()
{
	pRoyalguard = CGameObject_Manager::Get_Instance()->Get_NPC().front();
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"RoyalGuardName", StateKey, (DWORD)m_tFrame.fFrameStart);
	fCenterX = pTexInfo->tImageInfo.Width >> 1;
	fCenterY = pTexInfo->tImageInfo.Height >> 1;

	D3DXVECTOR3 tPos;
	tPos = pRoyalguard->Get_Info().vPos;
	tPos.y = tPos.y - 40;

	tPos -= CCamera::Get_Instance()->GetPos();

	D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);
	matWorld = matScale * matTrans;
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void RoyalGuardName::Release_GameObject()
{
}
