// Fill out your copyright notice in the Description page of Project Settings.

#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include <CryEntitySystem/IEntitySystem.h>
#include <Header_Files/UI/ButtonWithText.h>
#include <CrySchematyc/Utils/Array.h>

////////////////////////////////////////////////////////
// Represents a UI Component
// For now I am using this class to test whether buttons works
////////////////////////////////////////////////////////
class CUIComponent final : public IEntityComponent
{
public:
	std::unique_ptr<CButtonWithText> m_pButtonWithText;
	Schematyc::CSharedString m_buttonText;
	
public:
	CUIComponent() = default;
	virtual ~CUIComponent() = default;
	
	//IEntityComponent
	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event);
	//~IEntityComponent
	 
	// Reflect type to set a unique identifier for this component
	// and provide additional information to expose it in the sandbox
	static void ReflectType(Schematyc::CTypeDesc<CUIComponent>& desc)
	{
		desc.SetGUID("{0D382720-1C0C-49DE-BDFA-C5AEF492FDDF}"_cry_guid);
		desc.SetEditorCategory("UI");
		desc.SetLabel("UIComponent");
		desc.SetDescription("UI Component to Display Buttons");
		desc.SetComponentFlags({ IEntityComponent::EFlags::Transform, IEntityComponent::EFlags::Socket, IEntityComponent::EFlags::Attach });
		desc.AddMember(&CUIComponent::m_buttonText, 'btnt', "buttonText", "Button Text", "Set Button Text", "Default");
		}
};

#endif