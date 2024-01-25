// Fill out your copyright notice in the Description page of Project Settings.
#include "StdAfx.h"
#include "Header_Files/UI/Button.h"
#include <CrySystem/Scaleform/IFlashUI.h> 
#include <cassert>

CButton::CButton(const string& name)
{
	m_pUIElement = gEnv->pFlashUI->GetUIElement(name);
	if (m_pUIElement)
	{
		m_pUIElement->RemoveEventListener(this);	// to avoid double registration
		m_pUIElement->AddEventListener(this, name);
		m_pUIElement->Init();	
		
	}
}

void CButton::SetPosition(int32 x, int32 y)
{
	CallFunction("SetButtonPosition", x, y);
}

void CButton::SetWidthAndHeight(int32 width, int32 height)
{
	CallFunction("SetButtonWidthAndHeight", width, height);
}

void CButton::SetWidth(int32 width)
{
	CallFunction("SetButtonWidth", width);
}

void CButton::SetHeight(int32 height)
{
	CallFunction("SetButtonHeight", height);
}

void CButton::SetVisible(bool value)
{
	m_pUIElement->SetVisible(true);
}

