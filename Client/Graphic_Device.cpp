#include "stdafx.h"
#include "Graphic_Device.h"

IMPLEMENT_SINGLETON(CGraphic_Device)
CGraphic_Device::CGraphic_Device()
{
}


CGraphic_Device::~CGraphic_Device()
{
	Release_Graphic_Device(); 
}

HRESULT CGraphic_Device::Ready_Graphic_Device(MODE eMode)
{
	D3DCAPS9 d3dCaps{};
	//ZeroMemory(&d3dCaps, sizeof(D3DCAPS9)); 

	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION); 
	// ��� - ���� ���ܵ����� ������ �׷��� ī�带 �����ϰڴٶ�� ��. 
	// ����̽� Ÿ�� - �ִ� ��ġ�� ������ ��� ���� ���̳�. 
	// HAL �̶�� ������ ������ �����ڴ�. 
	// �̰� �׷��� ī�� ��鿡�� �������� �����͸� ���⿡ �־��ְ� 
	// ���ҿ����� �ű⼭ ������ ������ ���� ��. 
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps)))
		goto ERR;

	// ���ؽ� ���μ��� - ���� ����� �������� ��ģ�� 
	DWORD vp = 0; 
	
	if (d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	// ���� ��ȯ�� ���������� �ϵ����� ó�� �ϰڴ�. 
	else 
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	// ���� ��ȯ�� ���������� ����Ʈ����� ó�� �ϰڴ�. 

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory(&d3dpp, sizeof(d3dpp)); 
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality =0;

	//D3DSWAPEFFECT_DISCARD - ����ü�� ����� ����ϰڴ� ��� ��. 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWND;
	d3dpp.Windowed = eMode;// TRUE �� ��� â���, FALSE�� ��� ��üȭ�� ��� 
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	/* FullScreen_RefreshRateInHz must be zero for Windowed mode */
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// ��ġ�� �����ϱ� ���� �İ�ü �������� ���µ� ����. .. ���� �⺻ �����͸� �����ѰŰ� 
	// ���� ���⼭ ����� ����� �� �������� ����. 
	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWND, vp, &d3dpp, &m_pDevice)))
		goto ERR; 

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
		goto ERR; 

	D3DXFONT_DESCW tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW)); 
	tFontInfo.Height = 20; // ����
	tFontInfo.Width = 10; // �ʺ�
	tFontInfo.Weight = FW_HEAVY;//�β� �׷� ȫ�β�? ��������������������������
	tFontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"����ǹ��� �־�"); 
	if (FAILED(D3DXCreateFontIndirectW(m_pDevice, &tFontInfo, &m_pFont)))
		goto ERR; 

	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
		goto ERR;

	return S_OK;
ERR:
	ERR_MSG(L"Graphic_Device Ready Failed");

	return E_FAIL;
}

void CGraphic_Device::Release_Graphic_Device()
{
	if (m_pLine)
		m_pLine->Release();
	if (m_pFont)
		m_pFont->Release();

	if (m_pSprite)
		m_pSprite->Release();

	if (m_pDevice)
		m_pDevice->Release(); 
	// 
	if (m_pSDK)
		m_pSDK->Release();
}

void CGraphic_Device::Render_Begin()
{
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 255, 0), 0.f, 1);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CGraphic_Device::Render_End(HWND hWnd/* = nullptr*/)
{
	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
}