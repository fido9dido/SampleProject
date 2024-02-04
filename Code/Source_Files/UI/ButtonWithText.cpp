// Fill out your copyright notice here.
#include "StdAfx.h"
#include "Header_Files/UI/ButtonWithText.h"
#include <CrySystem/Scaleform/IFlashUI.h> 
#include <cassert>

CButtonWithText::CButtonWithText() : CButton("ButtonWithText")
{
}

CButtonWithText::CButtonWithText(string name) : CButton(name)
{
}

void CButtonWithText::SetText(const string& newText)
{
	m_text = newText;
	CallFunction("SetButtonText", m_text);
}

string CButtonWithText::GetButtonText()
{		  
	return CallFunction<string>("GetButtonText");
}

void CButtonWithText::OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args)
{
}

void CButtonWithText::OnUIEventEx(IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData)
{
}
