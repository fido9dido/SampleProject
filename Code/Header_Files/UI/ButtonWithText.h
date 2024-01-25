// Fill out your copyright notice in the Description page of Project Settings.
#ifndef BUTTON_WITH_TEXT_H
#define BUTTON_WITH_TEXT_H

#include "Button.h"
#include <CrySystem/Scaleform/IFlashUI.h> 
#include <CrySchematyc/Utils/SharedString.h> 

////////////////////////////////////////////////////////
// Represents a Button With Text
////////////////////////////////////////////////////////

class CButtonWithText : public CButton
{
private:
	string m_text;
public:

	CButtonWithText();
	//name should match the gfx's name
	CButtonWithText(string name);
	~CButtonWithText() = default;

	void SetText(const string& newText);
	string GetText();
	
	virtual void OnUIEvent(struct IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args) override;
	virtual void OnUIEventEx(struct IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData) override;

   // preparing to reflect it to the editor
	static void ReflectType(Schematyc::CTypeDesc<CButtonWithText>& desc)
	{
		desc.SetGUID("{F422C599-8B9D-4C43-B5C8-593120570B6C}"_cry_guid);
		desc.SetLabel("My Button With Text");

	}
private:
	friend inline bool Serialize(Serialization::IArchive& archive, CButtonWithText& value, const char* szName, const char* szLabel)
	{
		bool bResult = false;
		if (archive.isInput())
		{
			string temp;
			bResult = archive(temp, szName, szLabel);
			value = temp;
		}
		else if (archive.isOutput())
		{
		
			bResult = archive(value.m_text, szName, szLabel);
			
		}
		return bResult;
	}
};

#endif