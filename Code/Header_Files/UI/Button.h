// Fill out your copyright notice here.
#ifndef BUTTON_H
#define BUTTON_H

#include <CrySystem/Scaleform/IFlashUI.h> 

class IButton
{
	virtual void SetButtonPosition(f32 posX, f32 posY) = 0 ;

	virtual void SetButtonWidthAndHeight(int32 width, int32 height) = 0;
	virtual void SetButtonWidth(int32 width) = 0;
	virtual void SetButtonHeight(int32 height) = 0;
	virtual void SetVisible(bool value) = 0;
};

////////////////////////////////////////////////////////
// Represents a base class for a button 
////////////////////////////////////////////////////////
//todo: Should i make a pure vfunc?! probably! 
class CButton : public IButton, public IUIElementEventListener
{
protected:
	struct IUIElement* m_pUIElement;
public:
	//For a button that uses the default asset
	CButton() {};
	//For a button that uses custom assets, it assumes it implements IButton
	CButton(const string& gfxName);
	~CButton() = default;

	//I don't like SetPosition, but this function is here for now, for some reason the xml doesn't position it at all
	virtual void SetButtonPosition(f32 posX, f32 posY) override;
	virtual void SetButtonWidthAndHeight(int32 width, int32 height) override;
	virtual void SetButtonWidth(int32 width) override;
	virtual void SetButtonHeight(int32 height) override;
	virtual void SetVisible(bool value) override;
	
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

				if(!m_pUIElement->CallFunction(eventDesc->sName, arguments))
				{
					CRY_ASSERT_MESSAGE(false, "Function: %s call failed", eventDesc->sName);
				}
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

				if (m_pUIElement->CallFunction(eventDesc->sName, arguments, &result))	
				{
					result.GetValueWithConversion(returnValue);
				}
				else
				{
					CRY_ASSERT_MESSAGE(false, "Function: %s call failed", eventDesc->sName);
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