// Fill out your copyright notice here.
#include "StdAfx.h"
#include "Header_Files/UI/StructureUI.h"
#include <CrySystem/Scaleform/IFlashUI.h> 
#include <cassert>

CStructureUI::CStructureUI() : CButtonWithImage()
{
}

CStructureUI::CStructureUI(string gfxName) : CButtonWithImage(gfxName)
{
}

void CStructureUI::OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args)
{
}

void CStructureUI::OnUIEventEx(IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData)
{
}
