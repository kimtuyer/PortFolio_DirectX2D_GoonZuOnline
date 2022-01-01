#include "stdafx.h"
#include "CMPBar_Player.h"

CMPBar_Player::CMPBar_Player() : m_tFrame({})
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

}

CMPBar_Player::~CMPBar_Player()
{
	Release_GameObject();

}

int CMPBar_Player::FrameMove(float fSpeed)
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

HRESULT CMPBar_Player::Ready_GameObject()
{
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vPos = { 27,19,0 };
	m_tFrame = { 0.f, 1.f };
	//m_fSpeed = 300.f;
	StateKey = L"MPBar";

	//pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	//Set_Dir();
	return S_OK;
}

int CMPBar_Player::Update_GameObject()
{
	FrameMove(0.5f);

	return 0;
}

void CMPBar_Player::Late_Update_GameObject()
{
}

void CMPBar_Player::Render_GameObject()
{
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"MPBar", StateKey, (DWORD)m_tFrame.fFrameStart);


	fCenterX = pTexInfo->tImageInfo.Width >> 1;
	fCenterY = pTexInfo->tImageInfo.Height >> 1;

	D3DXVECTOR3 tPos = m_tInfo.vPos;

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x * 86, m_tInfo.vSize.y, 0.f);

	D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);

	matWorld = matScale * matTrans;
	//&D3DXVECTOR3(fCenterX, fCenterY, 0.f)
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	//CGraphic_Device::Get_Instance()->Get_Sprite()->End();
	////D3DXVECTOR2 vLine[5]{ {m_ColliderInfo.left,}, {200.f, 100.f},{ 200.f, 200.f },{ 100.f, 200.f },{ 100.f, 100.f }, };
	////CGraphic_Device::Get_Instance()->Get_Line()->SetWidth(20); 
	//
	//CGraphic_Device::Get_Instance()->Get_Line()->Draw(m_ColliderInfo, 5, D3DCOLOR_ARGB(255, 0, 0, 0));
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
}

void CMPBar_Player::Release_GameObject()
{
}
