// Fill out your copyright notice here.
#include "StdAfx.h"
#include "Header_Files/UI/Button.h"
#include <CrySystem/Scaleform/IFlashUI.h> 
#include <cassert>

CButton::CButton(const string& gfxName)
{
	m_pUIElement = gEnv->pFlashUI->GetUIElement(gfxName);
	if (m_pUIElement)
	{
		m_pUIElement->RemoveEventListener(this);	// to avoid double registration
		m_pUIElement->AddEventListener(this, gfxName);
		m_pUIElement->Init();	
	}
}

void CButton::SetButtonPosition(f32 xPos, f32 yPos)
{
	CallFunction("SetButtonPosition", xPos, yPos);
}

void CButton::SetButtonWidthAndHeight(int32 width, int32 height)
{
	CallFunction("SetButtonWidthAndHeight", width, height);
}

void CButton::SetButtonWidth(int32 width)
{
	CallFunction("SetButtonWidth", width);
}

void CButton::SetButtonHeight(int32 height)
{
	CallFunction("SetButtonHeight", height);
}

void CButton::SetVisible(bool value)
{	
	if (m_pUIElement)
	{
		m_pUIElement->SetVisible(true);
	}
}

