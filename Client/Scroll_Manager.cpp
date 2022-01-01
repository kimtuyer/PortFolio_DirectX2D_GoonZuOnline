#include "stdafx.h"
#include "Scroll_Manager.h"

IMPLEMENT_SINGLETON(CScroll_Manager)
CScroll_Manager::CScroll_Manager()
{
	ZeroMemory(&m_vScroll, sizeof(D3DXVECTOR3)); 
}


CScroll_Manager::~CScroll_Manager()
{
}

D3DXVECTOR3 CScroll_Manager::Get_Scroll()
{
	return m_vScroll;
}

float CScroll_Manager::Get_Scroll(ID eScrollBar)
{
	switch (eScrollBar)
	{
	case CScroll_Manager::eSB_HORZ:
		return m_vScroll.x; 
	case CScroll_Manager::eSB_VERT:
		return m_vScroll.y; 
	}
	return 0.f;
}

void CScroll_Manager::Set_Scroll(const D3DXVECTOR3 & vScroll)
{
	m_vScroll += vScroll; 
}

void CScroll_Manager::Set_Scroll(ID eScrollBar, const float & fScroll)
{
	switch (eScrollBar)
	{
	case CScroll_Manager::eSB_HORZ:
		m_vScroll.x += fScroll; 
		return; 
	case CScroll_Manager::eSB_VERT:
		m_vScroll.y += fScroll; 
		return; 
	}
}
