#include "stdafx.h"
#include "CMouse.h"
#include "CCamera.h"
#include "Terrain.h"


CMouse::CMouse() : m_tFrame({}),
 pTerrain(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

}


CMouse::~CMouse()
{
}

void CMouse::FrameMove(float fSpeed)
{
}

void CMouse::Move()
{
}

HRESULT CMouse::Ready_GameObject()
{
	m_tInfo.vPos = { 0, 0, 0.f };
	m_tMove= { 0, 0, 0.f };


	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	m_tInfo.vPos = { float(pt.x),float(pt.y),0 };

	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 13.f };
	//m_fSpeed = 100.f;
	StateKey = L"MouseStand";
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


	return S_OK;
}

int CMouse::Update_GameObject()
{
	//POINT pt{};
	//GetCursorPos(&pt);
	//ScreenToClient(g_hWND, &pt);
	ShowCursor(FALSE);

	//m_tInfo.vPos = { float(pt.x),float(pt.y),0 };
	//
	//m_tMove.x = pt.x - m_tInfo.vPos.x;
	//m_tMove.y= pt.y - m_tInfo.vPos.y;
	//
	//m_tInfo.vPos = {float(pt.x),float(pt.y),0} ;
	//

	//pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Player", StateKey, (DWORD)m_tFrame.fFrameStart);
	//pTerrain = dynamic_cast<CTerrain*>(CGameObject_Manager::Get_Instance()->Get_Terrain());
	//
	//D3DXVECTOR3 vPt = { float(pt.x),float(pt.y),0 };
	//D3DXVECTOR3 vMouse;
	//
	////플레이어가 월드좌표에서 카메라피벗 이상 이동시
	//if (m_tInfo.vPos.x >= CCamera::Get_Instance()->GetWorld().x*vPivot.x)
	//	vMouse = { float(pt.x) + vCamera.x + float(pTexInfo->tImageInfo.Width)*(0.45f)
	//   , float(pt.y) + vCamera.y, 0.f };
	//
	//
	//
	//else if (m_tInfo.vPos.y >= CCamera::Get_Instance()->GetWorld().y*vPivot.y)
	//	vMouse = { float(pt.x) + vCamera.x
	//   , float(pt.y) + vCamera.y + float(pTexInfo->tImageInfo.Height)*(0.5f), 0.f };
	//
	//
	//else
	//	vMouse = { float(pt.x) + vCamera.x
    //, float(pt.y) + vCamera.y, 0.f };
	//
	//
	return 0;
}

void CMouse::Late_Update_GameObject()
{
	FrameMove(1.0f);

}

void CMouse::Render_GameObject()
{
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Mouse", StateKey, (DWORD)m_tFrame.fFrameStart);

	fCenterX = pTexInfo->tImageInfo.Width >> 1;
	fCenterY = pTexInfo->tImageInfo.Height >> 1;

	D3DXVECTOR3 tPos = m_tInfo.vPos; //- m_tInfo.vSize;// * m_tPivot;

	tPos -= CCamera::Get_Instance()->GetPos();
	//else
	//	tPos -= CCamera::Get_Instance()->GetPos();


	m_ColliderInfo[0] = { tPos.x - 75 ,tPos.y - 50 };
	m_ColliderInfo[1] = { m_ColliderInfo[0].x + 150,tPos.y - 50 };
	m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 120 };
	m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
	m_ColliderInfo[4] = { tPos.x - 75 ,tPos.y - 50 };
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);

	D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);

	//D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_HORZ), m_tInfo.vPos.y + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_VERT), 0.f);
	matWorld = matScale * matTrans;
	

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	//CGraphic_Device::Get_Instance()->Get_Sprite()->End();
	////D3DXVECTOR2 vLine[5]{ {m_ColliderInfo.left,}, {200.f, 100.f},{ 200.f, 200.f },{ 100.f, 200.f },{ 100.f, 100.f }, };
	////CGraphic_Device::Get_Instance()->Get_Line()->SetWidth(20); 
	//
	//CGraphic_Device::Get_Instance()->Get_Line()->Draw(m_ColliderInfo, 5, D3DCOLOR_ARGB(255, 0, 0, 0));
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
}

void CMouse::Release_GameObject()
{
}
