#include "stdafx.h"
#include "CLoading.h"
#include "Scene_Manager.h"

int CLoading::rgb[4]{ 255, 0, 0, 0 };


CLoading::CLoading()
{
}

CLoading::~CLoading()
{
}

unsigned  CLoading::ImageLoading(LPVOID pVoid)
{
	CLoading* pLoading = (CLoading*)pVoid;
	EnterCriticalSection(&pLoading->m_Critical_Section);
	//TileTexture


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Terrain/TILEMAP/TILE0%d.png", L"Terrain", rgb, L"Tile", 4)))
		return E_FAIL;

	



	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/Tile/Town.png", L"StartMap", rgb, L"Map", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/Tile/Sea3.png", L"SeaMap1", rgb, L"Sea1", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/Tile/Sea4.png", L"SeaMap2", rgb, L"Sea2", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/Tile/0.bmp", L"DAEMA1", rgb, L"DAEMA1", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/Tile/1.bmp", L"DAEMA2", rgb, L"DAEMA2", 1)))
		return E_FAIL;






	//const TEXINFO* pTexInfo2 = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"SeaMap1", L"Sea1");

	//공격 맞은 이펙트

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CriticalEffect/%d.bmp", L"CriticalEffect", rgb, L"CriticalEffect", 11)))
		return E_FAIL;

	//GageBar
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/GageBar/000.bmp", L"GageBar", rgb, L"GageBar", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/GageBar/hpmp/0011.bmp", L"HPBar", rgb, L"HPBar", 1)))
		return E_FAIL;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/GageBar/hpmp/005.bmp", L"MPBar", rgb, L"MPBar", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/GageBar/exp/001.bmp", L"ExpBar", rgb, L"ExpBar", 1)))
		return E_FAIL;








	//소환영웅 간판
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Name/SummonName.png", L"SummonName", rgb, L"SummonName", 1)))
		return E_FAIL;


	//UI창, 소지품,상태,퀘스트정보 버튼 모아둔 창
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/UI/StatusWindow.png", L"StatusWindow", rgb, L"StatusWindow", 1)))
		return E_FAIL;

	rgb[0] = 255;
	rgb[1] = 0;
	rgb[2] = 0;
	rgb[3] = 0;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Object/gate_%d.bmp", L"MapObject", rgb, L"Gate", 74)))
		return E_FAIL;

	


	//탑 HP gage bar
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Top/Hanyang.png", L"TopHPBar", rgb, L"HanyangHP", 1)))
		return E_FAIL;

	//탑 HP gage bar
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Top/Kwanghwa.png", L"TopHPBar", rgb, L"KwanghwaHP", 1)))
		return E_FAIL;

	//탑 HP gage bar
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Top/Namhan.png", L"TopHPBar", rgb, L"NamhanHP", 1)))
		return E_FAIL;

	////탑 HP gage bar
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
	//	L"../Texture/Stage/Top/000.bmp", L"TopHPBar", rgb, L"BossHP", 1)))
	//	return E_FAIL;



	//탑 HP gage bar
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/GageBar/hpmp/0051.bmp", L"TopHP", rgb, L"TopHP", 1)))
		return E_FAIL;








	/////////////////////////////////////////////////////////////////////////////////////////////////
	//Player-Attack Texture 
	rgb[0] = 255;
	rgb[1] = 247;
	rgb[2] = 0;
	rgb[3] = 255;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/Monster/BossGage/0001.bmp", L"BossHpBar", rgb, L"BossHpBar", 1)))
		return E_FAIL;








	//소환영웅 UI 패널 백그라운드
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/UI/Summon_pannel/background/000.bmp", L"Summon_Pannel", rgb, L"Summon_Pannel", 1)))
		return E_FAIL;



	//숫자 넘버
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/0.bmp", L"DmgNumber", rgb, L"0", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/1.bmp", L"DmgNumber", rgb, L"1", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/2.bmp", L"DmgNumber", rgb, L"2", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/3.bmp", L"DmgNumber", rgb, L"3", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/4.bmp", L"DmgNumber", rgb, L"4", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/5.bmp", L"DmgNumber", rgb, L"5", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/6.bmp", L"DmgNumber", rgb, L"6", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/7.bmp", L"DmgNumber", rgb, L"7", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/8.bmp", L"DmgNumber", rgb, L"8", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/9.bmp", L"DmgNumber", rgb, L"9", 1)))
		return E_FAIL;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/10.bmp", L"DmgNumber", rgb, L"10", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/20.bmp", L"DmgNumber", rgb, L"20", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/30.bmp", L"DmgNumber", rgb, L"30", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/40.bmp", L"DmgNumber", rgb, L"40", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/50.bmp", L"DmgNumber", rgb, L"50", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/DmgNumber/60.bmp", L"DmgNumber", rgb, L"60", 1)))
		return E_FAIL;











	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/0.bmp", L"CdmgNumber", rgb, L"0", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/1.bmp", L"CdmgNumber", rgb, L"1", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/2.bmp", L"CdmgNumber", rgb, L"2", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/3.bmp", L"CdmgNumber", rgb, L"3", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/4.bmp", L"CdmgNumber", rgb, L"4", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/5.bmp", L"CdmgNumber", rgb, L"5", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/6.bmp", L"CdmgNumber", rgb, L"6", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/7.bmp", L"CdmgNumber", rgb, L"7", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/8.bmp", L"CdmgNumber", rgb, L"8", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/9.bmp", L"CdmgNumber", rgb, L"9", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/100.bmp", L"CdmgNumber", rgb, L"100", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/200.bmp", L"CdmgNumber", rgb, L"200", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CdmgNumber/300.bmp", L"CdmgNumber", rgb, L"300", 1)))
		return E_FAIL;



	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CDmgNumber1/100.bmp", L"CdmgNumber2", rgb, L"100", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CDmgNumber1/120.bmp", L"CdmgNumber2", rgb, L"120", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/CDmgNumber1/130.bmp", L"CdmgNumber2", rgb, L"130", 1)))
		return E_FAIL;






















	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Stand/%d.bmp", L"Player", rgb, L"Stand", 20)))
		return E_FAIL;

	//WALK
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Walk/%d.bmp", L"Player", rgb, L"Walk", 8)))
		return E_FAIL;
	//LD
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Walk/LD/%d.bmp", L"Player", rgb, L"WalkLD", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Walk/LU/%d.bmp", L"Player", rgb, L"WalkLU", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Walk/Left/%d.bmp", L"Player", rgb, L"WalkLeft", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Walk/Up/%d.bmp", L"Player", rgb, L"WalkUp", 8)))
		return E_FAIL;


	//Attack
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Attack/%d.bmp", L"Player", rgb, L"Attack", 10)))
		return E_FAIL;
	//LD
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Attack/LD/%d.bmp", L"Player", rgb, L"AttackLD", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Attack/LU/%d.bmp", L"Player", rgb, L"AttackLU", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Attack/Left/%d.bmp", L"Player", rgb, L"AttackLeft", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Attack/Up/%d.bmp", L"Player", rgb, L"AttackUp", 10)))
		return E_FAIL;


	//소환영웅

	//김시민
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Stand/%d.bmp", L"Kimsimin", rgb, L"Stand", 8)))
		return E_FAIL;

	//WALK
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Walk/%d.bmp", L"Kimsimin", rgb, L"Walk", 8)))
		return E_FAIL;
	//LD
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Walk/LD/%d.bmp", L"Kimsimin", rgb, L"WalkLD", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Walk/LU/%d.bmp", L"Kimsimin", rgb, L"WalkLU", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Walk/Left/%d.bmp", L"Kimsimin", rgb, L"WalkLeft", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Walk/Up/%d.bmp", L"Kimsimin", rgb, L"WalkUp", 8)))
		return E_FAIL;


	//Attack
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Attack/%d.bmp", L"Kimsimin", rgb, L"Attack", 12)))
		return E_FAIL;
	//LD
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Attack/LD/%d.bmp", L"Kimsimin", rgb, L"AttackLD", 12)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Attack/LU/%d.bmp", L"Kimsimin", rgb, L"AttackLU", 12)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Attack/Left/%d.bmp", L"Kimsimin", rgb, L"AttackLeft", 12)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Attack/Up/%d.bmp", L"Kimsimin", rgb, L"AttackUp", 12)))
		return E_FAIL;


	//Dash
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Dash/%d.bmp", L"Kimsimin", rgb, L"Dash", 12)))
		return E_FAIL;
	//LD
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Dash/LD/%d.bmp", L"Kimsimin", rgb, L"DashLD", 12)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Dash/LU/%d.bmp", L"Kimsimin", rgb, L"DashLU", 12)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Dash/Left/%d.bmp", L"Kimsimin", rgb, L"DashLeft", 12)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Kimsimin/Dash/Up/%d.bmp", L"Kimsimin", rgb, L"DashUp", 12)))
		return E_FAIL;





	//장금이
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Stand/%d.bmp", L"Janggum", rgb, L"Stand", 8)))
		return E_FAIL;

	//WALK
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Walk/%d.bmp", L"Janggum", rgb, L"Walk", 8)))
		return E_FAIL;
	//LD
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Walk/LD/%d.bmp", L"Janggum", rgb, L"WalkLD", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Walk/LU/%d.bmp", L"Janggum", rgb, L"WalkLU", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Walk/Left/%d.bmp", L"Janggum", rgb, L"WalkLeft", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Walk/Up/%d.bmp", L"Janggum", rgb, L"WalkUp", 8)))
		return E_FAIL;


	//Attack
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Heal/Down/%d.bmp", L"Janggum", rgb, L"Attack", 17)))
		return E_FAIL;
	//LD
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Heal/LD/%d.bmp", L"Janggum", rgb, L"AttackLD", 17)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Heal/LU/%d.bmp", L"Janggum", rgb, L"AttackLU", 17)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Heal/Left/%d.bmp", L"Janggum", rgb, L"AttackLeft", 17)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Heal/Up/%d.bmp", L"Janggum", rgb, L"AttackUp", 17)))
		return E_FAIL;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/Skill/%d.bmp", L"Janggum", rgb, L"HEAL", 32)))
		return E_FAIL;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Summon/Janggum/8/%d.bmp", L"Janggum", rgb, L"HEAL2", 21)))
		return E_FAIL;



	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/HealNumber/100.bmp", L"CdmgNumber2", rgb, L"HealNumber", 1)))
		return E_FAIL;








	//NPC
	//내금위종사관
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Name/Royalguard.png", L"RoyalGuardName", rgb, L"RoyalGuardName", 1)))
		return E_FAIL;



	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/NPC/RoyalGuard/Stand/%d.bmp", L"RoyalGuard", rgb, L"Stand", 8)))
		return E_FAIL;

	//WALK
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/NPC/RoyalGuard/Walk/%d.bmp", L"RoyalGuard", rgb, L"Walk", 8)))
		return E_FAIL;
	//LD
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/NPC/RoyalGuard/Walk/LD/%d.bmp", L"RoyalGuard", rgb, L"WalkLD", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/NPC/RoyalGuard/Walk/LU/%d.bmp", L"RoyalGuard", rgb, L"WalkLU", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/NPC/RoyalGuard/Walk/Left/%d.bmp", L"RoyalGuard", rgb, L"WalkLeft", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/NPC/RoyalGuard/Walk/Up/%d.bmp", L"RoyalGuard", rgb, L"WalkUp", 8)))
		return E_FAIL;

	rgb[0] = 255;
	rgb[1] = 247;
	rgb[2] = 0;
	rgb[3] = 255;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/NPC/Leewonik/%d.bmp", L"Leewonik", rgb, L"Leewonik", 52)))
		return E_FAIL;





	

	//Dash


	//Damage

	//rgb[0] = 255;
	//rgb[1] = 0;
	//rgb[2] = 0;
	//rgb[3] = 0;
	


	////////////////////////////////////////////////////////////////////////////////////////////////////
	//Unit 
	//West_Rifleman

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/Stand/%d.bmp", L"West_Rifleman", rgb, L"Stand", 8)))
		return E_FAIL;
	//Walk

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/Walk/%d.bmp", L"West_Rifleman", rgb, L"Walk", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/Walk/LD/%d.bmp", L"West_Rifleman", rgb, L"WalkLD", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/Walk/LU/%d.bmp", L"West_Rifleman", rgb, L"WalkLU", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/Walk/Left/%d.bmp", L"West_Rifleman", rgb, L"WalkLeft", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/Walk/Up/%d.bmp", L"West_Rifleman", rgb, L"WalkUp", 8)))
		return E_FAIL;

	//Attack

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/Attack/%d.bmp", L"West_Rifleman", rgb, L"Attack", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/Attack/LD/%d.bmp", L"West_Rifleman", rgb, L"AttackLD", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/Attack/LU/%d.bmp", L"West_Rifleman", rgb, L"AttackLU", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/Attack/Left/%d.bmp", L"West_Rifleman", rgb, L"AttackLeft", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/Attack/Up/%d.bmp", L"West_Rifleman", rgb, L"AttackUp", 10)))
		return E_FAIL;

	//Effect
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/effect/%d.bmp", L"West_Rifleman", rgb, L"effect", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/effect/LD/%d.bmp", L"West_Rifleman", rgb, L"effectLD", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/effect/LU/%d.bmp", L"West_Rifleman", rgb, L"effectLU", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/effect/Left/%d.bmp", L"West_Rifleman", rgb, L"effectLeft", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West1/effect/Up/%d.bmp", L"West_Rifleman", rgb, L"effectUp", 10)))
		return E_FAIL;
	/////////////////////////////////////////////////////////////////////////////

		//Unit 
	//West_Boss

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/WestBoss/Stand/%d.bmp", L"West_Boss", rgb, L"Stand", 8)))
		return E_FAIL;
	//Walk

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/WestBoss/Walk/%d.bmp", L"West_Boss", rgb, L"Walk", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/WestBoss/Walk/LD/%d.bmp", L"West_Boss", rgb, L"WalkLD", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/WestBoss/Walk/LU/%d.bmp", L"West_Boss", rgb, L"WalkLU", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/WestBoss/Walk/Left/%d.bmp", L"West_Boss", rgb, L"WalkLeft", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/WestBoss/Walk/Up/%d.bmp", L"West_Boss", rgb, L"WalkUp", 8)))
		return E_FAIL;

	//Attack

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/WestBoss/Attack/%d.bmp", L"West_Boss", rgb, L"Attack", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/WestBoss/Attack/LD/%d.bmp", L"West_Boss", rgb, L"AttackLD", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/WestBoss/Attack/LU/%d.bmp", L"West_Boss", rgb, L"AttackLU", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/WestBoss/Attack/Left/%d.bmp", L"West_Boss", rgb, L"AttackLeft", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/WestBoss/Attack/Up/%d.bmp", L"West_Boss", rgb, L"AttackUp", 8)))
		return E_FAIL;





	////////////////////////////////////////////////////////////////////////////////////

		//Unit 
	//West_Infantry

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West2/Stand/%d.bmp", L"West2", rgb, L"Stand", 8)))
		return E_FAIL;
	//Walk

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West2/Walk/%d.bmp", L"West2", rgb, L"Walk", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West2/Walk/LD/%d.bmp", L"West2", rgb, L"WalkLD", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West2/Walk/LU/%d.bmp", L"West2", rgb, L"WalkLU", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West2/Walk/Left/%d.bmp", L"West2", rgb, L"WalkLeft", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West2/Walk/Up/%d.bmp", L"West2", rgb, L"WalkUp", 8)))
		return E_FAIL;

	//Attack

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West2/Attack/%d.bmp", L"West2", rgb, L"Attack", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West2/Attack/LD/%d.bmp", L"West2", rgb, L"AttackLD", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West2/Attack/LU/%d.bmp", L"West2", rgb, L"AttackLU", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West2/Attack/Left/%d.bmp", L"West2", rgb, L"AttackLeft", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/West2/Attack/Up/%d.bmp", L"West2", rgb, L"AttackUp", 10)))
		return E_FAIL;


	//일본 근접병
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/Japan1/Stand/%d.bmp", L"Japan_infantry", rgb, L"Stand", 8)))
		return E_FAIL;
	//Walk

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/Japan1/Walk/%d.bmp", L"Japan_infantry", rgb, L"Walk", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/Japan1/Walk/LD/%d.bmp", L"Japan_infantry", rgb, L"WalkLD", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/Japan1/Walk/LU/%d.bmp", L"Japan_infantry", rgb, L"WalkLU", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/Japan1/Walk/Left/%d.bmp", L"Japan_infantry", rgb, L"WalkLeft", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/Japan1/Walk/Up/%d.bmp", L"Japan_infantry", rgb, L"WalkUp", 8)))
		return E_FAIL;

	//Attack

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/Japan1/Attack/%d.bmp", L"Japan_infantry", rgb, L"Attack", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/Japan1/Attack/LD/%d.bmp", L"Japan_infantry", rgb, L"AttackLD", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/Japan1/Attack/LU/%d.bmp", L"Japan_infantry", rgb, L"AttackLU", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/Japan1/Attack/Left/%d.bmp", L"Japan_infantry", rgb, L"AttackLeft", 8)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/Japan1/Attack/Up/%d.bmp", L"Japan_infantry", rgb, L"AttackUp", 8)))
		return E_FAIL;

	///////////////////////////////////////////////////////////////////////////////
	rgb[0] = 255;
	rgb[1] = 255;
	rgb[2] = 0;
	rgb[3] = 247;

	//일본 보스
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Boss/Stand/%d.bmp", L"Japan_Boss", rgb, L"Stand", 14)))
		return E_FAIL;
	//Walk

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Boss/Walk/%d.bmp", L"Japan_Boss", rgb, L"Walk", 6)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Boss/Walk/LD/%d.bmp", L"Japan_Boss", rgb, L"WalkLD", 6)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Boss/Walk/LU/%d.bmp", L"Japan_Boss", rgb, L"WalkLU", 6)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Boss/Walk/Left/%d.bmp", L"Japan_Boss", rgb, L"WalkLeft", 6)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Boss/Walk/Up/%d.bmp", L"Japan_Boss", rgb, L"WalkUp", 6)))
		return E_FAIL;

	//Attack

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Boss/Attack/%d.bmp", L"Japan_Boss", rgb, L"Attack", 18)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Boss/Attack/LD/%d.bmp", L"Japan_Boss", rgb, L"AttackLD", 18)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Boss/Attack/LU/%d.bmp", L"Japan_Boss", rgb, L"AttackLU", 18)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Boss/Attack/Left/%d.bmp", L"Japan_Boss", rgb, L"AttackLeft", 18)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Boss/Attack/Up/%d.bmp", L"Japan_Boss", rgb, L"AttackUp", 18)))
		return E_FAIL;


	//천주 최종 보스
	rgb[0] = 255;
	rgb[1] = 247;
	rgb[2] = 0;
	rgb[3] = 255;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Dead/%d.bmp", L"CheonGu", rgb, L"Dead", 25)))
		return E_FAIL;


	//일본 보스
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Stand/%d.bmp", L"CheonGu", rgb, L"Stand", 10)))
		return E_FAIL;
	//Walk

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Walk/%d.bmp", L"CheonGu", rgb, L"Walk", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Walk/LD/%d.bmp", L"CheonGu", rgb, L"WalkLD", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Walk/LU/%d.bmp", L"CheonGu", rgb, L"WalkLU", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Walk/Left/%d.bmp", L"CheonGu", rgb, L"WalkLeft", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Walk/Up/%d.bmp", L"CheonGu", rgb, L"WalkUp", 10)))
		return E_FAIL;

	//Attack

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Attack/%d.bmp", L"CheonGu", rgb, L"Attack", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Attack/LD/%d.bmp", L"CheonGu", rgb, L"AttackLD", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Attack/LU/%d.bmp", L"CheonGu", rgb, L"AttackLU", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Attack/Left/%d.bmp", L"CheonGu", rgb, L"AttackLeft", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Attack/Up/%d.bmp", L"CheonGu", rgb, L"AttackUp", 10)))
		return E_FAIL;




	//Dash 모션

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Dash/%d.bmp", L"CheonGu", rgb, L"Dash", 7)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Dash/LD/%d.bmp", L"CheonGu", rgb, L"DashLD", 7)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Dash/LU/%d.bmp", L"CheonGu", rgb, L"DashLU", 7)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Dash/Left/%d.bmp", L"CheonGu", rgb, L"DashLeft", 7)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Dash/Up/%d.bmp", L"CheonGu", rgb, L"DashUp", 7)))
		return E_FAIL;


	//Dash 이펙트!

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/DashEffect/%d.bmp", L"CheonGu", rgb, L"DashEffect", 7)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/DashEffect/LD/%d.bmp", L"CheonGu", rgb, L"DashEffectLD", 7)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/DashEffect/LU/%d.bmp", L"CheonGu", rgb, L"DashEffectLU", 7)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/DashEffect/Left/%d.bmp", L"CheonGu", rgb, L"DashEffectLeft", 7)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/DashEffect/Up/%d.bmp", L"CheonGu", rgb, L"DashEffectUp", 7)))
		return E_FAIL;


	//스킬 모션
	// 모션

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Skill/%d.bmp", L"CheonGu", rgb, L"Skill", 13)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Skill/LD/%d.bmp", L"CheonGu", rgb, L"SkillLD", 13)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Skill/LU/%d.bmp", L"CheonGu", rgb, L"SkillLU", 13)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Skill/Left/%d.bmp", L"CheonGu", rgb, L"SkillLeft", 13)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Skill/Up/%d.bmp", L"CheonGu", rgb, L"SkillUp", 13)))
		return E_FAIL;


	//스킬 이펙트!

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/SkillEffect/%d.bmp", L"CheonGu", rgb, L"SkillEffect", 13)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/SkillEffect/LD/%d.bmp", L"CheonGu", rgb, L"SkillEffectLD", 13)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/SkillEffect/LU/%d.bmp", L"CheonGu", rgb, L"SkillEffectLU", 13)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/SkillEffect/Left/%d.bmp", L"CheonGu", rgb, L"SkillEffectLeft", 13)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/SkillEffect/Up/%d.bmp", L"CheonGu", rgb, L"SkillEffectUp", 13)))
		return E_FAIL;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/BossShield/%d.bmp", L"CheonGu", rgb, L"Shield", 16)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/CheonGu/Dead/%d.bmp", L"CheonGu", rgb, L"Death", 25)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Effect/CastleBoom/%d.bmp", L"CheonGu", rgb, L"CastleBoom", 20)))
		return E_FAIL;




	rgb[0] = 255;
	rgb[1] = 255;
	rgb[2] = 0;
	rgb[3] = 247;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Samurai/Stand/%d.bmp", L"DAEMA_Samurai", rgb, L"Stand", 6)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Samurai/Attack/%d.bmp", L"DAEMA_Samurai", rgb, L"Attack", 11)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Samurai/Attack/LD/%d.bmp", L"DAEMA_Samurai", rgb, L"AttackLD", 11)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Samurai/Attack/LU/%d.bmp", L"DAEMA_Samurai", rgb, L"AttackLU", 11)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Samurai/Attack/Left/%d.bmp", L"DAEMA_Samurai", rgb, L"AttackLeft", 11)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Samurai/Attack/Up/%d.bmp", L"DAEMA_Samurai", rgb, L"AttackUp", 11)))
		return E_FAIL;




	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Samurai/Walk/LD/%d.bmp", L"DAEMA_Samurai", rgb, L"Walk", 6)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Samurai/Walk/LD/%d.bmp", L"DAEMA_Samurai", rgb, L"WalkLD", 6)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Samurai/Walk/LU/%d.bmp", L"DAEMA_Samurai", rgb, L"WalkLU", 6)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Samurai/Walk/Left/%d.bmp", L"DAEMA_Samurai", rgb, L"WalkLeft", 6)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Monster/DAEMA_Samurai/Walk/Up/%d.bmp", L"DAEMA_Samurai", rgb, L"WalkUp", 6)))
		return E_FAIL;












	rgb[0] = 255;
	rgb[1] = 0;
	rgb[2] = 0;
	rgb[3] = 0;
	//플레이어 화살
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/bullet/%d.bmp", L"PlayerBullet", rgb, L"PlayerBulletDown", 10)))
		return E_FAIL;
	//LD
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/bullet/LD/%d.bmp", L"PlayerBullet", rgb, L"PlayerBulletLD", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/bullet/LU/%d.bmp", L"PlayerBullet", rgb, L"PlayerBulletLU", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/bullet/Left/%d.bmp", L"PlayerBullet", rgb, L"PlayerBulletLeft", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/bullet/Up/%d.bmp", L"PlayerBullet", rgb, L"PlayerBulletUp", 10)))
		return E_FAIL;



	//West_라이플맨 총알
	rgb[0] = 255;
	rgb[1] = 247;
	rgb[2] = 0;
	rgb[3] = 255;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_SINGLE,
		L"../Texture/Stage/Bullet/West_Bullet/0.bmp", L"WestBullet", rgb, L"WestBullet", 1)))
		return E_FAIL;

	//플레이어 Dash

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Dash/Up/%d.bmp", L"Player", rgb, L"PlayerDashUp", 12)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Dash/LD/%d.bmp", L"Player", rgb, L"PlayerDashLD", 12)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Dash/LU/%d.bmp", L"Player", rgb, L"PlayerDashLU", 12)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Dash/Left/%d.bmp", L"Player", rgb, L"PlayerDashLeft", 12)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Dash/%d.bmp", L"Player", rgb, L"PlayerDash", 12)))
		return E_FAIL;



	//플레이어 Dash기 이펙트!

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Shadow/Up/%d.bmp", L"PlayerSkill1", rgb, L"PlayerSkill1Up", 12)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Shadow/LD/%d.bmp", L"PlayerSkill1", rgb, L"PlayerSkill1LD", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Shadow/LU/%d.bmp", L"PlayerSkill1", rgb, L"PlayerSkill1LU", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Shadow/Left/%d.bmp", L"PlayerSkill1", rgb, L"PlayerSkill1Left", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Shadow/%d.bmp", L"PlayerSkill1", rgb, L"PlayerSkill1", 10)))
		return E_FAIL;

	rgb[0] = 255;
	rgb[1] = 255;
	rgb[2] = 0;
	rgb[3] = 255;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Powerbullet/LD1/%d.bmp", L"Powerbullet_Player", rgb, L"Powerbullet_PlayerLD1", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Powerbullet/LD2/%d.bmp", L"Powerbullet_Player", rgb, L"Powerbullet_PlayerLD2", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Powerbullet/LD3/%d.bmp", L"Powerbullet_Player", rgb, L"Powerbullet_PlayerLD3", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Powerbullet/Left/%d.bmp", L"Powerbullet_Player", rgb, L"Powerbullet_PlayerLeft", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Powerbullet/%d.bmp", L"Powerbullet_Player", rgb, L"Powerbullet_Player", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Powerbullet/LU1/%d.bmp", L"Powerbullet_Player", rgb, L"Powerbullet_PlayerLU1", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Powerbullet/LU2/%d.bmp", L"Powerbullet_Player", rgb, L"Powerbullet_PlayerLU2", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Powerbullet/LU3/%d.bmp", L"Powerbullet_Player", rgb, L"Powerbullet_PlayerLU3", 10)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Player/Powerbullet/Up/%d.bmp", L"Powerbullet_Player", rgb, L"Powerbullet_PlayerUp", 10)))
		return E_FAIL;






	/*
	Stand

	Walk

	Attack

	Effect

	*/







	/*
	Stand

	Walk

	Attack

	Effect

	*/




	/*
	Stand

	Walk

	Attack

	Effect

	*/

	
	rgb[0] = 255;
	rgb[1] = 247;
	rgb[2] = 0;
	rgb[3] = 255;

	//마우스
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Mouse/%d.bmp", L"Mouse", rgb, L"MouseClick", 26)))
		return E_FAIL;


	rgb[0] = 255;
	rgb[1] = 255;
	rgb[2] = 0;
	rgb[3] = 255;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Mouse/Stand/%d.bmp", L"Mouse", rgb, L"MouseStand", 1)))
		return E_FAIL;

	rgb[0] = 255;
	rgb[1] = 0;
	rgb[2] = 0;
	rgb[3] = 0;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Mouse/Attack/%d.bmp", L"Mouse", rgb, L"MouseAttack", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Mouse/Move/%d.bmp", L"Mouse", rgb, L"MouseMove", 1)))
		return E_FAIL;




	rgb[0] = 255;
	rgb[1] = 247;
	rgb[2] = 0;
	rgb[3] = 247;
	//퀘스트 창 !!!!!
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Quest/1/%d.bmp", L"Quest", rgb, L"Quest1", 1)))
		return E_FAIL;

	rgb[0] = 255;
	rgb[1] = 247;
	rgb[2] = 0;
	rgb[3] = 255;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Quest/2/%d.bmp", L"Quest", rgb, L"Quest2", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Quest/3/%d.bmp", L"Quest", rgb, L"Quest3", 1)))
		return E_FAIL;

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Quest/4/%d.png", L"Quest", rgb, L"Quest4", 1)))
		return E_FAIL;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Quest/5/%d.bmp", L"Quest", rgb, L"Quest5", 1)))
		return E_FAIL;




	//불화살
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/firearrow/%d.bmp", L"firearrow", rgb, L"firearrow", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/firearrow/LD/%d.bmp", L"firearrow", rgb, L"firearrowLD", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/firearrow/LU/%d.bmp", L"firearrow", rgb, L"firearrowLU", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/firearrow/Left/%d.bmp", L"firearrow", rgb, L"firearrowLeft", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/firearrow/Up/%d.bmp", L"firearrow", rgb, L"firearrowUp", 1)))
		return E_FAIL;


	rgb[0] = 255;
	rgb[1] = 255;
	rgb[2] = 0;
	rgb[3] = 255;
	//불화살 스킬 이펙트

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/firearrow/skill/%d.bmp", L"firearrowSkill", rgb, L"firearrowSkill", 2)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/firearrow/skill/LD/%d.bmp", L"firearrowSkill", rgb, L"firearrowSkillLD", 2)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/firearrow/skill/LU/%d.bmp", L"firearrowSkill", rgb, L"firearrowSkillLU", 2)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/firearrow/skill/Up/%d.bmp", L"firearrowSkill", rgb, L"firearrowSkillUp", 2)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/firearrow/skill/Left/%d.bmp", L"firearrowSkill", rgb, L"firearrowSkillLeft", 2)))
		return E_FAIL;




	rgb[0] = 255;
	rgb[1] = 247;
	rgb[2] = 0;
	rgb[3] = 255;

	//물화살
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/waterarrow/%d.bmp", L"waterarrow", rgb, L"waterarrow", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/waterarrow/LD/%d.bmp", L"waterarrow", rgb, L"waterarrowLD", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/waterarrow/LU/%d.bmp", L"waterarrow", rgb, L"waterarrowLU", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/waterarrow/Up/%d.bmp", L"waterarrow", rgb, L"waterarrowUp", 1)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Bullet/waterarrow/Left/%d.bmp", L"waterarrow", rgb, L"waterarrowLeft", 1)))
		return E_FAIL;


	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Effect/BulletEffect/%d.bmp", L"BulletEffect", rgb, L"BulletEffect", 18)))
		return E_FAIL;


	//거북선

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Turtle/Stand/%d.bmp", L"TurtleShip", rgb, L"Stand", 10)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Turtle/Walk/%d.bmp", L"TurtleShip", rgb, L"Walk", 10)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Turtle/Walk/LD/%d.bmp", L"TurtleShip", rgb, L"WalkLD", 10)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Turtle/Walk/Left/%d.bmp", L"TurtleShip", rgb, L"WalkLeft", 10)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Turtle/Walk/LU/%d.bmp", L"TurtleShip", rgb, L"WalkLU", 10)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
		L"../Texture/Stage/Turtle/Walk/Up/%d.bmp", L"TurtleShip", rgb, L"WalkUp", 10)))
		return E_FAIL;











	//물화살 스킬 이펙트
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
	//	L"../Texture/Stage/Bullet/waterarrow/skill/Left/%d.bmp", L"waterarrowSkill", rgb, L"waterarrowSkillLeft", 2)))
	//	return E_FAIL;
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
	//	L"../Texture/Stage/Bullet/waterarrow/skill/LD/%d.bmp", L"waterarrowSkill", rgb, L"waterarrowSkillLeft", 2)))
	//	return E_FAIL;
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
	//	L"../Texture/Stage/Bullet/waterarrow/skill/LU/%d.bmp", L"waterarrowSkill", rgb, L"waterarrowSkillLeft", 2)))
	//	return E_FAIL;
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
	//	L"../Texture/Stage/Bullet/waterarrow/skill/Up/%d.bmp", L"waterarrowSkill", rgb, L"waterarrowSkillLeft", 2)))
	//	return E_FAIL;
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::TEX_MULTI,
	//	L"../Texture/Stage/Bullet/waterarrow/skill/Left/%d.bmp", L"waterarrowSkill", rgb, L"waterarrowSkillLeft", 2)))
	//	return E_FAIL;





	/////////////////////////////////////////////////////////////////////////////////////////////////
	CTexture_Manager::Get_Instance()->Set_LoadingList(L"로딩 완료!!");
	LeaveCriticalSection(&pLoading->m_Critical_Section);
	return 0;
}

