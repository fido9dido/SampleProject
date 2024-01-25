// Fill out your copyright notice in the Description page of Project Settings.
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

string CButtonWithText::GetText()
{
	return CallFunction<string>("GetButtonText");
}

void CButtonWithText::OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args)
{
}

void CButtonWithText::OnUIEventEx(IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData)
{
}
