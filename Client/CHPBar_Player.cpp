#include "stdafx.h"
#include "CHPBar_Player.h"
#include "GameObject_Manager.h"
#include "CCamera.h"

CHPBar_Player::CHPBar_Player() : m_tFrame({})
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

}

CHPBar_Player::~CHPBar_Player()
{
	Release_GameObject();

}

int CHPBar_Player::FrameMove(float fSpeed)
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

HRESULT CHPBar_Player::Ready_GameObject()
{
	pPlayer = CGameObject_Manager::Get_Instance()->Get_Player();

	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vPos = { 27,7,0 };
	m_tFrame = { 0.f, 1.f };
	//m_fSpeed = 300.f;
	StateKey = L"HPBar";

	//pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	//Set_Dir();
	return S_OK;
}

int CHPBar_Player::Update_GameObject()
{
	FrameMove(0.5f);
	return 0;
}

void CHPBar_Player::Late_Update_GameObject()
{
}

void CHPBar_Player::Render_GameObject()
{
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"HPBar", StateKey, (DWORD)m_tFrame.fFrameStart);

	
		fCenterX = pTexInfo->tImageInfo.Width >> 1;
		fCenterY = pTexInfo->tImageInfo.Height >> 1;

		D3DXVECTOR3 tPos = m_tInfo.vPos; 
		
		D3DXMatrixScaling(&matScale, 1, m_tInfo.vSize.y, 0.f);

		D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);

		matWorld = matScale * matTrans;
		//&D3DXVECTOR3(fCenterX, fCenterY, 0.f)
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &HP, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		//CGraphic_Device::Get_Instance()->Get_Sprite()->End();
		////D3DXVECTOR2 vLine[5]{ {m_ColliderInfo.left,}, {200.f, 100.f},{ 200.f, 200.f },{ 100.f, 200.f },{ 100.f, 100.f }, };
		////CGraphic_Device::Get_Instance()->Get_Line()->SetWidth(20); 
		//
		//CGraphic_Device::Get_Instance()->Get_Line()->Draw(m_ColliderInfo, 5, D3DCOLOR_ARGB(255, 0, 0, 0));
		//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

}

void CHPBar_Player::Release_GameObject()
{
}
