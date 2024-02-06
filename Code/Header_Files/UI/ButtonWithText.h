// Fill out your copyright notice here.
#ifndef BUTTON_WITH_TEXT_H
#define BUTTON_WITH_TEXT_H

#include "Button.h"
#include <CrySystem/Scaleform/IFlashUI.h> 
#include <CrySchematyc/Utils/SharedString.h> 

////////////////////////////////////////////////////////
// Represents a Button With Text
////////////////////////////////////////////////////////

class CButtonWithText : public CButton<CButtonWithText>
{
private:
	string m_text;

public:

	CButtonWithText();
	CButtonWithText(string gfxName);
	~CButtonWithText() = default;

	void SetText(const string& newText);
	
	const string& GetText() { return m_text; }

	string GetButtonText();

	virtual void OnUIEvent(struct IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args) override;
	virtual void OnUIEventEx(struct IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData) override;

};

#endif