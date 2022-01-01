#include "stdafx.h"
#include "NPC_Leewonik.h"
#include "Terrain.h"
#include "CCamera.h"
#include "CMouse.h"
#include "M_AStar_Manager.h"
#include "CAStar_Manager.h"
#include "GameObject_Manager.h"
#include "Player.h"
#include "CMapObject.h"
#include "Frame_Manager.h"
#include "Time_Manager.h"
NPC_Leewonik::NPC_Leewonik() : m_tFrame({}), m_fFPSTime(0.f), m_fShotFPSTime(0), m_szFPS(L"")
,
m_fSpeed(0), pTerrain(nullptr), pPlayer(nullptr), m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_fAttack_Range = float(TILECX * 2);
	m_fShortDist = m_fAttack_Range;



}

NPC_Leewonik::~NPC_Leewonik()
{
	Release_GameObject();

}
HRESULT NPC_Leewonik::Ready_GameObject()
{
	m_tInfo.vPos = { 702,416,0 };
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tFrame = { 0.f, 52.f };
	m_fSpeed = 500.f;
	StateKey = L"Leewonik";
	m_tInfo.ID = ID::ChoSun;
	m_Damage = 10;

	vMouse = { 0, 0, 0.f };


	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);


	m_listGameObject[PLAYER] = m_pGameObject_Manager->Get_ObjectList()[PLAYER];
	PlayerPos = m_listGameObject[PLAYER].front()->Get_Info().vPos;
	PlayerPos = { PlayerPos.x + TILECX * 2, PlayerPos.y,0 };

	//m_pM_AStar = new M_AStar_Manager(m_vecMonster[i]->vPos, tPos);

	m_listRoute.emplace_back(new M_AStar_Manager(m_tInfo.vPos, PlayerPos));
	//M_AStar_Manager::Get_Instance()->StartAStar_Manager(m_vecMonster[i]->vPos, tPos);
	m_tInfo.iAttack_Target = ID::END;




	return S_OK;
}

void NPC_Leewonik::FrameMove(float fSpeed)
{
	m_tFrame.fFrameStart += m_tFrame.fFrameEnd * CTime_Manager::Get_Instance()->Get_DeltaTime() * fSpeed;
	if (m_tFrame.fFrameEnd < m_tFrame.fFrameStart)
		m_tFrame.fFrameStart = 0.f;
}

void NPC_Leewonik::Move()
{
}


int NPC_Leewonik::Update_GameObject()
{
	return 0;
}

void NPC_Leewonik::Late_Update_GameObject()
{
}

void NPC_Leewonik::Render_GameObject()
{
	pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Leewonik", StateKey, (DWORD)m_tFrame.fFrameStart);
	if (nullptr == pTexInfo)
		return;
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	D3DXVECTOR3 tPos = m_tInfo.vPos - m_tInfo.vSize;// * m_tPivot;

	tPos -= CCamera::Get_Instance()->GetPos();



	m_ColliderInfo[0] = { tPos.x - 52 ,tPos.y - 50 };
	m_ColliderInfo[1] = { m_ColliderInfo[0].x + 104,tPos.y - 50 };
	m_ColliderInfo[2] = { m_ColliderInfo[1].x,m_ColliderInfo[1].y + 100 };
	m_ColliderInfo[3] = { m_ColliderInfo[0].x,m_ColliderInfo[2].y };
	m_ColliderInfo[4] = { tPos.x - 52 ,tPos.y - 50 };


	D3DXMatrixTranslation(&matTrans, tPos.x, tPos.y, 0.f);

	//D3DXMatrixScaling(&matScale, m_vecMonster[i]->vSize.x, m_vecMonster[i]->vSize.y, 0.f);
	//D3DXMatrixTranslation(&matTrans, m_vecMap[i]->vPos.x + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_HORZ), m_vecMap[i]->vPos.y + CScroll_Manager::Get_Instance()->Get_Scroll(CScroll_Manager::eSB_VERT), 0.f);
	matWorld = matScale * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	//CGraphic_Device::Get_Instance()->Get_Sprite()->End();
	//
	//CGraphic_Device::Get_Instance()->Get_Line()->Draw(m_ColliderInfo, 5, D3DCOLOR_ARGB(255, 0, 0, 0));
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
}

void NPC_Leewonik::Release_GameObject()
{
}

void NPC_Leewonik::Change_Animation(INFO * pObject, D3DXVECTOR3 vPos)
{
}

void NPC_Leewonik::Set_GoalTarget()
{
}

HRESULT NPC_Leewonik::Shot(D3DXVECTOR3 & vPos, D3DXVECTOR3 & GoalPos)
{
	return E_NOTIMPL;
}

void NPC_Leewonik::Search_Enemy()
{
}

HRESULT NPC_Leewonik::LoadData_Object(const wstring & wstrFilePath)
{
	return E_NOTIMPL;
}
