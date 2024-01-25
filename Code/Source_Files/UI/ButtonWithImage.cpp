// Fill out your copyright notice in the Description page of Project Settings.
#include "StdAfx.h"
#include "Header_Files/UI/ButtonWithImage.h"
#include <CrySystem/Scaleform/IFlashUI.h> 
#include <cassert>

CButtonWithImage::CButtonWithImage() : CButton("ButtonWithImage")
{
}

CButtonWithImage::CButtonWithImage(string name) : CButton(name)
{
}

string CButtonWithImage::GetImagePath()
{
	return CallFunction<string>("GetButtonImagePath");
}

void CButtonWithImage::SetImagePath(const string& imagePath, int32 width, int32 height)
{
	CallFunction("SetButtonImagePath", imagePath, width, height);
}

void CButtonWithImage::OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args)
{
}

void CButtonWithImage::OnUIEventEx(IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData)
{
}