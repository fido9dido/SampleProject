// Fill out your copyright notice in the Description page of Project Settings.
#ifndef BUTTON_WITH_IMAGE_H
#define BUTTON_WITH_IMAGE_H

#include "Button.h"
#include <CrySystem/Scaleform/IFlashUI.h> 

////////////////////////////////////////////////////////
// Represents a Button With Image 
////////////////////////////////////////////////////////
//This is work in progress, I can't compile the asset for some weird AS3 bug
class CButtonWithImage : public CButton
{
private:
	string m_texturePath;

public:
	CButtonWithImage();
	//name should match the gfx's name
	CButtonWithImage(string name);
	~CButtonWithImage() = default;

	string GetImagePath();
	void SetImagePath(const string& imagePath, int32 width, int32 height);
	
	virtual void OnUIEvent(struct IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args) override;
	virtual void OnUIEventEx(struct IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData) override;

};

#endif