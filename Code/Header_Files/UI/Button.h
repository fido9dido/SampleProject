// Fill out your copyright notice in the Description page of Project Settings.
#ifndef BUTTON_H
#define BUTTON_H

#include <CrySystem/Scaleform/IFlashUI.h> 

////////////////////////////////////////////////////////
// Represents a base class for a button 
////////////////////////////////////////////////////////
//todo: Should i make a pure vfunc?! probably! 
class CButton : public IUIElementEventListener
{
protected:
	struct IUIElement* m_pUIElement;
public:

	CButton() = delete;
	//name should match the gfx's name
	CButton(const string& name);
	~CButton() = default;

	//I don't like SetPosition, but this function is here for now, for some reason the xml doesn't position it at all
	void SetPosition(int32 x, int32 y);
	
	void SetWidthAndHeight(int32 width, int32 height);
	void SetWidth(int32 width);
	void SetHeight(int32 height);
	void SetVisible(bool value);
	
	template<typename ...Args>
	void CallFunction(const char* funcName, Args&&... params)
	{
		if (m_pUIElement)
		{
			const SUIEventDesc* eventDesc = m_pUIElement->GetFunctionDesc(funcName);
			if (eventDesc)
			{
				SUIArguments arguments;
				(
					[&]	  
					{
						arguments.AddArgument(params);
					} (), ...);

				m_pUIElement->CallFunction(eventDesc->sName, arguments);// to do assert here
			
			}
		}
	}

	template<typename T, typename ...Args>
	T CallFunction(const char* funcName, Args&&... params)
	{
		T returnValue;
		if (m_pUIElement)
		{
			const SUIEventDesc* eventDesc = m_pUIElement->GetFunctionDesc(funcName);
			if (eventDesc)
			{
				TUIData result;
				SUIArguments arguments;
				(
					[&]
					{
						arguments.AddArgument(params);
					} (), ...);

				if (m_pUIElement->CallFunction(eventDesc->sName, arguments, &result))	// to do assert here
				{
					result.GetValueWithConversion(returnValue);
				} 
			}
		}
		return returnValue;
	}

	bool operator==(const CButton& other) const
	{
		return (m_pUIElement == other.m_pUIElement) ? true : false;
	}
	bool operator!=(const CButton& other) const
	{
		return (m_pUIElement != other.m_pUIElement) ? true : false;
	}

	static void ReflectType(Schematyc::CTypeDesc<CButton>& desc)
	{
		desc.SetGUID("{870DF0A9-A176-42D5-ACE9-9BCC23BB3424}"_cry_guid);
		desc.SetLabel("My Button");

	}
protected:
	virtual void OnUIEvent(struct IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args) override { }
	virtual void OnUIEventEx(struct IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData) override { }

};

#endif