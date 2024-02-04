// Fill out your copyright notice here.
#ifndef BUTTON_WITH_IMAGE_H
#define BUTTON_WITH_IMAGE_H

#include "Button.h"
#include <CrySystem/Scaleform/IFlashUI.h> 
#include <CrySchematyc/Utils/SharedString.h> 

////////////////////////////////////////////////////////
// Represents a Button With Image 
////////////////////////////////////////////////////////
//This is work in progress, I can't compile the asset for some weird AS3 bug
class CButtonWithImage : public CButton
{
private:
	string m_iconPath;

public:
	CButtonWithImage();
	CButtonWithImage(string gfxName);
	~CButtonWithImage() = default;

	int GetTextureID();
	void SetTextureID(int textureID);

	void SetImagePosition(int xPos, int yPos);

	void SetDefaultWidthAndHeight(int newWidth, int newHeight);
	void SetImageWidth(int newWidth);
	void SetImageHeight(int newHeight);
	
	virtual void OnUIEvent(struct IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args) override;
	virtual void OnUIEventEx(struct IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData) override;
	
};

#endif