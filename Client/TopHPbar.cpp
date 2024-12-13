#include "stdafx.h"
#include "TopHPbar.h"
#include "CCamera.h"
#include "GameObject_Manager.h"
#include "CMapObject.h"
TopHPbar::TopHPbar() : m_tFrame({})
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	pTop = CGameObject_Manager::Get_Instance()->Get_listTop().front();


}

TopHPbar::~TopHPbar()
{
	Release_GameObject();

}

int TopHPbar::FrameMove(float fSpeed)
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

HRESULT TopHPbar::Ready_GameObject()
{
	m_tInfo.vPos = static_cast<CMapObject*>(pTop)->Get_VecTile().front()->vPos;
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	//m_tInfo.vPos = { 100,30,0 };
	m_tFrame = { 0.f, 1.f };
	//m_fSpeed = 300.f;
	StateKey = L"HanyangHP";
	D3DXMatrixScaling(&matScale, 0.5, m_tInfo.vSize.y, 0.f);

	//pTerrain = static_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	//Set_Dir();
	return S_OK;
}

int TopHPbar::Update_GameObject()
{
	FrameMove(0.5f);

	return 0;
}

void TopHPbar::Late_Update_GameObject()
{
}

void TopHPbar::Render_GameObject()
{
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"TopHPBar", StateKey, (DWORD)m_tFrame.fFrameStart);
	fCenterX = pTexInfo->tImageInfo.Width >> 1;
	fCenterY = pTexInfo->tImageInfo.Height >> 1;

	D3DXVECTOR3 tPos;
	tPos = m_tInfo.vPos;
	tPos.y = tPos.y - 150;

	tPos -= CCamera::Get_Instance()->GetPos();

	D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);
	matWorld = matScale * matTrans;
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void TopHPbar::Release_GameObject()
{
}
