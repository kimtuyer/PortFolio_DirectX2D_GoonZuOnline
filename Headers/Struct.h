#pragma once

typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture;// 텍스쳐 한장을 보관하기위한 컴객체. 
	D3DXIMAGE_INFO tImageInfo; 

}TEXINFO;
typedef struct tagTile
{
	D3DXVECTOR3 vPos; 
	D3DXVECTOR3 vSize; 
	int iIndex; 
	int iParentIndex; 
	BYTE byDrawID; 
	BYTE byOption; 
}TILE;
typedef struct tagMapObject
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	int iIndex;
	int iParentIndex;
	BYTE byDrawID;
	BYTE byOption;
}MAPOBJECT;


typedef struct tagUnitInfo
{
#ifdef _AFX
	CString wstrName; 
#else 
	wstring wstrName; 
#endif // _AFX

	int		iAtt; 
	int		iDef; 
	BYTE	byJob; 
	BYTE	byItem; 
}UNITINFO;

typedef struct tagInfo
{
	// 	D3DXVECTOR2; 
	// 	D3DXVECTOR3; 
	// 	D3DXVECTOR4; 
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vDir2;
	D3DXVECTOR3 vSize;
	D3DXVECTOR3 vColliderSize;
	int iIndex;
	int iParentIndex;
	BYTE byDrawID;
	BYTE byOption;

	int GoalIndex;
	wchar_t StateKey[20]=L"Stand";
	//wstring StateKey;
	int ID;
	int iAttack_Target = ID::MAP;

	



}INFO;
typedef struct tagFrame
{
	float fFrameStart; 
	float fFrameEnd; 
}FRAME;

typedef struct _tagResolution
{
	unsigned int  iW; //가로
	unsigned int  iH; //세로
	//float x; //가로
	//float y; //세로

	_tagResolution() :
		iW(0.f),
		iH(0.f)
	{

	}

	_tagResolution(int _x, int _y) :
		iW(_x),
		iH(_y)
	{

	}



}RESOLUTION, *PRESOLUTION;


typedef struct _tagDirection8
{
	
	D3DXVECTOR2 Direct[8] = { {1,-TILESX},{1,TILESY} ,{-TILESX,1} ,{-TILESX /2,TILESY /2} ,{-TILESX / 2,-TILESY / 2} ,{-TILESX /2,1} ,{TILESX / 2,TILESY / 2} ,
	{TILESX / 2,-TILESY / 2} };

}Direct8;

enum Direct{ Up,Down,Left,LD,LU,Right,RD,RU};