HRESULT CLoading::Ready_Scene()
{


	InitializeCriticalSection(&m_Critical_Section);
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ImageLoading, this, 0, nullptr);
	if (nullptr == m_hThread)
		return E_FAIL;
	
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"Music_Login.ogg");
	return S_OK;
}

void CLoading::Update_Scene()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		WaitForSingleObject(m_hThread, INFINITE);

		DeleteCriticalSection(&m_Critical_Section);
		CloseHandle(m_hThread);
		CScene_Manager::Get_Instance()->Change_Scene_Manager(CScene_Manager::Start);
	}
}

void CLoading::Render_Scene()
{
	D3DXMATRIX matTrans,matScale,matWorld;
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"Loading");

	if (nullptr == pTexInfo)
		return;
	D3DXMatrixScaling(&matScale, 1, 1, 0);
	D3DXMatrixTranslation(&matTrans, WINCX/2, WINCY / 2, 0.f);

	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;
	matWorld = matScale * matTrans;
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	wstring wstrLoadingList = CTexture_Manager::Get_Instance()->Get_LoadingList();
	D3DXMatrixTranslation(&matTrans, 100.f, 500.f, 0.f);
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(),
		wstrLoadingList.c_str(),
		wstrLoadingList.length(),
		nullptr,
		0,
		D3DCOLOR_ARGB(255, 0, 0, 0));
}

void CLoading::Release_Scene()
{
}
