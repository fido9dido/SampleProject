// Fill out your copyright notice here.

#ifndef BUTTON_H
#define BUTTON_H

#include "Header_Files/Utility/IDGenerator.h" 
#include "Header_Files/UI/IButton.h" 

#include <CrySystem/Scaleform/IFlashUI.h> 

////////////////////////////////////////////////////////
// Represents a base class for a button 
////////////////////////////////////////////////////////
template<typename T>
class CButton : public IButton, public IUIElementEventListener
{
protected:
	IUIElement* m_pUIElement = nullptr;
public:
	//For a button that uses the default asset
	CButton() 
	{
		CRY_ASSERT_MESSAGE(false, "a default asset for buttons doesn't exists yet");

		// This should fail because no asset are made with this name Yet
		IUIElement* pUIElement = gEnv->pFlashUI->GetUIElement("Button");
		
		if (!pUIElement) { return; }

		m_pUIElement = pUIElement->GetInstance(CIDGenerator<T>::GenerateNewID());
		if (m_pUIElement)
		{
			m_pUIElement->AddEventListener(this, "Button");
			m_pUIElement->Init();
		}
	};
	
	//For a button that uses custom assets, it assumes it implements IButton
	CButton(const string& gfxName)
	{
		IUIElement* pUIElement = gEnv->pFlashUI->GetUIElement(gfxName);
		
		if (!pUIElement) { return; }
		
		m_pUIElement = pUIElement->GetInstance(CIDGenerator<T>::GenerateNewID());
		if (m_pUIElement)
		{
			m_pUIElement->AddEventListener(this, gfxName);
			m_pUIElement->Init();
		}
	
	};

	~CButton()
	{
		CIDGenerator<T>::Reset();
		
		if (m_pUIElement)
		{
			m_pUIElement->RemoveEventListener(this);
		}
	}

	void OnReset()
	{
		m_pUIElement->RemoveEventListener(this);
		CIDGenerator<T>::Reset();
	}

	virtual void SetButtonPosition(f32 posX, f32 posY) override
	{
		CallFunction("SetButtonPosition", posX, posY);
	}

	virtual void SetButtonWidthAndHeight(int32 width, int32 height) override
	{
		CallFunction("SetButtonWidthAndHeight", width, height);
	}

	virtual void SetButtonWidth(int32 width) override
	{
		CallFunction("SetButtonWidth", width);
	}

	virtual void SetButtonHeight(int32 height) override
	{
		CallFunction("SetButtonHeight", height);
	}

	virtual void SetVisible(bool value) override
	{
		if (m_pUIElement)
		{
			m_pUIElement->SetVisible(true);
		}
	}
	
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