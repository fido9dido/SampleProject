// Fill out your copyright notice here.
#include "StdAfx.h"
#include "Header_Files/UI/ButtonWithImage.h"
#include <CrySystem/Scaleform/IFlashUI.h> 
#include <cassert>

CButtonWithImage::CButtonWithImage() : CButton("ButtonWithImage")
{
}

CButtonWithImage::CButtonWithImage(string gfxName) : CButton(gfxName)
{
}

int CButtonWithImage::GetTextureID()
{
	return CallFunction<int>("GetTextureID");
}

void CButtonWithImage::SetImagePosition(int xPos, int yPos)
{
	CallFunction("SetImagePosition", xPos, yPos);
}

void CButtonWithImage::SetDefaultWidthAndHeight(int newWidth, int newHeight)
{
	CallFunction("SetDefaultWidthAndHeight", newWidth, newHeight);
}

void CButtonWithImage::SetImageWidth(int newWidth)
{
	CallFunction("SetImageWidth", newWidth);
}

void CButtonWithImage::SetImageHeight(int newHeight)
{
	CallFunction("SetImageHeight", newHeight);
}

void CButtonWithImage::SetTextureID(int textureID)
{
	CallFunction("SetTextureID", textureID);
}

void CButtonWithImage::OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args)
{
}

void CButtonWithImage::OnUIEventEx(IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData)
{
}