// MapObject.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MapObject.h"
#include "MapUnit.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "MainFrm.h"
#include "MFCToolView.h"


// MapObject 대화 상자

IMPLEMENT_DYNAMIC(MapObject, CDialog)

MapObject::MapObject(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MapObject, pParent)
{

}

MapObject::~MapObject()
{
}

void MapObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(MapObject, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MapObject::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON2, &MapObject::OnBnClickedLoad)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &MapObject::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// MapObject 메시지 처리기


void MapObject::OnBnClickedSave()
{
	CFileDialog Dlg(FALSE, // 다른이름으로 저장. 만약 TRUE 파일 열기. 
		L"dat",// 디폴트 확장자 
		L"*.dat",// 디폴트 파일 이름 
		OFN_OVERWRITEPROMPT);// 덮어쓸때 경고 메시지 띄어주겠다. 
	TCHAR szCurDir[MAX_PATH]{};
	GetCurrentDirectory(MAX_PATH, szCurDir);
	//D:\박병건\118C\D2D\Framework_v1
	PathRemoveFileSpec(szCurDir);
	lstrcat(szCurDir, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szCurDir;
	if (IDOK == Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
		vector<MAPOBJECT*>&vecMapObject = pView->m_pMapObject->m_vecMapObject;
		DWORD dwByte = 0;
		for (auto& pTile : vecMapObject)
			WriteFile(hFile, pTile, sizeof(MAPOBJECT), &dwByte, nullptr);

		CloseHandle(hFile);
	}
}


void MapObject::OnBnClickedLoad()
{
	CFileDialog Dlg(TRUE, // 다른이름으로 저장. 만약 TRUE 파일 열기. 
		L"dat",// 디폴트 확장자 
		L"*.dat",// 디폴트 파일 이름 
		OFN_OVERWRITEPROMPT);// 덮어쓸때 경고 메시지 띄어주겠다. 
	TCHAR szCurDir[MAX_PATH]{};
	GetCurrentDirectory(MAX_PATH, szCurDir);
	//D:\박병건\118C\D2D\Framework_v1
	PathRemoveFileSpec(szCurDir);
	lstrcat(szCurDir, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szCurDir;
	if (IDOK == Dlg.DoModal())
	{
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 1));

		pView->m_pMapObject->Release_MapUnit();


		//pView->m_pTerrain->Release_Terrain();
		DWORD dwByte = 0;
		MAPOBJECT* pTile = nullptr;
		while (true)
		{
			pTile = new MAPOBJECT;
			ReadFile(hFile, pTile, sizeof(MAPOBJECT), &dwByte, nullptr);
			pView->m_pMapObject->m_vecMapObject.push_back(pTile);


			if (0 == dwByte)
			{
				Safe_Delete(pTile);
				break;
			}
			//pView->m_pTerrain->Set_Tile(pTile);
		}
		pView->Invalidate(FALSE);
		CloseHandle(hFile);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void MapObject::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
			// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int iSize = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	TCHAR szBuf[MAX_PATH] = L"";
	CString wstrRelativePath;
	for (int i = 0; i < iSize; ++i)
	{
		DragQueryFile(hDropInfo, i, szBuf, MAX_PATH);
		wstrRelativePath = CFileInfo::ConvertRelativePath(szBuf);
		CString wstrFileNameAndExtension = PathFindFileName(szBuf);
		TCHAR szFileName[MAX_PATH]{};
		lstrcpy(szFileName, wstrFileNameAndExtension.GetString());

		PathRemoveExtension(szFileName);

		m_ListBox.AddString(szFileName);
	}
	m_ListBox.SetHorizontalExtent(500);
	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}


void MapObject::OnLbnSelchangeList1()
{
	UpdateData(TRUE);
	int iIndex = m_ListBox.GetCurSel();
	CString wstrFileName;
	m_ListBox.GetText(iIndex, wstrFileName);
	int i = 0;
	for (; i < wstrFileName.GetLength(); ++i)
	{
		// isdigit 0~ 9까지의 숫자인지 아닌지를 판별해주는 함수. 
		if (isdigit(wstrFileName[i]))
			break;
	}
	wstrFileName.Delete(0, i);
	m_byDrawID = _ttoi(wstrFileName.GetString());

	CGraphic_Device::Get_Instance()->Render_Begin();
	D3DXMATRIX matScale, matTrans, matWorld;
	float fRatioX = float(WINCX) / MAPOBJECTCX;
	float fRatioY = float(WINCY) / MAPOBJECTCY;
	D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 0.f);
	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
	matWorld = matScale * matTrans;

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Manager(L"MapObject", L"Gate", m_byDrawID);
	if (nullptr == pTexInfo)
		return;
	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	float fCenterY = pTexInfo->tImageInfo.Height >> 1;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGraphic_Device::Get_Instance()->Render_End(m_Picture.m_hWnd);
	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
